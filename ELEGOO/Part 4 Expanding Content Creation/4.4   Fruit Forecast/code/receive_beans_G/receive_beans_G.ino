#include "receive_beans_G.h"
#include "LedControl.h"
#include "pitches.h"
#include  "Wire.h"

/***********************************************************************************************************************
 *                                          Receive Beans                                                                      *
 *                            Copyright (c)     Elegoo     //www.elegoo.com                                                                             
 *                            Author:           wee                                                               *                                                                                 *
 *                            Version number :  1.00                                                                                       *
 *                            Date :            2019.6.18                                                                                   *
 ***********************************************************************************************************************/

/*tips:You can change the speed to find the game difficulty that suits you 
 * and the animation playing experience that you like.
 */

int16_t bean_flick_speed=100;
int16_t er_show_speed=100;   //enlarge_reduce_display speed
int16_t heart_show_speed=100;   
int16_t game_show_speed=60;
int16_t music_speed=100;
int16_t car_display_speed=50;

uint8_t BRIGHT=2;              //you can change the Intensity of max7219
const uint8_t BEANS_GOAL=10;   //you can change the value to change the winning condition
uint8_t beans_received_num=0;
/*****************************************************************************************************************************/

void setup() 
{
  MPU_init();

  random_init();

  max7219_init(BRIGHT);
  
  RGB_init();
}

void loop() 
{
  game_init();
  
  pro_random_beans();
  
  case_ending_judge();
}
