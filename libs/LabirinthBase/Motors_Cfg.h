#ifndef MOTORS_CFG
#define MOTORS_CFG
#include <base.h>

#define LSpeed 5
#define RSpeed 3
#define LMotorF 9
#define LMotorB 10
#define RMotorF 8
#define RMotorB 7

#define Forward 0
#define Back	1

void 	SetMotorDirection(U8 motor, U8 direction, U8 speed);
U8 		CompensateMotor(U8 speed, U8 factorFrom255);
void 	UpdateMotors(U8 leftSpeed, U8 leftDir, U8 rightSpeed, U8 rightDir);

#endif