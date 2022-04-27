#include "LedControl.h"
#define BLUE 5
#define GREEN 6
#define RED 9
int Ball_Switch=2;
int i=100;
int j;
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 13 is connected to the DataIn 
 pin 11 is connected to LOAD(CS)
 pin 10 is connected to the CLK 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(13,7,8,1);
long randNumber;
/* we always wait a bit between updates of the display */
unsigned long delaytime1=100;
void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
  pinMode(Ball_Switch,INPUT);
  digitalWrite(Ball_Switch, HIGH);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  /*attachInterrupt(digitalPinToInterrupt(pin), ISR, mode)
  interrupt: the number of the interrupt. Allowed data types: int.
  pin: the Arduino pin number.
  ISR: the ISR to call when the interrupt occurs; this function must take no parameters and return nothing. This function is sometimes referred to as an interrupt service routine.
  mode: defines when the interrupt should be triggered. Four constants are predefined as valid values:
  LOW to trigger the interrupt whenever the pin is low,
  CHANGE to trigger the interrupt whenever the pin changes value
  RISING to trigger when the pin goes from low to high,
  FALLING for when the pin goes from high to low.
  The Due, Zero and MKR1000 boards allow also:
  HIGH to trigger the interrupt whenever the pin is high.
  */
  attachInterrupt(digitalPinToInterrupt(Ball_Switch),blink,RISING);
   lc.setIntensity(0,1);  //Set brightness
  Serial.begin(9600);
}
void writeRandomNumberOnMatrix() {
  byte Num_1[8]={B00000000,B00000000,B00011000,B00111100,B00111100,B00011000,B00000000,B00000000};//number 1
  byte Num_2[8]={B00000000,B00011000,B00011000,B00000000,B00000000,B00011000,B00011000,B00000000};//number 2
  byte Num_3[8]={B00000000,B00000110,B00000110,B00011000,B00011000,B01100000,B01100000,B00000000};//number 3
  byte Num_4[8]={B00000000,B01100110,B01100110,B00000000,B00000000,B01100110,B01100110,B00000000};//number 4
  byte Num_5[8]={B00000000,B01100110,B01100110,B00011000,B00011000,B01100110,B01100110,B00000000};//number 5
  byte Num_6[8]={B01100110,B01100110,B00000000,B01100110,B01100110,B00000000,B01100110,B01100110};//number 6
  switch (randNumber){
  /*
   * Play number
  */
  case 1:{
  lc.setRow(0,0,Num_1[0]);
  lc.setRow(0,1,Num_1[1]);
  lc.setRow(0,2,Num_1[2]);
  lc.setRow(0,3,Num_1[3]);
  lc.setRow(0,4,Num_1[4]);
  lc.setRow(0,5,Num_1[5]);
  lc.setRow(0,6,Num_1[6]);
  lc.setRow(0,7,Num_1[7]);
  /*Set rgb color*/
  analogWrite(RED, 238);
  analogWrite(GREEN,64);
  analogWrite(BLUE, 64);
  }break;
  case 2:{
  lc.setRow(0,0,Num_2[0]);
  lc.setRow(0,1,Num_2[1]);
  lc.setRow(0,2,Num_2[2]);
  lc.setRow(0,3,Num_2[3]);
  lc.setRow(0,4,Num_2[4]);
  lc.setRow(0,5,Num_2[5]);
  lc.setRow(0,6,Num_2[6]);
  lc.setRow(0,7,Num_2[7]);
  analogWrite(RED, 50);
  analogWrite(GREEN, 205);
  analogWrite(BLUE, 50);
  }break;
  case 3:{
  lc.setRow(0,0,Num_3[0]);
  lc.setRow(0,1,Num_3[1]);
  lc.setRow(0,2,Num_3[2]);
  lc.setRow(0,3,Num_3[3]);
  lc.setRow(0,4,Num_3[4]);
  lc.setRow(0,5,Num_3[5]);
  lc.setRow(0,6,Num_3[6]);
  lc.setRow(0,7,Num_3[7]);
  analogWrite(RED, 238);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 238);
  }break;
  case 4:{
  lc.setRow(0,0,Num_4[0]);
  lc.setRow(0,1,Num_4[1]);
  lc.setRow(0,2,Num_4[2]);
  lc.setRow(0,3,Num_4[3]);
  lc.setRow(0,4,Num_4[4]);
  lc.setRow(0,5,Num_4[5]);
  lc.setRow(0,6,Num_4[6]);
  lc.setRow(0,7,Num_4[7]);
  analogWrite(RED, 28);
  analogWrite(GREEN, 144);
  analogWrite(BLUE, 255);
  }break;
  case 5:{
  lc.setRow(0,0,Num_5[0]);
  lc.setRow(0,1,Num_5[1]);
  lc.setRow(0,2,Num_5[2]);
  lc.setRow(0,3,Num_5[3]);
  lc.setRow(0,4,Num_5[4]);
  lc.setRow(0,5,Num_5[5]);
  lc.setRow(0,6,Num_5[6]);
  lc.setRow(0,7,Num_5[7]);
  analogWrite(RED, 255);
  analogWrite(GREEN, 165);
  analogWrite(BLUE, 0);
  }break;
  case 6:{
  lc.setRow(0,0,Num_6[0]);
  lc.setRow(0,1,Num_6[1]);
  lc.setRow(0,2,Num_6[2]);
  lc.setRow(0,3,Num_6[3]);
  lc.setRow(0,4,Num_6[4]);
  lc.setRow(0,5,Num_6[5]);
  lc.setRow(0,6,Num_6[6]);
  lc.setRow(0,7,Num_6[7]);
  analogWrite(RED, 148);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 211);
  }break;
}
}
void loop() {
  lc.clearDisplay(0);
  // put your main code here, to run repeatedly:
  writeRandomNumberOnMatrix();
  delay(delaytime1);
  delaytime1=delaytime1+20;//The time for digital changes becomes larger
  /*delaytime1>300 Digital does not change*/
  while(delaytime1>300){
   writeRandomNumberOnMatrix();
   delay(delaytime1);
   Serial.println(delaytime1);
  }
  randNumber = random(1, 7);
}
/*
 *Interrupt.
*/
void blink(){
  delaytime1=100;
  Serial.println(delaytime1);
  }
