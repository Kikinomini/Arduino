#include <SoftwareSerial.h>
#include <NanoESP.h>
#include <NanoESP_HTTP.h>
#include <NanoESP_MQTT.h>
#include <string.h>

NanoESP nanoesp = NanoESP();
//NanoESP_HTTP http = NanoESP_HTTP(nanoesp);

//Zugang WLAN
const char ssid[] = "Arduino_test";
const char pw[] = "test1234Arduino";

//Daten für Übertragung
//const char pflanze[] = "PflanzeNeu";
//int wert = 56;
//char getRequest[1000];
  
unsigned int value1, value0;

//LEDs
int red = 7;
int white = 8;

void aktiviereSensor(short sensor);
unsigned int meassure();
void deaktiviereSensor(short sensor);

void setup() 
{                
  Serial.begin(19200);
  //Initialisierung PINs
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(white, OUTPUT);

  //Registermodifikation für Counter
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 7;
  TCNT1 = 0;
  interrupts();

  
  nanoesp.init();


  // Loop?
  //sprintf (getRequest, "GET /dbConnect.php?name=%s&value=%d", pflanze, wert);
}

void loop() 
{
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


   int vTime = nanoesp.ping("www.google.de");

  if (vTime > 0 ){
    Serial.println("Internet Connection OK\nPing: " + String(vTime) + "ms"); 
  }
  else {
    Serial.println(F("Error: Internet Connection"));
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

//  if(nanoesp.sendData(0, getRequest))
//  { 
//    Serial.println("Success");
//  }
//  else {
//    Serial.println("FAIL");
//  }

  
//  aktiviereSensor(0);
//  value0 = meassure();
//  deaktiviereSensor(0);

  //digitalWrite(9, HIGH);
  //digitalWrite(10, LOW);
  //digitalWrite(11, LOW);
  

//  aktiviereSensor(1);
//  value1 = meassure();
//  deaktiviereSensor(1);
  
//  Serial.print(value0);
//  Serial.print(" ");
//  Serial.println(value1);

  
// 
//  if (!nanoesp.disconnectWifi()) {
//    Serial.println(F("Error: WLAN still Connected :(\n"));
//    digitalWrite(white, HIGH);
//    delay(10000);
//    digitalWrite(white, LOW);
//  }
//  else {
//    Serial.println(F("WLAN Disconnected :)\n"));
//    digitalWrite(red, HIGH);
//    delay(10000);
//    digitalWrite(red, LOW);
  
// }
  delay(1000);
}


//unsigned int meassure()
//{
////  return TCNT1L + (TCNT1H<<8);
//  
//  TCNT1 = 0;
//  delay(10);
//  return TCNT1;
//}


//void aktiviereSensor(short sensor)
//{
//  digitalWrite(14+sensor, HIGH);
//
//  digitalWrite(9, sensor & 0001);
//  digitalWrite(10, sensor & 0010);
//  digitalWrite(11, sensor & 0100);
//  
//  delay(150);
//}
//
//void deaktiviereSensor(short sensor)
//{
//  digitalWrite(14+sensor, LOW);
//}

