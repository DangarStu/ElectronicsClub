#include "Key.h"

void button_choose_interrupt ()
{
  time_button_choose = millis();

  if(ELIMINAT_THE_JITTER_OF_BUTTON_CHOOSE)
  {
    last_time_button_choose = time_button_choose;
    if(mode==DISPLAY_MODE)
    {
      mode=INPUT_MODE;
      lcd.clear();
     }
     else if(mode==INPUT_MODE)
     {
      mode=DISPLAY_MODE;
      lcd.clear();
      }
  }
}
