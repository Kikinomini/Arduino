#include <NanoESP.h>
#include <NanoESP_HTTP.h>
#include <NanoESP_MQTT.h>
#include <string.h>
#include <SoftwareSerial.h>

//Change SSID and PASSWORD here:
const char ssid[] = "ssid";
const char pw[] = "passwort";

char getRequest[256];
char content[64];

unsigned int value0, value2;

  
NanoESP nanoesp = NanoESP();

//LEDs
int red = 4;
int white = 3;

void setup() 
{                
  Serial.begin(19200);
  //pins for ports
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
   
  //pins for sensors
  pinMode(14, OUTPUT);
  pinMode(16, OUTPUT);
  //pins for multiplexer
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 7;
  TCNT1 = 0;
  interrupts();  
  nanoesp.init();
}

void loop() 
{ 
  Serial.println("Beginne Messung...");

  activateSensor(0);
  value0 = measure();
  deactivateSensor(0); 
  
  Serial.print("Sensor 1: ");
  Serial.println(value0);  
  
  activateSensor(2);
  value2 = measure();
  deactivateSensor(2);
  
  Serial.print("Sensor 3: ");
  Serial.println(value2);


  //Connect to WiFi  
  if (!nanoesp.configWifiStation(ssid, pw)) {
    digitalWrite(red, HIGH);
    delay(10000);
    digitalWrite(red, LOW);
    return;
  }
  else {
    Serial.println(F("WLAN Connected\n"));
    digitalWrite(white, HIGH);
    delay(10000);
    digitalWrite(white, LOW);
  }

  if(nanoesp.newConnection(0, "TCP", "193.196.175.151", 80 ))
  {
    Serial.println("true");
  }
  else {
    Serial.println("false");
  }
  //Sending data first measure
  if(nanoesp.sendData(0, createPostRequest(value0, 1, 0 )))
  { 
    Serial.println("Success");
  }
  else {
    Serial.println("FAIL");
  }

  //Sending data second measure
  if(nanoesp.sendData(0, createPostRequest(value2, 3, 0 )))
  { 
    Serial.println("Success");
  }
  else {
    Serial.println("FAIL");
  } 

  nanoesp.closeConnection(0);

  //warten bis zur nächsten Messung
//  delay(2000);
  delay(3578500);
}

unsigned int measure()
{

  TCNT1 = 0;
  delay(10);
  return TCNT1;
}


void activateSensor(unsigned short sensor)
{
  digitalWrite(14+sensor, HIGH);
  
  digitalWrite(8,  (sensor & B0001) ? HIGH : LOW);
  digitalWrite(9, (sensor & B0010) ? HIGH : LOW);
  digitalWrite(10, (sensor & B0100) ? HIGH : LOW);
  delay(150);
}

void deactivateSensor(short sensor)
{
  digitalWrite(14+sensor, LOW);
}

char * createPostRequest(int messwert1, int sensor, int pflanze){

  
  sprintf(content,  "w=%d&s=%d&p=%d", messwert1, sensor, pflanze);
  
  sprintf(getRequest, "POST /insertMesswerte.php HTTP/1.1\r\n");
  sprintf(getRequest, "%sHost: 193.196.175.151\r\n", getRequest);
  sprintf(getRequest, "%sContent-Length: %d\r\n", getRequest, strlen(content));
  sprintf(getRequest, "%sContent-Type: application/x-www-form-urlencoded\r\n\r\n", getRequest);
  sprintf(getRequest, "%s%s", getRequest, content);
  return getRequest;
}
