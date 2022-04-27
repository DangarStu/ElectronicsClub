#include "LedControl.h"
#include "Wire.h"
#include "demo1.h"

/*
  demo1:control car move.
*/

void setup() 
{  
  max7219_init();
  
   MPU_init();
}

void loop() {
  game_init();
  
  update_Ac();
  
  Control_right();
  
  Control_left();
  
  Serial.print(car[0]);
  Serial.print("\n");
}

void max7219_init()//max7219 init
{
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);           
}

void game_init() //car init
{
 lc.setRow(0,7,car[0]);
 lc.setRow(0,6,car[1]);
}
