#include <base.h>


// SerDebug
#ifdef SERDEBUG


void printMotors(U8 motor, U8 direction, U8 speed)
{
	Serial.print("M: ");
	Serial.print(motor);
	Serial.print(" D: ");
	Serial.print(direction);
	Serial.print(" S: ");
	if(motor == 1)
	{
		Serial.print(speed);
	}
	else
	{
		Serial.print(speed);
		Serial.println();
	}
}

#endif