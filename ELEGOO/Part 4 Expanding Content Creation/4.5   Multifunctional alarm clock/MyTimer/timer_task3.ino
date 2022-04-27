void task3_update_RTCtime()
{
   if(task3_cnt == 100)
  { 
    task3_cnt = 0;
    flag_100ms_update_clock=!flag_100ms_update_clock;
  }
}
