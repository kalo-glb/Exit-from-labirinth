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

#endif
