#ifndef SENSORS_INTERFACE
#define SENSORS_INTERFACE

#include <base.h>

#define WallThreshhold 150

void 	ProcessSensors(void);
void	InitSensors(void);
double 	GetPIDInput(void);

U16 	GetForwardSensor(void);
U16		GetLeftSensor(void);
U16		GetRightSensor(void);

#endif // SENSORS_INTERFACE