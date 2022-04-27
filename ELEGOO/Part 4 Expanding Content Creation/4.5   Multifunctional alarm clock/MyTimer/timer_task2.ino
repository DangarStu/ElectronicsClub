void task2_cout_down()
{
    if(task2_cnt == 21)
  { 
    task2_cnt = 0;
    
    if(flag_begin)
   {    
      if (number > 9999)
         number = 9999;
    
      if(number%100 > 60 || number == 99)
         number = number/100*100+59;
  
      if(number>0) 
      {  
         number--;
         waiting_time_cnt=1;
      }

      if (number > 9999)
        number = 9999;
    
      if(number%100 > 60 || number == 99)
         number = number/100*100+59;
    } 
  }
}
