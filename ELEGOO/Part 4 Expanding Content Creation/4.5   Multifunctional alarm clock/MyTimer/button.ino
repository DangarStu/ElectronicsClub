void button_init(const uint8_t button_s,const uint8_t button_ms,const uint8_t button_choose,const uint8_t button_display_change)
{
  pinMode(button_s, INPUT_PULLUP);  
  pinMode(button_ms, INPUT_PULLUP); 
  pinMode(button_choose, INPUT_PULLUP);
  pinMode(button_display_change, INPUT_PULLUP);
  }


void button_interrupt_init(const uint8_t button_s,const uint8_t button_ms,const uint8_t button_choose,const uint8_t button_display_change)
{
  attachPinChangeInterrupt(button_s, button_s_interrupt, FALLING );
  attachPinChangeInterrupt(button_ms, button_ms_interrupt, FALLING);
  attachPinChangeInterrupt(button_choose, button_choose_interrupt, FALLING );
  attachPinChangeInterrupt(button_display_change, button_display_change_interrupt, FALLING );
}


void button_s_interrupt()
{
  time_button_s=millis();
  
  if (ELIMINAT_THE_JITTER_OF_BUTTON_S)
  {
    flag_alarm = 0;
    
    clock_to_timer();

    waiting_time_cnt=1;
    
    flag_begin=0; 
    
    number +=100;
    
    last_time_button_s = time_button_s;

    if(function_clock || flag_year || flag_month || flag_temperature || flag_humidity )
     {  
        display_clear(); 
        number = 0;
     }
    else if(flag_alarm_set && number >=2359)
      { number = 0;}
      
    if (number >= 9900)
        number = 9999;
  }   
}

  void button_ms_interrupt()
{
  time_button_ms=millis();
  
  if (ELIMINAT_THE_JITTER_OF_BUTTON_MS)
  {  
     flag_alarm = 0;
  
     clock_to_timer();
     
     waiting_time_cnt=1;
     
     flag_begin=0;
     
     number +=1;

     if(function_clock || flag_year || flag_month || flag_temperature || flag_humidity )
     {  
        display_clear(); 
        number = 0;
     }
     else if(flag_alarm_set && number >=2359)
      { number = 0;}

     if(number%100 == 60 && number != 60)
       number = number/100*100+100;
       
     if(number==60)
        {number=100;}

     if (number >= 9900)
        number = 9999;

     last_time_button_ms = time_button_ms;
  }    
}

void button_choose_interrupt ()
{
  time_button_choose=millis();

 if ( ELIMINAT_THE_JITTER_OF_BUTTON_CHOOSE &&
     !(flag_year || flag_month || flag_temperature || flag_humidity) )
  { 
    waiting_time_cnt = 1;
    if(flag_alarm_ring)
    {
      flag_alarm_ring=0;
      function_clock=1;
      alarm_value = 0;
      eeprom_write_int(0,number);
      waiting_time_cnt=104;
      task2_cnt = 20;
      last_time_button_choose = time_button_choose;
      }
    else if( ( flag_year == 0 )        &&
             ( flag_month == 0 )       &&
             ( flag_temperature == 0  )&&
             ( flag_humidity == 0   )  && 
             ( function_clock )        && 
             ( flag_alarm == 1 )       && (flag_begin == 0) ) 
    {
      function_clock = 0;
      number = 0;
      alarm_value = 0;
      rgb_yellow();
      flag_alarm_set=1;
      last_time_button_choose = time_button_choose;     
     }
    else if(  ((flag_alarm_set && flag_alarm == 0) || (number == 0 && function_clock == 0)) && (flag_begin != 1))
     { 
       flag_alarm = 1;
       flag_alarm_set = 0;
       eeprom_write_int(0,number);
       alarm_value = eeprom_read_int(0);
       flag_alarm_set_ok = 1;
       EEPROM.write(3,flag_alarm_set_ok);
       function_clock = 1;
       waiting_time_cnt=104;
       last_time_button_choose = time_button_choose;
      }
    else if( flag_alarm_set != 1)
    {
      clock_to_timer();
      rgb_light();
      
      if(flag_begin)
        {
          waiting_time_cnt=104;
         }
        
      flag_begin=!flag_begin;
      
      last_time_button_choose = time_button_choose;
    }
  }
}

void clock_to_timer()
{
  if(function_clock)
  {
    function_clock=0;
    number=0;
   }
 }

 void button_display_change_interrupt()
 {
   uint8_t display_mode[]={0,1,2,3,4}; 

   time_button_display_change = millis();

   if (ELIMINAT_THE_JITTER_OF_BUTTON_DISPLAY_CHANGE)
  { 
     switch(display_mode[press_cnt++])
     {
      case DISPLAY_YEAR: 
                          display_year();
                          break;
      case DISPLAY_MONTH: 
                          display_month();
                          break;
      case DISPLAY_TIME: 
                          display_time();
                          break;
      case DISPLAY_TEMPERATURE: 
                          display_temperature();
                          break;
      case DISPLAY_HUNMIDITY: 
                          display_humidity();
                          break;
      }
  
      if(press_cnt>4)
         press_cnt=0;
  
      waiting_time_cnt=1;
  }
}

void display_year()
{
    flag_year = 1 ;
    flag_month = 0;
    flag_temperature=0;
    flag_humidity=0;
}

void display_month()
{
    flag_year = 0 ;
    flag_month = 1;
    flag_temperature=0;
    flag_humidity=0;
}

void display_time()
{
    flag_year = 0;
    flag_month = 0;
    flag_temperature=0;
    flag_humidity=0;
    function_clock=1;
}

void display_temperature()
{
    flag_year =0 ;
    flag_month = 0;
    flag_temperature=1;
    flag_humidity=0;
}

void display_humidity()
{
    flag_year = 0;
    flag_month = 0;
    flag_temperature=0;
    flag_humidity=1;
}

void display_clear()
{
    flag_year = 0;
    flag_month = 0;
    flag_temperature=0;
    flag_humidity=0;
    function_clock=0;
}
