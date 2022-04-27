void MCU_timer_interrupt_init(unsigned long time2)
{
   MsTimer2::set(time2, timer2_interrupt); // 100ms period
   MsTimer2::start();
}

void timer2_interrupt()
{                                                               
   task1_press_continuously();  //task1 was run every 100 ms.            The "100"  is because "task1_cnt * TIMER_TIME = 2*50 = 100"                           
   task2_cout_down();           //task2 was run every about 1s(1050ms，Because there may be errors.).  The "1050" is because "task2_cnt * TIMER_TIME = 50*21 = 1050"        
   task3_update_RTCtime();      //task3 was run every about 200 ms.      The "200"  is because "task3_cnt * TIMER_TIME = 4*50 = 200" 
   task_reset();                //reset was run every about 5s(5250ms).  The "5250" is because "waiting_time_cnt * TIMER_TIME = 105*50 = 5250"

   task1_cnt++;
   task2_cnt++;
   task3_cnt++;
}


void task_reset()
{
  if(waiting_time_cnt)
    {
      waiting_time_cnt++;
      }
  
  if(waiting_time_cnt==105)
    {
     rgb_light();
     function_clock=1;
     flag_year = 0; 
     flag_month = 0;
     press_cnt = 0;
     flag_temperature=0;
     flag_humidity=0;
     waiting_time_cnt=0;
     flag_alarm = 1;
     flag_alarm_set = 0;
    }    
}
