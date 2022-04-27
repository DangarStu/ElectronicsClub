void rgb_init()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
 // rgb_green();
}

void rgb_color()
{
  int redValue = 20;
  int greenValue = 0;

    for(int i = 0; i < 20; i += 1) 
  {
    wdt_reset();
    redValue -= 1;
    greenValue += 1;
    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
    delay(rgb_color_delay);
  }
}

void rgb_light()
{
  if(flag_alarm_set_ok)
     rgb_yellow();
  else
     rgb_green();
}

void rgb_green()
{
  analogWrite(RED, 0);
  analogWrite(GREEN, 33);
}

void rgb_yellow()
{
  analogWrite(RED, 33);
  analogWrite(GREEN, 33);
}

void close_rgb()
{
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
}
