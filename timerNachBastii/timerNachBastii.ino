#include <SoftwareSerial.h>

volatile unsigned int pulseZero;
volatile unsigned int pulseOne;

void setup() 
{                
  Serial.begin(19200);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 7;
  TCNT1 = 0;
  interrupts();
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

  delay(200);
 
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
  
  digitalWrite(9,  (sensor & B0001) ? HIGH : LOW);
  digitalWrite(10, (sensor & B0010) ? HIGH : LOW);
  digitalWrite(11, (sensor & B0100) ? HIGH : LOW);

//  switch(sensor){
//    case 0: {
//      digitalWrite(9, LOW);
//      digitalWrite(10, LOW);
//      digitalWrite(11, LOW);
//      break;
//    }
//    case 1: {
//      digitalWrite(9, HIGH);
//      digitalWrite(10, LOW);
//      digitalWrite(11, LOW);
//      break;
//    }
//    case 2: {
//      digitalWrite(9, LOW);
//      digitalWrite(10, HIGH);
//      digitalWrite(11, LOW);
//      break;
//    }
//    case 3: {
//      digitalWrite(9, HIGH);
//      digitalWrite(10, HIGH);
//      digitalWrite(11, LOW);
//      break;
//    }
//    case 4: {
//      digitalWrite(9, LOW);
//      digitalWrite(10, LOW);
//      digitalWrite(11, HIGH);
//      break;
//    }
//    case 5: {
//      digitalWrite(9, HIGH);
//      digitalWrite(10, LOW);
//      digitalWrite(11, HIGH);
//      break;
//    }
//  }

  delay(150);
}

void deaktiviereSensor(short sensor)
{
  digitalWrite(14+sensor, LOW);
}
