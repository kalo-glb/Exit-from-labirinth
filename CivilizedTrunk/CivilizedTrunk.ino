#include <base.h>
#include <Logic.h>
#include <Sensors_I.h>
#include <Motors_I.h>
#include <Comunication_I.h>

static OpMode mode = NoMode;

void setup()
{
  Init();
  Serial.begin(9600);
}

void loop()
{
  ProcessSensors();  
  mode = DetermineMode();
  ExecuteMode(mode);
}

void Init(void)
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
  InitMotors();
  InitLogic();
}

