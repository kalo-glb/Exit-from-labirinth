#include <base.h>
#include <Motors_I.h>
#include <Motors_Cfg.h>

void ProcessMotors(U16 PIDResult)
{
	SetMotorDirection(Left, Forward, PIDResult);
	SetMotorDirection(Right, Forward, 255 - PIDResult);
}

void Turn(U8 direction, U8 speed)
{
	SetMotorDirection(direction, Forward, speed);
	SetMotorDirection(((direction == Left)? Right : Left), Back, speed);
}

void HardStop()
{
	SetMotorDirection(Left, Back, 100);
	SetMotorDirection(Right, Back, 100);
	delay(50);
	SetMotorDirection(Left, Back, 0);
	SetMotorDirection(Right, Back, 0);
}

void GoForward(U16 speed)
{
	SetMotorDirection(Left, Forward, speed);
	SetMotorDirection(Right, Forward, speed);
}

void GoBack(U16 speed)
{
	SetMotorDirection(Left, Back, speed);
	SetMotorDirection(Right, Back, speed);
}

void SetMotorDirection(U8 motor, U8 direction, U8 speed)
{
	//printMotors(motor, direction, speed);
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

U8 CompensateMotor(U8 speed, U8 factorFrom255)
{
	U16 resultSpd = speed;
	resultSpd *= factorFrom255;
	resultSpd /= 255;
	return (U8)resultSpd;
}