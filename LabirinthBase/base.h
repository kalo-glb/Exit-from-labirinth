#ifndef LABIRINTH_BASE
#define LABIRINTH_BASE

#include <Arduino.h>

// Basic types
#define U8 	unsigned char
#define S8 	char
#define U16 unsigned int
#define S16	signed int
#define U32 unsigned long
#define S32 signed long

// Motors
#define Left  	0
#define Right 	1

#define PIDSetPoint 1200

// Tactile sensors
#define FTSen 8

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

// Debug
void printMotors(U8 motor, U8 direction, U8 speed);
void PrintSensors(U16 s1, U16 s2, U16 s3);

#endif
