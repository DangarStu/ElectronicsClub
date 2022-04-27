#ifndef DEMO1_H
#define DEMO1_H
#include "LedControl.h"
#include "Wire.h"
/*Pin******************************************************************************************************************/
/*max 7219*/
LedControl lc=LedControl(13,7,8,1);//max7219 pin definition

/*MPU*/
const int16_t MPU_addr=0x68;
int16_t AcX,AcY,AcZ;

/*******************************************************************************************************************/
//the car used to receive beans
uint8_t car[2]={B00000111,B00000101};
            // car[0]      car[1]
       
int16_t car_display_speed=50;

/*function******************************************************************************************************************/
void max7219_init();
void game_init();

/*direction_control*/
void MPU_init();
void update_Ac();
void Control_right();
void Control_left();

#endif
