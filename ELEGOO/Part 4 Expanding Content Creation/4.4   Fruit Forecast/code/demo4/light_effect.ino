void RGB_init()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}


void hp3_light_effect()
{
 analogWrite(RED, 0);
 analogWrite(BLUE, 0);
 analogWrite(GREEN,5);
}

void hp1_light_effect()
{
  uint8_t i=3;
  while(i--)
  {
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,0);
  delay(100);
  analogWrite(RED, 5);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,5);
  delay(100);
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,0);
  }
  analogWrite(RED, 5);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,5);
}


void hp2_light_effect()
{
  uint8_t i=3;
  while(i--)
  {
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,0);
  delay(100);
  analogWrite(RED, 5);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,0);
  delay(100);
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,0);
  }
  analogWrite(RED, 5);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,0);
}

void end_light_effect()
{
  uint8_t i=3;
  while(i--)
  {
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,0);
  delay(100);
  analogWrite(RED, 4);
  analogWrite(BLUE, 4);
  analogWrite(GREEN,4);
  delay(100);
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,0);
  }  
  }

void close_light_effect()
{
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,0);
  }

void win_light_effect()
{
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,0);
  delay(100);
  analogWrite(RED, 6);
  analogWrite(BLUE, 2);
  analogWrite(GREEN,1);
  delay(100); 
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,0);
  delay(100);
  }
