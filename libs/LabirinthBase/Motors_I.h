#ifndef MOTORS_INTERFACE
#define MOTORS_INTERFACE
#include <base.h>

void ProcessMotors(U16 PIDResult);
void HardStop();
void GoForward(U16 speed);
void GoBack(U16 speed);
void Turn(U8 direction, U8 speed);

#endif