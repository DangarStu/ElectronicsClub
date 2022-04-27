#include "MsTimer2.h"
#define COM4 5
#define COM3 4
#define COM2 3
#define COM1 2

#define LATCH 12  
#define CLOCK 13 
#define DATA 8 
unsigned int number = 9999;
const static uint8_t num_buf[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void setup() 
{
  latch_init(LATCH,CLOCK,DATA); //74hC595 IC
  
  com_init(COM1,COM2,COM3,COM4); 
  
  //  com4   com3  com2  com1 
  // _________________________
  // |  9  |  9  |  9  |  9  |    ←Four Digital Seven Segment
  // ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣

  MsTimer2::set(100, timer2_interrupt); // 100ms period
  MsTimer2::start();
}

void timer2_interrupt()
{
  number--;
}

void loop() 
{
  display_num(number);
}
