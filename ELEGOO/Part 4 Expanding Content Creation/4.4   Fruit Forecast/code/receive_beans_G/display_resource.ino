void max7219_init(uint8_t bright)
{
  lc.shutdown(0,false);
  lc.clearDisplay(0);           //max7219 init
  lc.setIntensity(0, bright);
}

void enlarge_reduce_display()
{
   lc.clearDisplay(0);
   delay(er_show_speed);
   lc.setRow(0,4,B00011000);
   lc.setRow(0,3,B00011000);
   delay(er_show_speed);
   lc.clearDisplay(0);
   delay(er_show_speed);
   lc.setRow(0,5,B00111100);
   lc.setRow(0,4,B00100100);
   lc.setRow(0,3,B00100100);
   lc.setRow(0,2,B00111100);
   delay(er_show_speed);
   lc.clearDisplay(0);
   delay(er_show_speed); 
   lc.setRow(0,7,B00000000);
   lc.setRow(0,6,B01111110);
   lc.setRow(0,5,B01000010);
   lc.setRow(0,4,B01000010);
   lc.setRow(0,3,B01000010);
   lc.setRow(0,2,B01000010);
   lc.setRow(0,1,B01111110);
   lc.setRow(0,0,B00000000);
   delay(er_show_speed);
   lc.clearDisplay(0);
   delay(er_show_speed); 
   lc.setRow(0,7,B11111111);
   lc.setRow(0,6,B10000001);
   lc.setRow(0,5,B10000001);
   lc.setRow(0,4,B10000001);
   lc.setRow(0,3,B10000001);
   lc.setRow(0,2,B10000001);
   lc.setRow(0,1,B10000001);
   lc.setRow(0,0,B11111111);
   delay(er_show_speed);
   lc.clearDisplay(0);
   delay(er_show_speed); 
  }

void heart_display()
{
   lc.setRow(0,0,B00000000);
   lc.setRow(0,1,B01100110);
   lc.setRow(0,2,B11111111);
   lc.setRow(0,3,B11111111);
   lc.setRow(0,4,B11111111);
   lc.setRow(0,5,B01111110);
   lc.setRow(0,6,B00111100);
   lc.setRow(0,7,B00011000);
   
   delay(heart_show_speed);
   lc.clearDisplay(0);
   delay(heart_show_speed);
   lc.setRow(0,0,B00000000);
   lc.setRow(0,1,B00000000);
   lc.setRow(0,2,B00100100);
   lc.setRow(0,3,B01111110);
   lc.setRow(0,4,B01111110);
   lc.setRow(0,5,B00111100);
   lc.setRow(0,6,B00011000);
   lc.setRow(0,7,B00000000);
   delay(heart_show_speed);
   lc.clearDisplay(0);
   delay(heart_show_speed);
 }

