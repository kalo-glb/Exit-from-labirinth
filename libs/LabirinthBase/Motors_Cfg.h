#ifndef MOTORS_CFG
#define MOTORS_CFG
#include <base.h>

#define LMotorF 3
#define LMotorB 9
#define RMotorF 5
#define RMotorB 6

#define Forward 0
#define Back	1

void 	SetMotorDirection(U8 motor, U8 direction, U8 speed);
U8 		CompensateMotor(U8 speed, U8 factorFrom255);

#endif