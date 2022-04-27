#include "PinChangelnt.h"
#include "MsTimer2.h"          
#include "avr/wdt.h"

int number = 0;
void setup() 
{
  Serial.begin(9600);
  
  // 4000ms triggered once  "timer2_interrupt" is the function name:you can set your favourite name  
  MsTimer2::set(4000, timer2_interrupt); 
  MsTimer2::start(); //timer2 interrupt begin

  pinMode(A3, INPUT_PULLUP); 
  attachPinChangeInterrupt(A3, button_interrupt, FALLING );

  wdt_enable(WDTO_1S);
  Serial.println("watchDog_interrupt triggered");
}

/*the function is the thing you want to do in timer2_interrupt,
and the function name is the favourite name you set in "MsTimer2::set(4000, timer2_interrupt); "*/
void timer2_interrupt()
{
  Serial.println("timer2_interrupt triggered");
}

void button_interrupt()
{
  Serial.println("button_interrupt triggered");
}

void loop() 
{
 Serial.print("we begin to count:");
 Serial.println(number++);
 delay(2000);
 wdt_reset();//we should feed the dog avoiding it reseted.
}
