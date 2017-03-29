#include <NanoESP.h>
//#include <NanoESP_Flash.h>
#include <NanoESP_HTTP.h>
#include <NanoESP_MQTT.h>

/*
  Test for Wifi connection and ping-time
  Change SSID and PASSWORD.
*/

//#include <NanoESP.h>
#include <SoftwareSerial.h>

//Change SSID and PASSWORD here:



NanoESP nanoesp = NanoESP();
NanoESP_HTTP http = NanoESP_HTTP(nanoesp);

void setup() {
  Serial.begin(19200);
  nanoesp.init();

  //Station Mode, Connect to WiFi
  if (!nanoesp.configWifiStation("Arduino_test", "test1234Arduino")) {
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

  if(nanoesp.sendData(0, "GET /dbConnect.php?name=Pflanze&value=45\r\nHost: 193.196.175.151\r\n\r\n"))
  { 
    Serial.println("Success");
  }
  else {
    Serial.println("FAIL");
  }
}

void loop() {

}
