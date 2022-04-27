#include "Time_clocks.h"
#include "PinChangeInt.h"

String name[] = {"xiaoou", "xiaoou2", "xiaoou3", "xiaoou4", "elegoo3", "elegoo4"};
String number[] = {"1", "2", "3", "4", "5", "6"};

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  clock.begin();
  clock.setDateTime(__DATE__, __TIME__);
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card
  pinMode(A0, INPUT_PULLUP);
  attachPinChangeInterrupt(A0, button_choose_interrupt, FALLING );
}

void loop() {
  Start_interface();
  Mode_Choose(mode);
}

void Mode_Choose(int mode)
{
  switch (mode)
  {
    case DISPLAY_MODE:
      LCD_ShowDate(clock.getDateTime());
      Data_Display();
      delay(100);
      break;
    case INPUT_MODE:
      lcd.setCursor(3, 0);
      lcd.print("Input Mode");
      lcd.setCursor(3, 1);
      lcd.print("Swipe card.");
      if (cnt < (sizeof(name) / sizeof(String)))
      {
        Data_Input(name[cnt], number[cnt]);
      }
      delay(100); break;
    default: break;
  }
}

void Start_interface()
{
  if (flag_start == 1)
  {
    lcd.setCursor(3, 0);
    lcd.print("Starting up..");
    delay(2000);
    flag_start = 0;
    lcd.clear();
  }
}


void Data_Input(String name, String number)
{
  if (UID_Check())
  {
    Staff** tmp = &staff;

    if (*tmp == NULL)
    {
      *tmp = new Staff;
      head = *tmp;
    }
    else
    {
      if (UID_Compare(*tmp))
      { //Serial.print("ssssssssss:");
        return;
      }

      if ((*tmp)->next == NULL)
      {
        (*tmp)->next = new Staff;
        (*tmp) = (*tmp)->next;
      }
      else
      {
        while ((*tmp)->next != NULL)
        {
          (*tmp) = (*tmp)->next;
        }
        (*tmp)->next = new Staff;
        (*tmp) = (*tmp)->next;
      }
    }

    for (int i = 0; i < mfrc522.uid.size; i++)
    {
      (*tmp)->m_uidData[i] = mfrc522.uid.uidByte[i];


    }
    Serial.println();
    (*tmp)->m_name = name;
    (*tmp)->m_number = number;
    //Serial.print("staff:"); Serial.println(name);
    (*tmp)->next = NULL;

    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print((*tmp)->m_name);
    lcd.setCursor(3, 1);
    lcd.print("OK !!");
    delay(1000);
    lcd.clear();
    //    lcd.setCursor(3, 0);
    //    lcd.print("Input Mode");
    //    lcd.setCursor(3, 1);
    //    lcd.print("Swipe card.");
    tone(3, NOTE_F5, duration);
    cnt++;
  }
}

//Staff* Data_Modify(Staff* head, String name, String number)
//{
//  if (UID_Check())
//  {
//    Staff* tmp = head;
//    while (tmp != NULL)
//    {
//      if (UID_Compare(tmp))
//      {
//        tmp->m_name = name;
//        tmp->m_number = number;
//      }
//      tmp = tmp->next;
//    }
//    return head;
//  }
//}

void Data_Display()
{
  if (UID_Check())
  {
    Staff* tmp = head;

    while (tmp != NULL)
    {
      if (UID_Compare(tmp))
      {
        tone(3, NOTE_F5, duration);
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print(tmp->m_name);
        lcd.setCursor(3, 1);
        lcd.print(tmp->m_number);
        dt = clock.getDateTime();
        Serial.print("$");
        Serial.print(tmp->m_number);
        Serial.print(",");
        Serial.print(tmp->m_name);
        Serial.print(",");
        Serial.print(dt.year);
        Serial.print(".");
        Serial.print(dt.month);
        Serial.print(".");
        Serial.print(dt.day);
        Serial.print(",");
        Serial.print(dt.hour);
        Serial.print(":");
        Serial.print(dt.minute);
        Serial.print(":");
        Serial.print(dt.second);
        Serial.print("%");
        delay(2000);
      }
      tmp = tmp->next;
    }
  }
}

bool UID_Compare(Staff* tmp)
{
  int sum = 0;
  for (int i = 0; i < mfrc522.uid.size; i++)
  {
    sum += tmp->m_uidData[i] - mfrc522.uid.uidByte[i];
  }
  if (0 == sum)
  {
    return true;
  }
  else
    return false;
}

void LCD_ShowDate(RTCDateTime dt)
{
  lcd.setCursor(3, 0);
  lcd.print(dt.year);   lcd.print(".");
  lcd.print(dt.month);  lcd.print(".");
  lcd.print(dt.day);

  lcd.setCursor(3, 1);
  lcd.print(dt.hour);   lcd.print(":");
  lcd.print(dt.minute); lcd.print(":");
  lcd.print(dt.second);
  if (dt.second == 0 || dt.second > 59)
  {
    lcd.setCursor(10, 1);
    lcd.print(" ");
  }
}

bool UID_Check()
{
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return false;
  }

  return true;
}
