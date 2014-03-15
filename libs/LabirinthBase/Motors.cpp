#include <base.h>
#include <Motors_I.h>
#include <Motors_Cfg.h>

static Motors *motors;
static Motors *oldMotors;

void ProcessMotors(U16 PIDResult)
{
	UpdateMotors(PIDResult, Forward, (255 - PIDResult), Forward);
}

void Turn(U8 direction, U8 speed)
{
	UpdateMotors(
			speed, 
			((direction == Left)? Forward : Back), 
			speed, 
			((direction == Left)? Back : Forward)
			);
}

void GoForward(U8 speed)
{
	UpdateMotors(speed, Forward, speed, Forward);
}

void GoBack(U8 speed)
{
	UpdateMotors(speed, Back, speed, Back);
}

/*
//deprecated
void SetMotorDirection(U8 motor, U8 direction, U8 speed)
{
	speed = CompensateMotor(speed, 200);
	if(Right == motor)
	{
		//speed = CompensateMotor(speed, 240); // 238
		if(Forward == direction)
		{
			digitalWrite(RMotorB, 0);
			analogWrite(RMotorF, speed);
		}
		else if(Back == direction)
		{
			digitalWrite(RMotorF, 0);
			analogWrite(RMotorB, speed);
		}

	}
	else if(Left == motor)
	{
		//speed = CompensateMotor(speed, 238);
		if(Forward == direction)
		{
			digitalWrite(LMotorB, 0);
			analogWrite(LMotorF, speed);
		}
		else if(Back == direction)
		{
			digitalWrite(LMotorF, 0);
			analogWrite(LMotorB, speed);

		}
	}
}

//tb6612f
void UpdateMotors(U8 leftSpeed, U8 leftDir, U8 rightSpeed, U8 rightDir)
{
	if(Forward == leftDir)
	{
		digitalWrite(LMotorF, HIGH);
		digitalWrite(LMotorB, LOW);
	}
	else if(Back == leftDir)
	{
		digitalWrite(LMotorF, LOW);
		digitalWrite(LMotorB, HIGH);
	}
	analogWrite(LSpeed, leftSpeed);
	
	if(Forward == rightDir)
	{
		digitalWrite(RMotorF, HIGH);
		digitalWrite(RMotorB, LOW);
	}
	else if(Back == rightDir)
	{
		digitalWrite(RMotorF, LOW);
		digitalWrite(RMotorB, HIGH);
	}
	analogWrite(RSpeed, leftSpeed);
}

U8 IsChangeInMotors(Motors *motors, Motors *oldMotors)
{
    U8 i = 0;
    for(;i < sizeof(Motors);i++)
    {
        if(((U8 *)motors)[i] != ((U8 *)oldMotors)[i])
        {
            return True;
        }
    }
    
    return False;
}
*/

//l293b
void UpdateMotors(U8 leftSpeed, U8 leftDir, U8 rightSpeed, U8 rightDir)
{
    //if(False != IsChangeInMotors(motors, oldMotors))
    //{
    // compensate left motor speed
    rightSpeed = CompensateMotor(rightSpeed, 230);
    if(Forward == leftDir)
    {
        analogWrite(LMotorF, leftSpeed);
        digitalWrite(LMotorB, LOW);
    }
    else if(Back == leftDir)
    {
        analogWrite(LMotorB, leftSpeed);
        digitalWrite(LMotorF, LOW);
    }
    
    if(Forward == rightDir)
    {
        analogWrite(RMotorF, rightSpeed);
        digitalWrite(RMotorB, LOW);
    }
    else if(Back == rightDir)
    {
        analogWrite(RMotorB, rightSpeed);
        digitalWrite(RMotorF, LOW);
    }
    //}
}

void InitMotors()
{
    //tb6612f
	//pinMode(LSpeed, OUTPUT);
	//pinMode(RSpeed, OUTPUT);
	pinMode(LMotorF, OUTPUT);
	pinMode(LMotorB, OUTPUT);
	pinMode(RMotorF, OUTPUT);
	pinMode(RMotorB, OUTPUT);
	
	/*
	motors = (Motors *)malloc(sizeof(Motors));
	oldMotors = (Motors *)malloc(sizeof(Motors));
	
	memset((void *)oldMotors, 0, sizeof(oldMotors));
	memset((void *)motors, 0, sizeof(oldMotors));
	*/
}

U8 CompensateMotor(U8 speed, U8 factorFrom255)
{
	U16 resultSpd = speed;
	resultSpd *= factorFrom255;
	resultSpd /= 255;
	return (U8)resultSpd;
}
