#include <Sensors_I.h>
#include <Sensors_Cfg.h>
#include <base.h>

// Private data
static RolingAverage forwardFilt;
static RolingAverage leftFilt;
static RolingAverage rightFilt;
static U16 fSenVal = 0;
static U16 lSenVal = 0;
static U16 rSenVal = 0;

// Public functions
void InitSensors(void)
{
	  pinMode(LOSen, INPUT);
	  pinMode(FOSen, INPUT);
	  pinMode(ROSen, INPUT);
}

void ProcessSensors(void)
{
	  // read sensors
	RolingAvrgAddValue(analogRead(FOSen), &forwardFilt);
	RolingAvrgAddValue(analogRead(LOSen), &leftFilt);
	RolingAvrgAddValue(analogRead(ROSen), &rightFilt);
}

double GetPIDInput(void)
{
	double result = 0;
	
	lSenVal = RolingAvrgGetValue(&leftFilt);
	rSenVal = RolingAvrgGetValue(&rightFilt);
	
	result = (double)(((PIDSetPoint + lSenVal) - rSenVal) - 150);
	
	return result;
}

U16 GetForwardSensor(void)
{
	return RolingAvrgGetValue(&forwardFilt);
}

U16 GetLeftSensor(void)
{
	return RolingAvrgGetValue(&leftFilt);
}

U16 GetRightSensor(void)
{
	return RolingAvrgGetValue(&rightFilt);
}

// Private functions
void RolingAvrgAddValue(U16 value, RolingAverage *buffer)
{
	buffer->values[buffer->index] = value;
	buffer->index++;
	buffer->index = buffer->index % MaxValuesCnt;
}

U16 RolingAvrgGetValue(RolingAverage *buffer)
{
	U16 result = 0;
	for(U8 indx = 0; indx < MaxValuesCnt; indx++)
	{
		result += buffer->values[indx];
	}
	
	result /= MaxValuesCnt;
	return result;
}

void FillSensorBuf(S16 sensorId, RolingAverage *filter)
{
  U16 sen;
  for(U8 indx = 0; indx < MaxValuesCnt; indx++)
  {
    sen = analogRead(sensorId);
    RolingAvrgAddValue(sen, filter);
  }
}