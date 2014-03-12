#define LSpeed 5
#define RSpeed 3
#define LMotorF 9
#define LMotorB 10
#define RMotorF 8
#define RMotorB 7

void setup()
{
  DDRD &= 3;
  DDRC = 0;
  DDRB = 0;
  
  pinMode(LSpeed, OUTPUT);
  pinMode(RSpeed, OUTPUT);
  pinMode(LMotorF, OUTPUT);
  pinMode(LMotorB, OUTPUT);
  pinMode(RMotorF, OUTPUT);
  pinMode(RMotorB, OUTPUT);
  
  PORTB = 0;
  PORTC = 0;
  PORTD = 0;
  
  digitalWrite(LSpeed, HIGH);
  digitalWrite(RSpeed, HIGH);
  
  //digitalWrite(LMotorF, HIGH);
}

void loop()
{
  delay(1000);
  digitalWrite(RMotorB, LOW);
  delay(1000);
  digitalWrite(LMotorF, HIGH);
  delay(3000);
  digitalWrite(LMotorF, LOW);
  delay(1000);
  digitalWrite(LMotorB, HIGH);
  delay(3000);
  digitalWrite(LMotorB, LOW);
  delay(1000);
  digitalWrite(RMotorF, HIGH);
  delay(3000);
  digitalWrite(RMotorF, LOW);
  delay(1000);
  digitalWrite(RMotorB, HIGH);
  delay(3000);
  
  
}
