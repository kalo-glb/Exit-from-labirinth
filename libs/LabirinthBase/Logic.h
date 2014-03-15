#ifndef LOGICCONTROLS
#define LOGICCONTROLS

#include <base.h>

typedef enum tOpMode
{
	NoMode,
    GoingStreight,
    TurningLeft,
    TurningRight,
    TurnedLeft,
    TurnedRight
} OpMode;

void   ExecuteLeftTurn();
void   ExecuteRightTurn();
OpMode DetermineMode();
void   ExecuteMode(OpMode mode);
void   InitLogic();

void   StartTimer(U32 *timerAddr);
U8     IsTimerExpired(U32 timerAddr, U32 timerDelay);
U8     IsTimerStarted(U32 timerAddr);

#endif
