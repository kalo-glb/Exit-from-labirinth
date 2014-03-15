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

typedef enum bools
{
    False = 0,
    True  = 1
} Boolean;

// Motors
typedef enum sides
{
    Left = 0,
    Right = 1
} Sides;

#define PIDSetPoint 1200
#define TurnDelay 350

#endif
