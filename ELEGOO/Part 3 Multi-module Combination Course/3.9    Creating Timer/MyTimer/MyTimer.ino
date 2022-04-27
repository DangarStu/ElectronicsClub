#include "PinChangelnt.h"   // ↑↑↑↑↑↑ all the define in there
#include "MsTimer2.h"
#include "MsTimer1.h"
#include "MyTimer.h"

/***********************************************************************************************************************
 *                  My Timer                                                                      *
 *        Copyright (c)     Elegoo                                                                                  
 *        author:           wee                                                               *                                                                                 *
 *        Version number :  1.00                                                                                       *
 *        Date :            2019.8.22                                                                                   *
 ***********************************************************************************************************************/


void setup() 
{
  latch_init(LATCH,CLOCK,DATA); //74hC595 IC
  
  com_init(COM1,COM2,COM3,COM4); 

  button_init(BUTTON_S,BUTTON_MS,BUTTON_CHOOSE);

  button_interrupt_init(BUTTON_S,BUTTON_MS,BUTTON_CHOOSE);

  MCU_timer_interrupt_init(150 ,1060); //set timer1 0.15s  timer2 1s 
  
  buzzer_init(BUZZER);

  led_init(LED);
}

void loop() 
{
 display_num(number);

 time_out();
}
