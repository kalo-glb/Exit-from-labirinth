#ifndef MOTORS_INTERFACE
#define MOTORS_INTERFACE
#include <base.h>

void ProcessMotors(U16 PIDResult);
void Turn(U8 direction, U8 speed);

#endif