void button_init(const uint8_t button_s,const uint8_t button_ms,const uint8_t button_choose)
{
  pinMode(button_s, INPUT_PULLUP);  
  pinMode(button_ms, INPUT_PULLUP); 
  pinMode(button_choose, INPUT_PULLUP);
}


void button_interrupt_init(const uint8_t button_s,const uint8_t button_ms,const uint8_t button_choose)
{
  attachPinChangeInterrupt(button_s, button_s_interrupt, FALLING );
  attachPinChangeInterrupt(button_ms, button_ms_interrupt, FALLING);
  attachPinChangeInterrupt(button_choose, button_choose_interrupt, FALLING );
}


void button_s_interrupt()
{
  time_button_s=millis();
  
  if (200 < (abs(time_button_s - last_time_button_s)))
  {
    flag_begin=0; 
    
    number +=100;
    
    last_time_button_s = time_button_s;
    
    if (number >= 9900)
        number = 9999;
  }   
}

  void button_ms_interrupt()
{
  time_button_ms=millis();
  
  if (200 < (abs(time_button_ms - last_time_button_ms)))
  {
     flag_begin=0;
     
     number +=1;
     
     if(number%100 == 60 && number != 60)
       number = number/100*100+100;
       
     if(number==60)
        {number=100;}

     if(number >= 9900)
        number = 9999;

      last_time_button_ms = time_button_ms;
  }    
}

void button_choose_interrupt ()
{
   time_button_choose=millis();

   if (200 < (abs(time_button_choose - last_time_button_choose)))
    { 
      if(flag_begin)
        {
          number=0;
         }
         
      flag_begin=!flag_begin;
      
      last_time_button_choose = time_button_choose;
    }
}
