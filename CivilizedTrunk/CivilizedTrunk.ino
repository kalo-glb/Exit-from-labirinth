#include <PID_v1.h>
#include <base.h>
#include <Sensors_I.h>
#include <Motors_I.h>
#include <Comunication_I.h>

//#define SERDEBUG
//#define MOTORSTREIGHT
OpMode mode = NoMode;
OpMode prevMode = NoMode;
U16 fSen = 0;
U16 lSen = 0;

double input, output, setPoint;
PID control(&input, &output, &setPoint, 0.5, 0.1, 3.9, DIRECT);

#ifdef SERDEBUG
U16 sen1, sen2;
#endif

void setup()
{
  Init();
  
  #ifdef SERDEBUG
  Serial.begin(115200);
  #endif

  setPoint = PIDSetPoint;
  mode = GoingStreight;
}

void loop()
{
  ProcessSensors();  
  
  #ifdef SERDEBUG
  //Serial.println(input);
  sen1 = GetLeftSensor();
  sen2 = GetRightSensor();
  PrintSensors(sen1, sen2, 0);
  #endif
  
  
  
  #ifndef MOTORSTREIGHT
    
  DetermineMode();
  
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
  #else/*
  // motors set to same speed for streight forward motion
  static boolean phase = 0;
  if(phase == 1)
  {
    ProcessMotors(127);
    phase = 0;
  }
  else
  {
    ProcessMotors(128);
    phase = 1;
  }*/
  #endif
}

void ExecuteLeftTurn()
{
  GoForward(127);
  delay(100);
  Turn(Left, 127);
  delay(280);
  GoForward(127);
  delay(1000);
}

void ExecuteRightTurn()
{
  GoBack(127);
  delay(570);
  Turn(Right, 127);
  delay(280);
  GoForward(127);
  delay(600);
}

void DetermineMode()
{
  lSen = GetLeftSensor();
  fSen = GetForwardSensor();
  if(!fSen)
  {
    mode = TurningRight;
  }
  else if((lSen < WallThreshhold)/* && (prevMode != TurningLeft)*/)
  {
    mode = TurningLeft;
  }
  else
  {
    mode = GoingStreight;
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
  
  control.SetSampleTime(5);
  control.SetMode(AUTOMATIC);
  control.SetOutputLimits(0, 255);
}

void PrintSensors(U16 s1, U16 s2, U16 s3)
{
	Serial.print("s1 : ");
	Serial.print(s1);
	Serial.print("s2 : ");
	Serial.print(s2);
	Serial.print("s3 : ");
	Serial.println(s3);
}
