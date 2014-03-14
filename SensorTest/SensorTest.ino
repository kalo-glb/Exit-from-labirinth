#include <Sensors_I.h>

uint16_t sen1 = 0;
uint16_t sen2 = 0;
int count = 0;

void setup()
{
  PORTB = 0;
  PORTD = 0;
  PORTC = 0;
  DDRC = B11111111;
  
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  
  InitSensors();
  
  Serial.begin(9600);
}

void loop()
{
  ProcessSensors();
  
  count++;
  if(count > 20)
  {
    sen1 = GetLeftSensor();
    sen2 = GetRightSensor();
    Serial.print(sen1);
    Serial.print(" ");
    Serial.println(sen2);
  }
}
