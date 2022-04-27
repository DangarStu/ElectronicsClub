#ifndef MEMORY_ARITHMETIC_GAME_H
#define MEMORY_ARITHMETIC_GAME_H

#include "LiquidCrystal.h"
#include "pitches.h"
#include "IRremote.h"

/****************************************Pin*******************************************************************/
/*lcd1602 pin*/
LiquidCrystal lcd(2, A3,8, 7, A2, 4);

/*IR  pin*/
const uint8_t receiver = 12; 
IRrecv irrecv(receiver);     
decode_results results; 

/*RGB pin*/
const uint8_t BLUE=5;
const uint8_t GREEN=6;
const uint8_t RED=9;

/*buzzer pin*/
const uint8_t BUZZER=3;

/***********************************variable definition***************************************************************************/
/*Definition of keys*/
// Example: The equivalent of BTN_0 and 0xFF6897 makes the name look simpler and easier to understand.
#define BTN_0 0xFF6897 
#define BTN_1 0xFF30CF 
#define BTN_2 0xFF18E7 
#define BTN_3 0xFF7A85 
#define BTN_4 0xFF10EF 
#define BTN_5 0xFF38C7 
#define BTN_6 0xFF5AA5 
#define BTN_7 0xFF42BD 
#define BTN_8 0xFF4AB5 
#define BTN_9 0xFF52AD 
#define BTN_RET 0xFFB04F 
#define BTN_EQ 0xFF9867 
#define BTN_VOL 0xFFA857

#define QUESTION_TOTAL_NUM 5    //setting the number of question

/*Storage Difficulty 2.3 Addition (Multiplication) Subformula 1 and 2*/
uint16_t var1=0;
uint16_t var2=0;
/*Numbers to be memorized in difficulty 1*/
uint16_t var3=0;

// flag: As a switch
// variable flag, 
//which produces only one random number before the first calculation is completed
uint8_t var_flag=1;

//multiplier switch of the third level
uint8_t mulrun_flag=0;

// the adder switch of the second level
uint8_t addrun_flag=0;

//memory switch of the first level
uint8_t remrun_flag=0;

 // Select the difficulty interface marker to display (switch) this interface 
 //only at the end or beginning of the game
uint8_t menu_flag=1;

uint8_t save_buf_flag=0;

// Storing the number you input
char buf[16]={0};

// Stores the number each time you input it
//Example: pressing "2" after 1 and then "5"
//"1", "12", "125"
char pre_buf[16][16]={0};
uint16_t result=0;

//count the number of times
// When backspace is used, the number ordering for each input is stored in a two-dimensional array.
// Example: Enter "2" after 1 and then "5"
//                "1", "12", "125"
// btn_cnt         0     1     2
// btn_cnt is the ordinal number of a number in a two-dimensional array according to pre_buf [cnt]
// Pre_buf [0] is "1"
// pre_buf [1] is "12"
// pre_buf [2] is "125".
uint8_t btn_cnt=0;


uint8_t qut_cnt=0;  //the number of the maths question
uint8_t T_cnt=0;    //the right number of the answer
uint8_t input_digital_cnt=0;

//Withdrawal
byte empty[8] = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000};






#endif
