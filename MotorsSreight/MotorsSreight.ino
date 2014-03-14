#include <base.h>
#include <Motors_I.h>

void setup()
{
  InitMotors();
}

void loop()
{
  Turn(Right, 126);
}
