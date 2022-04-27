#include "PinChangeInt.h"
#include "MsTimer2.h"
#include "clock.h"
#include "MyTimer.h"
#include "MyTimerDetails.h"
#include <Wire.h>
#include <dht_nonblocking.h>
#include <avr/wdt.h>
#include <EEPROM.h>

/***********************************************************************************************************************
 *                                             My Timer                                                                      *
 *                            Copyright (c)     Elegoo    //www.elegoo.com                                                                               
 *                            Author:           wee                                                              *                                                                                 *
 *                            Version number :  1.00                                                                                       *
 *                            Date :            2019.8.22                                                                                   
 *                                                                                                           *
 ***********************************************************************************************************************/


void setup()                        
{// ←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←                                                                                                            ←
 // ↓                                      //*******************************************************************  ↑
  //You_must_do_for_the_first_time();     // if you are the first time to upload the code you must delete the  '//' 
                                           // to initialize the time .
                                           // And then add the '//' again in the second time.
                                           //*******************************************************************                                       
  latch_init(LATCH,CLOCK,DATA); //74hC595
  
  com_init(COM1,COM2,COM3,COM4); 

  button_init(BUTTON_S,BUTTON_MS,BUTTON_CHOOSE,BUTTON_DISPLAY_CHANGE);

  button_interrupt_init(BUTTON_S,BUTTON_MS,BUTTON_CHOOSE,BUTTON_DISPLAY_CHANGE);

  MCU_timer_interrupt_init(TIMER_TIME); //set timer2 0.05s 
  
  buzzer_init(BUZZER);

  clock_init();

  rgb_init();
  
  wdt_enable(WDTO_120MS); 

  rgb_light();
}

void loop() 
{
   update_clock();
   
   update_dht11_value();
   
   interface_display();
   
   time_out();
   
   wdt_reset();
}

void You_must_do_for_the_first_time()
{
  clock_setDateTime(__DATE__, __TIME__);
  eeprom_clear_all(256);
}
