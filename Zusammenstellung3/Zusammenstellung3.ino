#include <NanoESP.h>
#include <NanoESP_HTTP.h>
#include <NanoESP_MQTT.h>
#include <string.h>
#include <SoftwareSerial.h>

volatile unsigned int pulseZero;
volatile unsigned int pulseOne;

//Change SSID and PASSWORD here:
const char ssid[] = "FRITZ!Box 6490 Cable";
const char pw[] = "40122403491461293850";

NanoESP nanoesp = NanoESP();

void setup() 
{                
  Serial.begin(19200);
  //pins für sensoren
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  //pins für multiplexer
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
//  pinMode(11, OUTPUT);
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 7;
  TCNT1 = 0;
  interrupts();  
  nanoesp.init();
//  esp8266.begin(19200);
}

void loop() 
{ 
  Serial.println("Beginne Messung...");
  unsigned int value1, value0, value2, value3, value4, value5;

  aktiviereSensor(0);
  value0 = meassure();
  deaktiviereSensor(0); 
  
  Serial.print("Sensor 1: ");
  Serial.println(value0);  

  aktiviereSensor(1);
  value1 = meassure();
  deaktiviereSensor(1);

  Serial.print("Sensor 2: ");
  Serial.println(value1);
  
  aktiviereSensor(2);
  value2 = meassure();
  deaktiviereSensor(2);
  
  Serial.print("Sensor 3: ");
  Serial.println(value2);

  aktiviereSensor(3);
  value3 = meassure();
  deaktiviereSensor(3);

  Serial.print("Sensor 4: ");
  Serial.println(value3);    

  aktiviereSensor(4);
  value4 = meassure();
  deaktiviereSensor(4);
  
  Serial.print("Sensor 5: ");
  Serial.println(value4);
  
  aktiviereSensor(5);
  value5 = meassure();
  deaktiviereSensor(5);

  Serial.print("Sensor 6: ");
  Serial.println(value5);

  //Station Mode, Connect to WiFi  
  if (!nanoesp.configWifiStation(ssid, pw)) {
    Serial.println(F("Error: WLAN not Connected\n"));
    return;
  }
  else {
    Serial.println(F("WLAN Connected\n"));
  }

  if(nanoesp.newConnection(0, "TCP", "193.196.175.151", 80 ))
  {
    Serial.println("true");
  }
  else {
    Serial.println("false");
  }
  //sendet Daten der ersten Messung
  if(nanoesp.sendData(0, createPostRequest(value0, 1, 1 )))
  { 
    Serial.println("Success");
  }
  else {
    Serial.println("FAIL");
  }

  //sendet Daten der zweiten Messung
  if(nanoesp.sendData(0, createPostRequest(value1, 2, 1 )))
  { 
    Serial.println("Success");
  }
  else {
    Serial.println("FAIL");
  }

  //sendet Daten der dritten Messung
  if(nanoesp.sendData(0, createPostRequest(value2, 3, 1 )))
  { 
    Serial.println("Success");
  }
  else {
    Serial.println("FAIL");
  }

  //sendet Daten der vierten Messung
  if(nanoesp.sendData(0, createPostRequest(value3, 4, 1 )))
  { 
    Serial.println("Success");
  }
  else {
    Serial.println("FAIL");
  }

  //sendet Daten der fünften Messung
  if(nanoesp.sendData(0, createPostRequest(value4, 5, 1 )))
  { 
    Serial.println("Success");
  }
  else {
    Serial.println("FAIL");
  }

  //sendet Daten der sechsten Messung
  if(nanoesp.sendData(0, createPostRequest(value5, 6, 1 )))
  { 
    Serial.println("Success");
  }
  else {
    Serial.println("FAIL");
  }

  nanoesp.closeConnection(0);

  //warten bis zur nächsten Messung
  delay(3578500);
}

unsigned int meassure()
{
//  return TCNT1L + (TCNT1H<<8);
  
  TCNT1 = 0;
  delay(10);
  return TCNT1;
}


void aktiviereSensor(unsigned short sensor)
{
  digitalWrite(14+sensor, HIGH);
  
  digitalWrite(8,  (sensor & B0001) ? HIGH : LOW);
  digitalWrite(9, (sensor & B0010) ? HIGH : LOW);
  digitalWrite(10, (sensor & B0100) ? HIGH : LOW);
  delay(150);
}

void deaktiviereSensor(short sensor)
{
  digitalWrite(14+sensor, LOW);
}

char * createPostRequest(int messwert1, int sensor, int pflanze){
  char getRequest[256];
  char content[64];
  
  sprintf(content,  "w=%d&s=%d&p=%d", messwert1, sensor, pflanze);
  
  sprintf(getRequest, "POST /insertMesswerte.php HTTP/1.1\r\n");
  sprintf(getRequest, "%sHost: 193.196.175.151\r\n", getRequest);
  sprintf(getRequest, "%sContent-Length: %d\r\n", getRequest, strlen(content));
  sprintf(getRequest, "%sContent-Type: application/x-www-form-urlencoded\r\n\r\n", getRequest);
  sprintf(getRequest, "%s%s", getRequest, content);
  return getRequest;
}
