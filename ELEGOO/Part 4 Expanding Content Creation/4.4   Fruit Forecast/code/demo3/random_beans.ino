//to produce random beans
void random_init()
{randomSeed(analogRead(0));} //random init


void beans_init()
{bean_y = random(7);            
 bean_x=0;}

void pro_random_beans()//produce ramdon beans
{ 
   beans_init();
  for(bean_x=0;bean_x<=7;)
  { 
    update_Ac();
    Control_right();
    Control_left();
    game_init();
    beans_falling();
    } 
}

void beans_falling()
{ 
  lc.setLed(0,bean_x,7-bean_y,true);
  delay(bean_flick_speed);
  lc.setLed(0,bean_x,7-bean_y,false);
  delay(bean_flick_speed);
  delay(300);
  bean_x++;
}
