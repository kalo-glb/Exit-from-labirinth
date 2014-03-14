#ifndef SENSORS_INTERFACE
#define SENSORS_INTERFACE

#include <base.h>

#define WallThreshhold 180

void 	ProcessSensors(void);
void	InitSensors(void);
double 	GetPIDInput(void);

U16 	GetForwardSensor(void);
U16		GetLeftSensor(void);
U16		GetRightSensor(void);

U8 		IsLeftDistRising();
U8 		IsRightDistRising();

#endif // SENSORS_INTERFACE
