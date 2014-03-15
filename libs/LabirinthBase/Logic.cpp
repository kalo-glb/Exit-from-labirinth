#include <Logic.h>
#include <Sensors_I.h>
#include <Motors_I.h>
#include <PID_v1.h>

static OpMode mode = NoMode;
static OpMode prevMode = NoMode;
static U8     modeFrozen = 0;

double input, output, setPoint;
PID control(&input, &output, &setPoint, 0.5, 0.1, 3.9, DIRECT);

U16 fSen = 0;
U16 lSen = 0;

void InitLogic()
{
    mode = GoingStreight;
    setPoint = PIDSetPoint;
    control.SetSampleTime(5);
    control.SetMode(AUTOMATIC);
    control.SetOutputLimits(0, 255);
}

OpMode DetermineMode()
{
  if(modeFrozen == 0)
  {
    //Serial.println("not Frozen");                                                             //ser
    lSen = GetLeftSensor();
    fSen = GetForwardSensor();
    //Serial.println(lSen);                                                             //ser
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
    //Serial.println("modeFrozen");                                                             //ser
  }
  
  return mode;
}

void ExecuteMode(OpMode mode)
{
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
  //Serial.println(mode);                                                             //ser
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
        GoForward(127);
      }
      
      //Serial.println("l1");                                                             //ser
      if(False != IsTimerExpired(forwardTimer1, 50))
      {
        stage = 1;
      }
    }
    break;
    case 1:
    {
      if(False == IsTimerStarted(turnTimer))
      {
        StartTimer(&turnTimer);
        Turn(Left, 127);
      }
      
      //Serial.println("l2");                                                             //ser
      if(False != IsTimerExpired(turnTimer, (TurnDelay - 70)))
      {
        stage = 2;
      }
    }
    break;
    case 2:
    {
      if(False == IsTimerStarted(forwardTimer2))
      {
        StartTimer(&forwardTimer2);
        GoForward(127);
      }
      
      //Serial.println("l3");                                                             //ser
      if(False != IsTimerExpired(forwardTimer2, 800))
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
        GoBack(127);
      }
      
      //Serial.println("r1");                                                             //ser
      if(False != IsTimerExpired(forwardTimer1, 950))
      {
        stage = 1;
      }
    }
    break;
    case 1:
    {
      if(False == IsTimerStarted(turnTimer))
      {
        StartTimer(&turnTimer);
        Turn(Right, 200);
      }
      
      //Serial.println("r2");                                                             //ser
      if(False != IsTimerExpired(turnTimer, (TurnDelay + 70)))
      {
        stage = 2;
      }
    }
    break;
    case 2:
    {
      if(False == IsTimerStarted(forwardTimer2))
      {
        //Serial.println("r ent");                                                             //ser
        StartTimer(&forwardTimer2);
        GoForward(127);
      }
      
      //Serial.println("r3");                                                             //ser
      if(False != IsTimerExpired(forwardTimer2, 500))
      {
        //Serial.println("r ex");                                                             //ser
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
