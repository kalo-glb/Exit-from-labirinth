#ifndef LABIRINTH_BASE
#define LABIRINTH_BASE

#include <Arduino.h>

// Basic types
#define U8 	uint8_t
#define S8 	char
#define U16 uint16_t
#define S16	signed int
#define U32 uint32_t
#define S32 signed long

#define True  (U8)1
#define False (U8)0

// Motors
#define Left  	0
#define Right 	1

#define PIDSetPoint 1200
#define TurnDelay 350

// Logic
typedef enum tOpMode
{
	NoMode,
    GoingStreight,
    TurningLeft,
    TurningRight,
    TurnedLeft,
    TurnedRight
} OpMode;

/*
void StartTimer(U32 *timerAddr);
U8   IsTimerExpired(U32 timerAddr, U32 timerDelay);
U8   IsTimerStarted(U32 timerAddr);
*/

#endif
