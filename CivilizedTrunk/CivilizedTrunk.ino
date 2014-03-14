#include <PID_v1.h>
#include <base.h>
#include <Sensors_I.h>
#include <Motors_I.h>
#include <Comunication_I.h>

static OpMode mode = NoMode;
static OpMode prevMode = NoMode;
static U8     modeFrozen = 0;

U16 fSen = 0;
U16 lSen = 0;

double input, output, setPoint;
PID control(&input, &output, &setPoint, 0.5, 0.1, 3.9, DIRECT);

void setup()
{
  Init();

  setPoint = PIDSetPoint;
  mode = GoingStreight;
  
  //Serial.begin(9600);
}

void loop()
{
  ProcessSensors();  
  DetermineMode();
  
  switch(mode)
  {
  case GoingStreight:
    input = GetPIDInput();
    control.Compute();
    ProcessMotors(int(output));
    break;
  case TurningRight:
    ExecuteRightTurn();
    prevMode = TurningRight;
    break;
  case TurningLeft:
    ExecuteLeftTurn();
    prevMode = TurningLeft;
    break;
  }
}

void ExecuteLeftTurn()
{
  static U32 forwardTimer1 = 0;
  static U32 turnTimer     = 0;
  static U32 forwardTimer2 = 0;
  static U8  stage = 0;
  
  switch(stage)
  {
    case 0:
    {
      if(False == IsTimerStarted(forwardTimer1))
      {
        StartTimer(&forwardTimer1);
        modeFrozen = True;
      }
      
      GoForward(127);
      
      if(False != IsTimerExpired(forwardTimer1, 50))
        stage += 1;
    }
    break;
    case 1:
    {
      if(False == IsTimerStarted(turnTimer))
        StartTimer(&turnTimer);
      
      Turn(Left, 127);
      
      if(False != IsTimerExpired(turnTimer, (TurnDelay - 40)))
        stage += 1;
    }
    break;
    case 2:
    {
      if(False == IsTimerStarted(turnTimer))
        StartTimer(&turnTimer);
      
      GoForward(127);
      
      if(False != IsTimerExpired(turnTimer, 1000))
      {
        forwardTimer1 = 0;
        turnTimer     = 0;
        forwardTimer2 = 0;
        stage = 0;
        modeFrozen = False;
      }
    }
    break;
  }
}

void ExecuteRightTurn()
{
  static U32 forwardTimer1 = 0;
  static U32 turnTimer     = 0;
  static U32 forwardTimer2 = 0;
  static U8  stage = 0;
  switch(stage)
  {
    case 0:
    {
      if(False == IsTimerStarted(forwardTimer1))
      {
        StartTimer(&forwardTimer1);
        modeFrozen = True;
      }
      //Serial.println("l1");
      GoBack(127);
      
      if(False != IsTimerExpired(forwardTimer1, 1000))
        stage += 1;
    }
    break;
    case 1:
    {
      if(False == IsTimerStarted(turnTimer))
        StartTimer(&turnTimer);
      //Serial.println("l2");
      Turn(Left, 150);
      
      if(False != IsTimerExpired(turnTimer, (TurnDelay)))
        stage += 1;
    }
    break;
    case 2:
    {
      if(False == IsTimerStarted(turnTimer))
        StartTimer(&turnTimer);
      //Serial.println("l3");
      GoForward(127);
      
      if(False != IsTimerExpired(turnTimer, 500))
      {
        forwardTimer1 = 0;
        turnTimer     = 0;
        forwardTimer2 = 0;
        stage = 0;
        modeFrozen = False;
      }
    }
    break;
  }
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
  else
  {
    //Serial.println("modeFrozen");
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

void StartTimer(U32 *timerAddr)
{
    *timerAddr = millis();
}

U8 IsTimerExpired(U32 timerAddr, U32 timerDelay)
{
    if(False != IsTimerStarted(timerAddr))
    {
        if((timerAddr + timerDelay) < (millis()))
        {
            return True;
        }
        else
        {
            return False;
        }
    }
    else
    {
        return False;
    }
}

U8 IsTimerStarted(U32 timerAddr)
{
    if(0 != timerAddr)
    {
        return True;
    }
    else
    {
        return False;
    }
}
