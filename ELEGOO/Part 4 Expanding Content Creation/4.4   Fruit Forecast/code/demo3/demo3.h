#ifndef DEMO3_H
#define DEMO3_H
#include "LedControl.h"
#include "Wire.h"
/*Pin******************************************************************************************************************/
/*max 7219*/
LedControl lc=LedControl(13,7,8,1);//max7219 pin definition

/*MPU*/
const int16_t MPU_addr=0x68;  // I2C address
int16_t AcX,AcY,AcZ;

/*variable definition******************************************************************************************************************/
int16_t bean_flick_speed=50;
uint8_t bean_x = 0;     //Storage location: At which point16_t the bean falls on the x-axis
uint8_t bean_y = 0;     //Storage location: At which point16_t the bean falls on the y-axis 

//the car used to receive beans
uint8_t car[2]={B00000111,B00000101};
       // car[0]      car[1]

int16_t car_display_speed=85;

/*function******************************************************************************************************************/
void max7219_init();
void game_init();

/*random_beans*/
void random_init();
void beans_init();
void pro_random_beans();
void beans_falling();

/*direction_control*/
void MPU_init();
void update_Ac();
void Control_right();
void Control_left();

#endif
