#ifndef TIME_CLOCKS_H_
#define TIME_CLOCKS_H_

#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
#include "pitches.h"

#define RST_PIN   A1    
#define SS_PIN    10

void LCD_ShowDate(RTCDateTime dt);

DS3231 clock;
RTCDateTime dt;
LiquidCrystal lcd(2,A3,8,7,A2,4);
MFRC522 mfrc522(SS_PIN, RST_PIN);

int cnt=0;
int flag_start=1;
int16_t duration = 500; 

enum Mode{
  DISPLAY_MODE,
  INPUT_MODE,
}mode=DISPLAY_MODE;


typedef struct Staff
{
  byte m_uidData[10];
  String m_name;
  String m_number; 
  Staff* next;
}; 
Staff* staff = NULL;
Staff* head = NULL;
#endif
