//www.elegoo.com
//2016.12.9

#include "IRremote.h"
#include <Servo.h>
/* After including the corresponding libraries,
   we can use the "class" like "Servo" created by the developer for us.
   We can use the functions and variables created in the libraries by creating 
   objects like the following "myservo" to refer to the members in ".".*/

Servo myservo;
int receiver = 12; // Signal Pin of IR receiver to Arduino Digital Pin 12

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{

  switch(results.value)

  {

  //the "VOL-" button
  case 0xFF629D:  myservo.write(30);// move servos to center position -> 30°
  delay(1000); 
  break;
  
  //the "VOL+" button
  case 0xFFA857:   myservo.write(150);// move servos to center position -> 150°
  delay(1000);
  break;
  default: 
    Serial.println(" other button   ");

  }// End Case

  delay(500); // Do not get immediate repeat


} //END translateIR
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
  myservo.attach(11);//connect pin 11 with the control line(the middle line of Servo) 
 
}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */
