#include "PinChangelnt.h"

int buttonApin = A1;
int time_buttonApin = 0;
int last_time_buttonApin = 0;
int i;
void setup() 
{ 
  Serial.begin(9600);
  pinMode(buttonApin, INPUT_PULLUP);
  attachPinChangeInterrupt(buttonApin,buttonApin_interrupt, FALLING );
}


void buttonApin_interrupt()
{
  time_buttonApin=millis();
 
  if (200 < (abs(time_buttonApin - last_time_buttonApin)))
  {
    Serial.print("buttonApin have been pressed");
    last_time_buttonApin = time_buttonApin;  //update the time you press
    Serial.println("              i:");
    Serial.println(i++);
  }   
}

void loop() 
{
}
