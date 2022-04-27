#define TIME 2

void interface_display()
{
  if (function_clock)
  {
    if (flag_year)
    {
      number = dt.year;
      display_num(number);
    }
    else if (flag_month)
    {
      number = dt.month * 100 + dt.day;
      display_num(number);
    }
    else if (flag_temperature)
    {
      number = temperature * 100;
      //clear_bit_display();
      temperature_display(number);
    }
    else if (flag_humidity)
    {
      number = humidity * 100;
      //clear_bit_display();
      humidity_display(number);
    }
    else
    {
      if (!flag_alarm_set)
        number = dt.hour * 100 + dt.minute;
      display_num(number);
    }
  }
  else
  {
    display_num(number);
  }
}

void latch_init(const uint8_t latch, const uint8_t clock, const uint8_t data)
{
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);
}

void com_init(const uint8_t com1 , const uint8_t com2 , const uint8_t com3 , const uint8_t com4 )
{
  pinMode(com1, OUTPUT);
  pinMode(com2, OUTPUT);
  pinMode(com3, OUTPUT);
  pinMode(com4, OUTPUT);
}

void display_num(uint16_t num)
{
  uint8_t com = 0;
  uint8_t polling = 0;
  uint8_t bit_num = 0;
  uint8_t num_place[4] = {0};

  if (num >= 1000 && num <= 9999)
  {
    polling = 4;
    bit_num = 3;
    num_place[3] = num / 1000;
    num_place[2] = num / 100 % 10;
    num_place[1] = num / 10 % 10;
    num_place[0] = num % 10;
    for (int i = 0; i < 4; i++)
    { clear_bit_display();
      choose_com(polling);
      polling--;
      if (2 == polling && !flag_year)
      {
        display2(num_place[bit_num--]);
      }
      else
        display(num_place[bit_num--]);
      delay(TIME);
    }
  }
  else if (num >= 100 && num < 1000)
  {
    polling = 3;
    bit_num = 2;
    num_place[2] = num / 100;
    num_place[1] = num / 10 % 10;
    num_place[0] = num % 10;
    for (int i = 0; i < 3; i++)
    { clear_bit_display();
      choose_com(polling);
      polling--;
      if (2 == polling && !flag_year)
      {
        display2(num_place[bit_num--]);
      }
      else
        display(num_place[bit_num--]);

      delay(TIME);
    }
  }
  else if (num >= 10 && num < 100)
  {
    polling = 2;
    bit_num = 1;
    num_place[1] = num / 10;
    num_place[0] = num % 10;

    if (flag_alarm_set || function_clock)
    {
      polling = 4;
      for (int i = 0; i < 2; i++)
      { clear_bit_display();
        choose_com(polling);
        polling--;
        display(0);
        delay(TIME);
      }
    }

    for (int i = 0; i < 2; i++)
    { clear_bit_display();
      choose_com(polling);
      polling--;
      if (2 == polling && !flag_year)
      {
        display2(num_place[bit_num--]);
      }
      else
        display(num_place[bit_num--]);
      delay(TIME);
    }
  }
  else if (num >= 0 && num <= 9)
  {
    uint8_t com = 0;
    uint8_t polling = 0;
    uint8_t bit_num = 0;
    uint8_t num_place[4] = {0};

    if (flag_alarm_set || function_clock)
    {
      polling = 4;
      for (int i = 0; i < 3; i++)
      { clear_bit_display();
        choose_com(polling);
        polling--;
        display(0);
        delay(TIME);
      }
    }

    num_place[0] = num % 10;
    choose_com(1);
    clear_bit_display();
    display(num_place[0]);
    delay(TIME);
  }
  else
  {
    num = 9999;
  }
}

void temperature_display(uint16_t num)
{
  uint8_t com = 0;
  uint8_t bit_num = 0;
  uint8_t num_place[4] = {0};

  if (num >= 1000 && num <= 9999)
  {
    bit_num = 3;
    num_place[3] = num / 1000;
    num_place[2] = num / 100 % 10;
    num_place[1] = num / 10 % 10;
    clear_bit_display();
    choose_com(4);

    display(num_place[bit_num--]);
    delay(TIME);
    clear_bit_display();
    choose_com(3);

    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, MSBFIRST, dht11_buf2[num_place[bit_num--]]);
    digitalWrite(LATCH, HIGH);
    delay(TIME);
    clear_bit_display();
    choose_com(2);

    display(num_place[bit_num--]);
    delay(TIME);
    clear_bit_display();
    choose_com(1);

    display(10);
    delay(TIME);
  }
}


void humidity_display(uint16_t num)
{
  uint8_t com = 0;
  uint8_t bit_num = 0;
  uint8_t num_place[4] = {0};

  if (num >= 1000 && num <= 9999)
  {
    bit_num = 3;
    num_place[3] = num / 1000;
    num_place[2] = num / 100 % 10;
    num_place[1] = num / 10 % 10;
    clear_bit_display();
    choose_com(4);

    display(num_place[bit_num--]);
    delay(TIME);
    clear_bit_display();
    choose_com(3);

    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, MSBFIRST, dht11_buf2[num_place[bit_num--]]);
    digitalWrite(LATCH, HIGH);
    delay(TIME);
    clear_bit_display();
    choose_com(2);

    display(num_place[bit_num--]);
    delay(TIME);
    clear_bit_display();
    choose_com(1);

    display(11);
    delay(TIME);
  }
}

void display(uint8_t num)
{
  //clear_bit_display();
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, num_buf[num]);
  digitalWrite(LATCH, HIGH);
  //digitalWrite(LATCH,LOW);
}

void display2(uint8_t num)
{
  //clear_bit_display();
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, num_buf_1[num]);
  digitalWrite(LATCH, HIGH);
  //digitalWrite(LATCH,LOW);
}

void choose_com(uint8_t com)
{
  switch (com)
  {
    case 1: choose_com1();

      break;
    case 2: choose_com2();

      break;
    case 3: choose_com3();

      break;
    case 4: choose_com4();

      break;
    default : break;
  }
}

void choose_com1()
{
  digitalWrite(COM1, LOW);
  digitalWrite(COM2, HIGH);
  digitalWrite(COM3, HIGH);
  digitalWrite(COM4, HIGH);
}

void choose_com2()
{
  digitalWrite(COM1, HIGH);
  digitalWrite(COM2, LOW);
  digitalWrite(COM3, HIGH);
  digitalWrite(COM4, HIGH);
}
void choose_com3()
{
  digitalWrite(COM1, HIGH);
  digitalWrite(COM2, HIGH);
  digitalWrite(COM3, LOW);
  digitalWrite(COM4, HIGH);
}
void choose_com4()
{
  digitalWrite(COM1, HIGH);
  digitalWrite(COM2, HIGH);
  digitalWrite(COM3, HIGH);
  digitalWrite(COM4, LOW);
}

void close_all_com()
{
  digitalWrite(COM1, LOW);
  digitalWrite(COM2, HIGH);
  digitalWrite(COM3, HIGH);
  digitalWrite(COM4, HIGH);

}

void clear_bit_display()
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, 0);
  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
  delay(TIME);
}


void clear_display()
{
  for (int i = 0; i < 4; i++)
  {
    choose_com(i);
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, MSBFIRST, 0);
    digitalWrite(LATCH, HIGH);
    digitalWrite(LATCH, LOW);
    delay(TIME);
  }
}
