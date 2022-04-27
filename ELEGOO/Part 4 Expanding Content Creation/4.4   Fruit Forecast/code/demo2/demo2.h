#ifndef DEMO2_H
#define DEMO2_H
#include "LedControl.h"
#include "Wire.h"
/*Pin******************************************************************************************************************/
/*max 7219*/
LedControl lc=LedControl(13,7,8,1);//max7219 pin definition

/*variable definition******************************************************************************************************************/
int16_t bean_flick_speed=50;
uint8_t bean_x = 0;     //Storage location: At which point16_t the bean falls on the x-axis
uint8_t bean_y = 0;     //Storage location: At which point16_t the bean falls on the y-axis 

/*function******************************************************************************************************************/
void max7219_init();


/*random_beans*/
void random_init();
void beans_init();
void pro_random_beans();
void beans_falling();


#endif
