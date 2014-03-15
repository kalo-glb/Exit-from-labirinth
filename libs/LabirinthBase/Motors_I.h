#ifndef MOTORS_INTERFACE
#define MOTORS_INTERFACE
#include <base.h>

void ProcessMotors(U16 PIDResult);
void InitMotors();
//void HardStop();
void GoForward(U8 speed);
void GoBack(U8 speed);
void Turn(U8 direction, U8 speed);

typedef struct mot
{
    U8 leftSpeed;
    U8 leftDir;
    U8 rightSpeed;
    U8 rightDir;
} Motors;

#endif
