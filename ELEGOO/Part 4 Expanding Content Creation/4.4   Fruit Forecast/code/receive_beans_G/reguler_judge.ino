void case_run()
{
  fail_receive_voice();

  switch(hp_cnt)
  {
    case 0: hp_cnt0(); break;
    case 1: hp_cnt1(); break;
    case 2: hp_cnt2(); break;
  }
  
    hp_cnt++;
}

void case_ending_judge()
{
   if(bean_x>7)//When the beans fall to the last grid
  {
    switch(bean_y)//Determine which column is the last grid
    {
      case x1:if(car[0]!=x[bean_y]) {case_run();}
                else {success_receive_voice();
                      beans_received_num++; } break;
                
      case x2:if(car[0]!=x[bean_y]) {case_run();}
                 else {success_receive_voice();
                       beans_received_num++;} break;
              
      case x3:if(car[0]!=x[bean_y]) {case_run();} 
                 else {success_receive_voice();
                       beans_received_num++;} break;
             
      case x4:if(car[0]!=x[bean_y]) {case_run();} 
                 else {success_receive_voice();
                       beans_received_num++;} break;
              
      case x5:if(car[0]!=x[bean_y]) {case_run();} 
                 else {success_receive_voice();
                       beans_received_num++;}break;
              
      case x6:if(car[0]!=x[bean_y]) {case_run();} 
                 else {success_receive_voice();
                       beans_received_num++;}break;
              
      case x7:if(car[0]!=x[bean_y]) {case_run();} 
                 else {success_receive_voice();
                       beans_received_num++;}break;

      case x8:if(car[0]!=x[bean_y]) {case_run();} 
                 else {success_receive_voice();
                       beans_received_num++;}break;
      }
    }
  
  }

void hp_cnt0()
{hp1_light_effect();}

void hp_cnt1()
{hp2_light_effect();}

void hp_cnt2()
{
  if(beans_received_num>=BEANS_GOAL)
  {
    win_display();
    beans_received_num=0;
  }
  else
  {
     end_light_effect();
     end_interface();
     beans_received_num=0;
  }
 
  while(1)
    {update_Ac();
   if(AcZ<4000)
     break;}
     
  mid_click_voice();
  hp_cnt=0;
  hp3_light_effect();
  hp_cnt--;
}
