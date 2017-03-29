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

//Daten fürs get
const char pflanze[] = "PflanzeNeu";

void setup() {
  int wert = 56;
  char getRequest[1000];
  sprintf (getRequest, "GET /dbConnect.php?name=%s&value=%d", pflanze, wert);
  Serial.begin(19200);
  nanoesp.init();

  //Station Mode, Connect to WiFi
  if (!nanoesp.configWifiStation(ssid, pw)) {
    Serial.println(F("Error: WLAN not Connected\n"));
  }
  else {
    Serial.println(F("WLAN Connected\n"));
  }

 //Print IP in Terminal
  Serial.println(nanoesp.getIp());
  
  //Time for Ping
  int vTime = nanoesp.ping("www.google.de");

  if (vTime > 0 ){
    Serial.println("Internet Connection OK\nPing: " + String(vTime) + "ms"); 
  }
  else {
    Serial.println(F("Error: Internet Connection"));
  }

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
