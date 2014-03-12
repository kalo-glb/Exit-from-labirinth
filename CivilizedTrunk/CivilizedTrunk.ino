#include <PID_v1.h>
#include <base.h>
#include <Sensors_I.h>
#include <Motors_I.h>
#include <Comunication_I.h>

OpMode mode = NoMode;
OpMode prevMode = NoMode;
U8     modeFrozen = 0;

U16 fSen = 0;
U16 lSen = 0;

#define TurnDelay 350

double input, output, setPoint;
PID control(&input, &output, &setPoint, 0.5, 0.1, 3.9, DIRECT);

void setup()
{
  Init();

  setPoint = PIDSetPoint;
  mode = GoingStreight;
}

void loop()
{
  ProcessSensors();  
  DetermineMode();
  
  /*
  switch(mode)
  {
    
  }
  */
  if(mode == GoingStreight)
  {
    input = GetPIDInput();
    control.Compute();
    ProcessMotors(int(output));
  }
  else if(mode == TurningRight)
  {
    ExecuteRightTurn();
    prevMode = TurningRight;
  }
  else if(mode == TurningLeft)
  {
    ExecuteLeftTurn();
    prevMode = TurningLeft;
  }
}

void ExecuteLeftTurn()
{
  GoForward(127);
  delay(50);
  Turn(Right, 127);
  delay(TurnDelay - 40);
  GoForward(127);
  delay(1000);
}

void ExecuteRightTurn()
{
  GoBack(127);
  delay(520);//540
  Turn(Left, 127);
  delay(TurnDelay + 10);
  GoForward(127);
  delay(500);//600
}

void DetermineMode()
{
  if(modeFrozen == 0)
  {
    lSen = GetLeftSensor();
    fSen = GetForwardSensor();
    if(!fSen)
    {
      mode = TurningRight;
    }
    else if(lSen < WallThreshhold)
    {
      mode = TurningLeft;
    }
    else
    {
      mode = GoingStreight;
    }
  }
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
  
  control.SetSampleTime(5);
  control.SetMode(AUTOMATIC);
  control.SetOutputLimits(0, 255);
}
