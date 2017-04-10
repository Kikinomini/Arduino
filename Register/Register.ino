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
//  attachInterrupt(0, zaehlenZero, RISING);
}

void loop() 
{
  //Serial.println("Beginne Messung...");
  unsigned int value1, value0, value2, value3, value4, value5;

  aktiviereSensor(0);
  value0 = meassure();
  delay(100);
  deaktiviereSensor(0); 
  
  Serial.print("Sensor 1: ");
  Serial.println(value0);
  

  aktiviereSensor(1);
  value1 = meassure();
  delay(100);
  deaktiviereSensor(1);

  Serial.print("Sensor 2: ");
  Serial.println(value1);

  
  aktiviereSensor(2);
  value2 = meassure();
  delay(100);
  deaktiviereSensor(2);
  
  Serial.print("Sensor 3: ");
  Serial.println(value2);


  aktiviereSensor(3);
  value3 = meassure();
  delay(100);
  deaktiviereSensor(3);

  Serial.print("Sensor 4: ");
  Serial.println(value3);
    

  aktiviereSensor(4);
  value4 = meassure();
  delay(100);
  deaktiviereSensor(4);
  
  Serial.print("Sensor 5: ");
  Serial.println(value4);
  

  aktiviereSensor(5);
  value5 = meassure();
  delay(100);
  deaktiviereSensor(5);

  Serial.print("Sensor 6: ");
  Serial.println(value5);


  delay(5000);
  
          
//  Serial.print(value0);
//  Serial.print(" ");
//  Serial.println(value1);
 
}

unsigned int meassure()
{
//  return TCNT1L + (TCNT1H<<8);
  
  TCNT1 = 0;
  delay(10);
  return TCNT1;
}


void aktiviereSensor(short sensor)
{
  digitalWrite(14+sensor, HIGH);
//
//  digitalWrite(9, sensor & 0001);
//  digitalWrite(10, sensor & 0010);
//  digitalWrite(11, sensor & 0100);

  switch(sensor){
    case 0: {
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
    }
    case 1: {
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
    }
    case 2: {
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
    }
    case 3: {
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
    }
    case 4: {
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
    }
    case 5: {
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
    }
  }
  
  
  //delay(60);
  delay(150);
}

void deaktiviereSensor(short sensor)
{
  digitalWrite(14+sensor, LOW);
}

