//Opening animation settings
void start_interface()
{
   enlarge_reduce_display();
   start_music();
   heart_display();
  }

//Ending animation settings of game over
void end_interface()
{  
  enlarge_reduce_display();
  game_over_display();
 }

//the game begin offically
void game_init()
{
 while(0==open_flag)
 {
  open_flag=1;
  start_interface();
  hp3_light_effect();
  break;
 }

 lc.setRow(0,7,car[0]);
 lc.setRow(0,6,car[1]);//car init
  
}
