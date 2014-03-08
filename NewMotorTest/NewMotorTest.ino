void setup()
{
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
  PORTB = 0;
  PORTC = 0;
  PORTD = 0;
}

void loop()
{
  digitalWrite(8,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(5,HIGH);
}
