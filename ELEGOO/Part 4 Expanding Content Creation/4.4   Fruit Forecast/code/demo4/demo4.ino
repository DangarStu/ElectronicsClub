#include "LedControl.h"
#include "demo4.h"
#include "pitches.h"

void setup() 
{
  max7219_init();

  RGB_init();
}

void loop() {
  
 /*display_resource*/
  enlarge_reduce_display();
  heart_display();
  game_over_display();
  win_display();

/*light effect*/
  RGB_init();
  hp3_light_effect();
  hp1_light_effect();
  hp2_light_effect();
  end_light_effect();
  close_light_effect();
  win_light_effect();

/*voice_resource*/
  ending_music1();
  ending_music2();
  start_music();
  success_receive_voice();
  fail_receive_voice();
  mid_click_voice();
  win_music();

while(1);
}
