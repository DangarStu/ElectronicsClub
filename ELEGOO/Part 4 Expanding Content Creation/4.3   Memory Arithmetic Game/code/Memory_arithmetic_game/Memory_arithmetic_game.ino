#include "LiquidCrystal.h"
#include "pitches.h"
#include "IRremote.h"
#include "string.h"
#include "Memory_arithmetic_game.h"

/***********************************************************************************************************************
 *                                       Memory_arithmetic_game                                                                      *
 *                           Copyright (c)     Elegoo     //www.elegoo.com                                                                              
 *                           Author:           wee                                                                   *                                                                                   *
 *                           Version number :  1.00                                                                                       *
 *                           Date :            2019.6.18                                                                                   *
 ***********************************************************************************************************************/

void setup() {
  
  lcd.begin(16, 2);

  irrecv.enableIRIn(); 

  randomSeed(analogRead(0)); 

  RGB_init();
}

void loop() 
{
  
  level_choose();
 
  main_run();
  
}
