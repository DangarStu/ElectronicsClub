#ifndef DEMO4_H
#define DEMO4_H
#include "LedControl.h"
#include "pitches.h"
/*Pin******************************************************************************************************************/
/*max 7219*/
LedControl lc=LedControl(13,7,8,1);//max7219 pin definition

/*buzzer pin*/
const uint8_t BUZZER=3;

/*RGB pin*/
const uint8_t BLUE=5;
const uint8_t GREEN=6;
const uint8_t RED=9;

/*variable definition******************************************************************************************************************/
//buzzer melody definition
int16_t melody[] = {
NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int16_t duration = 500;  // 500 miliseconds

int16_t er_show_speed=150;   //enlarge_reduce_display speed
int16_t heart_show_speed=150;   
int16_t game_show_speed=80;
int16_t music_speed=100;
int16_t car_display_speed=85;

/*function******************************************************************************************************************/
void max7219_init();


/*display_resource*/
void max7219_init();
void enlarge_reduce_display();
void heart_display();
void game_over_display();
void win_display();

/*light effect*/
void RGB_init();
void hp3_light_effect();
void hp1_light_effect();
void hp2_light_effect();
void end_light_effect();
void close_light_effect();
void win_light_effect();

/*voice_resource*/
void ending_music1();
void ending_music2();
void start_music();
void success_receive_voice();
void fail_receive_voice();
void mid_click_voice();
void win_music();


#endif
