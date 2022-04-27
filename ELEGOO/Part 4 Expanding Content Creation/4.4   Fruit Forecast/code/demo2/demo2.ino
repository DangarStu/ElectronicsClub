#include "LedControl.h"
#include "pitches.h"
#include "demo2.h"
/*
  demo2:beans falling
*/

void setup() {
  max7219_init();
  
  random_init();
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
