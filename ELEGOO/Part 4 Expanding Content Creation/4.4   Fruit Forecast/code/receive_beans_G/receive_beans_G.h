#ifndef RECEIVE_BEANS_G_H
#define RECEIVE_BEANS_G_H
#include "LedControl.h"
#include "pitches.h"
#include  "Wire.h"

/************************************************Pin***********************************************************/

/*RGB pin*/
const uint8_t BLUE=5;
const uint8_t GREEN=9;
const uint8_t RED=6;

/*led pin              din clk   cs*/
LedControl lc=LedControl(13,7,8,1);

/*MPU*/
const int16_t MPU_addr=0x68;  // I2C address
int16_t AcX,AcY,AcZ;

/*buzzer pin*/
const uint8_t BUZZER=3;

/************************************variable definition**************************************************************************/

//buzzer melody definition
int16_t melody[] = {
NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int16_t duration = 500;  // 500 miliseconds

//the car used to receive beans
uint8_t car[2]={B00000111,B00000101};

//the position where the bean  fall,which corresponding to the 8 points on th X axis of the screen
uint8_t bean[7] = {B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000};

//it is the position where the car can pick up the beans ,when the beans fall to the last grid.
uint8_t x[]={B00000011,B00000111,B00001110,B00011100,B00111000,B01110000,B11100000,B11000000};

uint8_t hp_cnt=0;       //Used to store the remaining blood volume.

uint8_t bean_x = 0;     //Storage location: At which point16_t the bean falls on the x-axis
uint8_t bean_y = 0;     //Storage location: At which point16_t the bean falls on the y-axis

uint8_t open_flag=0;    //the sign of opening animation
enum{x1,x2,x3,x4,x5,x6,x7,x8};//the same as the bean_y,but it used in "switch" sentence.

/********************************************function******************************************************************/

/*direction_control*/
void MPU_init();
void update_Ac();
void Control_right();
void Control_left();

/*display_resource*/
void max7219_init();
void enlarge_reduce_display();
void heart_display();
void game_over_display();
void win_display();

/*interface_resource*/
void start_interface();
void end_interface();
void game_init();

/*light effect*/
void RGB_init();
void hp3_light_effect();
void hp1_light_effect();
void hp2_light_effect();
void end_light_effect();
void close_light_effect();
void win_light_effect();

/*random_beans*/
void random_init();
void beans_init();
void pro_random_beans();
void beans_falling();

/*regular_judge*/
void case_run();
void case_ending_judge();
void hp_cnt0();
void hp_cnt1();
void hp_cnt2();

/*voice_resource*/
void ending_music1();
void ending_music2();
void start_music();
void success_receive_voice();
void fail_receive_voice();
void mid_click_voice();
void win_music();

#endif
