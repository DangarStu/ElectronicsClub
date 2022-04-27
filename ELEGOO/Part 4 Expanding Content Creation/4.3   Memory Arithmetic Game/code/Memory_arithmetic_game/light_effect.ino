void RGB_init()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  close_light_effect();
}

void close_light_effect()
{
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,0);
}

  
void T_light_effect()
{
  int i=3;
  while(i--)
  {
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,0);
  delay(100);
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,5);
  delay(100);
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN,0);
  }
}
