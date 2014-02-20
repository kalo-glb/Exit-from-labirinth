#ifndef SENSORS_CFG
#define SENSORS_CFG
#include <base.h>

// Optical sensors
#define ROSen A5
#define FOSen A3
#define LOSen A1

// Optical sensor filter
#define MaxValuesCnt 8
typedef struct tRolAvrg
{
	U16 values[MaxValuesCnt];
	U8  index;
} RolingAverage;

void 	RolingAvrgAddValue(U16 value, RolingAverage *buffer);
U16 	RolingAvrgGetValue(RolingAverage *buffer);
void 	FillSensorBuf(S16 sensorId, RolingAverage *filter);
U16		LineariseSensor(U16 filteredValue);

#endif