void game_over_display()
{
  int g[8] = {B00000000,B01110000,B10000000,B10000000,B10110000,B10010000,B01110000,B00000000};
  int a[8]={B00000000,B01100000,B10010000,B10010000,B11110000,B10010000,B10010000};
  int m[8]={B00000000,B11111000,B10101000,B10101000,B10101000,B10101000,B10101000,B00000000};
  int e[8]={B00000000,B11110000,B10000000,B10000000,B11110000,B10000000,B11110000};
  int o[8]={B00000000,B01100000,B10010000,B10010000,B10010000,B10010000,B01100000};
  int v[8]={B00000000,B10000100,B10000100,B10000100,B10000100,B01001000,B00110000};
  int r[8]={B00000000,B10000000,B10000000,B10100000,B11010000,B10000000,B10000000};


  for(int i=0;i<4;i++)
  {
     delay(game_show_speed);
     lc.setRow(0,0,g[0]);
     lc.setRow(0,1,g[1]);
     lc.setRow(0,2,g[2]);
     lc.setRow(0,3,g[3]);
     lc.setRow(0,4,g[4]);
     lc.setRow(0,5,g[5]);
     lc.setRow(0,6,g[6]);
     lc.setRow(0,7,g[7]);
     g[0]=g[0]>>1;
     g[1]=g[1]>>1;
     g[2]=g[2]>>1;
     g[3]=g[3]>>1;
     g[4]=g[4]>>1;
     g[5]=g[5]>>1;
     g[6]=g[6]>>1;
     g[7]=g[7]>>1;
     delay(game_show_speed); 
     lc.clearDisplay(0);
     delay(game_show_speed);
  }


  for(int i=0;i<4;i++)
  {
     delay(game_show_speed);
     lc.setRow(0,0,a[0]);
     lc.setRow(0,1,a[1]);
     lc.setRow(0,2,a[2]);
     lc.setRow(0,3,a[3]);
     lc.setRow(0,4,a[4]);
     lc.setRow(0,5,a[5]);
     lc.setRow(0,6,a[6]);
     lc.setRow(0,7,a[7]);
     a[0]=a[0]>>1;
     a[1]=a[1]>>1;
     a[2]=a[2]>>1;
     a[3]=a[3]>>1;
     a[4]=a[4]>>1;
     a[5]=a[5]>>1;
     a[6]=a[6]>>1;
     a[7]=a[7]>>1;
     delay(game_show_speed); 
     lc.clearDisplay(0);
     delay(game_show_speed);
  }
  //******************************************

 
  for(int i=0;i<4;i++)
  {
     delay(game_show_speed);
     lc.setRow(0,0,m[0]);
     lc.setRow(0,1,m[1]);
     lc.setRow(0,2,m[2]);
     lc.setRow(0,3,m[3]);
     lc.setRow(0,4,m[4]);
     lc.setRow(0,5,m[5]);
     lc.setRow(0,6,m[6]);
     lc.setRow(0,7,m[7]);
     m[0]=m[0]>>1;
     m[1]=m[1]>>1;
     m[2]=m[2]>>1;
     m[3]=m[3]>>1;
     m[4]=m[4]>>1;
     m[5]=m[5]>>1;
     m[6]=m[6]>>1;
     m[7]=m[7]>>1;
     delay(game_show_speed); 
     lc.clearDisplay(0);
     delay(game_show_speed);
  }
  //******************************************


  for(int i=0;i<4;i++)
  {
     delay(game_show_speed);
     lc.setRow(0,0,e[0]);
     lc.setRow(0,1,e[1]);
     lc.setRow(0,2,e[2]);
     lc.setRow(0,3,e[3]);
     lc.setRow(0,4,e[4]);
     lc.setRow(0,5,e[5]);
     lc.setRow(0,6,e[6]);
     lc.setRow(0,7,e[7]);
     e[0]=e[0]>>1;
     e[1]=e[1]>>1;
     e[2]=e[2]>>1;
     e[3]=e[3]>>1;
     e[4]=e[4]>>1;
     e[5]=e[5]>>1;
     e[6]=e[6]>>1;
     e[7]=e[7]>>1;
     delay(game_show_speed); 
     lc.clearDisplay(0);
     delay(game_show_speed);
  }
  //******************************************

  //ending_music1();
  for(int i=0;i<4;i++)
  {
     delay(game_show_speed);
     lc.setRow(0,0,o[0]);
     lc.setRow(0,1,o[1]);
     lc.setRow(0,2,o[2]);
     lc.setRow(0,3,o[3]);
     lc.setRow(0,4,o[4]);
     lc.setRow(0,5,o[5]);
     lc.setRow(0,6,o[6]);
     lc.setRow(0,7,o[7]);
     o[0]=o[0]>>1;
     o[1]=o[1]>>1;
     o[2]=o[2]>>1;
     o[3]=o[3]>>1;
     o[4]=o[4]>>1;
     o[5]=o[5]>>1;
     o[6]=o[6]>>1;
     o[7]=o[7]>>1;
     delay(game_show_speed); 
     lc.clearDisplay(0);
     delay(game_show_speed);
  }
  ////******************************************

  //ending_music2();
  for(int i=0;i<4;i++)
  {
     delay(game_show_speed);
     lc.setRow(0,0,v[0]);
     lc.setRow(0,1,v[1]);
     lc.setRow(0,2,v[2]);
     lc.setRow(0,3,v[3]);
     lc.setRow(0,4,v[4]);
     lc.setRow(0,5,v[5]);
     lc.setRow(0,6,v[6]);
     lc.setRow(0,7,v[7]);
     v[0]=v[0]>>1;
     v[1]=v[1]>>1;
     v[2]=v[2]>>1;
     v[3]=v[3]>>1;
     v[4]=v[4]>>1;
     v[5]=v[5]>>1;
     v[6]=v[6]>>1;
     v[7]=v[7]>>1;
     delay(game_show_speed); 
     lc.clearDisplay(0);
     delay(game_show_speed);
  }
  
  //******************************************
   e[0]=e[0]<<5;
   e[1]=e[1]<<5;
   e[2]=e[2]<<5;
   e[3]=e[3]<<5;
   e[4]=e[4]<<5;
   e[5]=e[5]<<5;
   e[6]=e[6]<<5;
   e[7]=e[7]<<5;
 
  //ending_music1();
  for(int i=0;i<5;i++)
  {
     delay(game_show_speed);
     lc.setRow(0,0,e[0]);
     lc.setRow(0,1,e[1]);
     lc.setRow(0,2,e[2]);
     lc.setRow(0,3,e[3]);
     lc.setRow(0,4,e[4]);
     lc.setRow(0,5,e[5]);
     lc.setRow(0,6,e[6]);
     lc.setRow(0,7,e[7]);
     e[0]=e[0]>>1;
     e[1]=e[1]>>1;
     e[2]=e[2]>>1;
     e[3]=e[3]>>1;
     e[4]=e[4]>>1;
     e[5]=e[5]>>1;
     e[6]=e[6]>>1;
     e[7]=e[7]>>1;
     delay(game_show_speed); 
     lc.clearDisplay(0);
     delay(game_show_speed);
  }
  ////******************************************

  ending_music2();
  for(int i=0;i<4;i++)
  {
     //delay(game_show_speed);
     lc.setRow(0,0,r[0]);
     lc.setRow(0,1,r[1]);
     lc.setRow(0,2,r[2]);
     lc.setRow(0,3,r[3]);
     lc.setRow(0,4,r[4]);
     lc.setRow(0,5,r[5]);
     lc.setRow(0,6,r[6]);
     lc.setRow(0,7,r[7]);
     r[0]=r[0]>>1;
     r[1]=r[1]>>1;
     r[2]=r[2]>>1;
     r[3]=r[3]>>1;
     r[4]=r[4]>>1;
     r[5]=r[5]>>1;
     r[6]=r[6]>>1;
     r[7]=r[7]>>1;
     delay(game_show_speed); 
     lc.clearDisplay(0);
     delay(game_show_speed);
  }
  ////******************************************
  }
   
   void win_display()
 {
   int i=3;
  while(i--)
  {
  win_music();
  lc.setRow(0,0,B11100111);
  lc.setRow(0,1,B11100111);
  lc.setRow(0,2,B11100111);
  lc.setRow(0,5,B01111110);
  lc.setRow(0,6,B00111100);
  lc.setRow(0,7,B00011000);
  win_light_effect();
  lc.setRow(0,0,B00000000);
  lc.setRow(0,1,B00000000);
  lc.setRow(0,2,B00000000);
  lc.setRow(0,5,B00000000);
  lc.setRow(0,6,B00000000);
  lc.setRow(0,7,B00000000);
  win_light_effect();
  lc.setRow(0,1,B01000010);
  lc.setRow(0,2,B10100101);
  lc.setRow(0,5,B01000010);
  lc.setRow(0,6,B00100100);
  lc.setRow(0,7,B00011000);
  win_music();
  lc.setRow(0,0,B00000000);
  lc.setRow(0,1,B00000000);
  lc.setRow(0,2,B00000000);
  lc.setRow(0,5,B00000000);
  lc.setRow(0,6,B00000000);
  lc.setRow(0,7,B00000000);
  }
 }

  
