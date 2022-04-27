//    ↑↑↑the Definition of demo1
//                ↑↑ demo2
//www.elegoo.com
//2019.9.11
#include <EEPROM.h>

void setup() 
{
  Serial.begin(9600);
  test1();

  float a=3.14;     //'a' is the data you want to store in eeprom
  float a2=0;       //'a2' is the data you want to read from eeprom
  EEPROM_write(a,0); /* '0' is the address on eeprom
                        the range address on UNO eeprom:0~1023    
                        you can store your data between 0 to 1023 you like */
  Serial.print("float data:");
  Serial.println(EEPROM_read(a2,0));


  int b1=2000;
  int b2=0;
  EEPROM_write(b1,0);
  Serial.print("int data:");
  Serial.println(EEPROM_read(b2,0));
  

  long c1=65539;
  long c2=0;
  EEPROM_write(c1,0);
  Serial.print("long data:");
  Serial.println(EEPROM_read(c2,0));


  char d1[50]=__DATE__;
  char d2[50]="0";
  EEPROM_write(d1,0);
  Serial.print("string data:\n            elegoo:");
  Serial.println(EEPROM_read(d2,0));

}

void loop() 
{
 
}
