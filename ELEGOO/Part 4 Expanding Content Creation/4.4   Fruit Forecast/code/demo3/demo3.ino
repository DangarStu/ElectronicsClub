#include "LedControl.h"
#include "Wire.h"
#include "demo3.h"

/*
  demo2:receive beans
*/

void setup() {
  max7219_init();
  
  random_init();
  
  MPU_init();
}

void loop() {
  pro_random_beans();
  beans_falling();
}

void max7219_init()
{
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);           //max7219 init
}

void game_init()
{
 lc.setRow(0,7,car[0]);
 lc.setRow(0,6,car[1]);//car init
}
