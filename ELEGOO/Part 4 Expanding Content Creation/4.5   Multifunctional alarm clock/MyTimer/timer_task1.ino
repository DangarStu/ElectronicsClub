void task1_press_continuously()
{
     if(task1_cnt == 2)
  {
      task1_cnt = 0;
      time_timer=millis();

      task1_case1_button_ms_was_pressed_and_lasts_for_1000ms();
      task1_case2_button_s_was_pressed_and_lasts_for_1000ms();
  }
}

void task1_case1_button_ms_was_pressed_and_lasts_for_1000ms()
{
   if(BUTTON_MS_WAS_PRESSED_AND_LASTS_FOR_1000_MS)
 {
     number +=1;
     waiting_time_cnt=1;
     if(number%100 == 60 && number != 60)
        number = number/100*100+100;

     if(flag_alarm_set && number >=2359)
       {number = 0;}
     
     if(number==60)
        number=100;  
  }
}

void task1_case2_button_s_was_pressed_and_lasts_for_1000ms()
{
  if(BUTTON_S_WAS_PRESSED_AND_LASTS_FOR_1000_MS)
    {
       number +=100;
       waiting_time_cnt=1;

       if(flag_alarm_set && number >=2400)
       { number = 0;}
     }
}
