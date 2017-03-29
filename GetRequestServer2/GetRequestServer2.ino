#include <NanoESP.h>
#include <NanoESP_HTTP.h>
#include <NanoESP_MQTT.h>
#include <SoftwareSerial.h>
#include <string.h>

NanoESP nanoesp = NanoESP();
NanoESP_HTTP http = NanoESP_HTTP(nanoesp);

//Change SSID and PASSWORD here:
char ssid[] = "Arduino_test";
char pw[] = "test1234Arduino";

//Data for GET
const char pflanze[] = "PflanzeNeu";

//LEDs
int red = 8;
int white = 9;

void setup() {
  int wert = 56;
  char getRequest[1000];
  sprintf (getRequest, "GET /dbConnect.php?name=%s&value=%d", pflanze, wert);
  Serial.begin(19200);
  nanoesp.init();

  pinMode(white, OUTPUT);
  pinMode(red, OUTPUT);

  //Station Mode, Connect to WiFi
  if (!nanoesp.configWifiStation(ssid, pw)) {
    Serial.println(F("Error: WLAN not Connected :(\n"));
    digitalWrite(red, HIGH);
    delay(10000);
    digitalWrite(red, LOW);
  }
  else {
    Serial.println(F("WLAN Connected :)\n"));
    digitalWrite(white, HIGH);
    delay(10000);
    digitalWrite(white, LOW);
  }

 //Print IP in Terminal
  Serial.println(nanoesp.getIp());
  


  if(nanoesp.newConnection(0, "TCP", "193.196.175.151", 80 ))
  {
    Serial.println("true");
    }
    else {
      Serial.println("false");
      }

  if(nanoesp.sendData(0, getRequest))
  { 
    Serial.println("Success");
  }
  else {
    Serial.println("FAIL");
  }
}

void loop() {

}
