void latch_init(const uint8_t latch,const uint8_t clock,const uint8_t data)
{
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,OUTPUT);
 }

void com_init(const uint8_t com1 , const uint8_t com2 ,const uint8_t com3 ,const uint8_t com4 )
{
  pinMode(com1,OUTPUT);
  pinMode(com2,OUTPUT);
  pinMode(com3,OUTPUT);
  pinMode(com4,OUTPUT);
}

void display_num(uint16_t num)
{
  uint8_t com=0;
  uint8_t polling=0;
  uint8_t bit_num=0;
  uint8_t num_place[4]={0};
  
  if(num>=1000&&num<=9999)
  {
   polling=4;
   bit_num=3;
   num_place[3]=num/1000;
   num_place[2]=num/100%10;
   num_place[1]=num/10%10;
   num_place[0]=num%10;
     for(int i=0;i<4;i++)
     {
      choose_com(polling);
      polling--;
      display(num_place[bit_num--]);
      delay(5);
     }
   }
   else if(num>=100&&num<1000)
   {
    polling=3;
    bit_num=2;
    num_place[2]=num/100;
    num_place[1]=num/10%10;
    num_place[0]=num%10;
      for(int i=0;i<3;i++)
     {
      choose_com(polling);
      polling--;
      display(num_place[bit_num--]);
      delay(5);
     }
    }
    else if(num>=10&&num<100)
   {
    polling=2;
    bit_num=1;
    num_place[1]=num/10;
    num_place[0]=num%10;
       for(int i=0;i<2;i++)
       {
        choose_com(polling);
        polling--;
        display(num_place[bit_num--]);
        delay(5);
       }
    }
    else if(num>=0 && num<=9)
    { 
        num_place[0]=num%10;
        choose_com(1);
        display(num_place[0]);
        delay(5);
     }
    else
     {num=9999;}
 
  }


void display(uint8_t num)
{
  digitalWrite(LATCH,LOW);
  shiftOut(DATA,CLOCK,MSBFIRST,num_buf[num]);
  digitalWrite(LATCH,HIGH);
}

void choose_com(uint8_t com)
 {
  switch(com)
  {
    case 1:choose_com1();
            
            break;
    case 2:choose_com2();

            break;
   case 3:choose_com3();

            break;
    case 4:choose_com4();
            
            break;         
    default :break;
    }
  }

void choose_com1()
{
    digitalWrite(COM1,LOW);
    digitalWrite(COM2,HIGH);
    digitalWrite(COM3,HIGH);
    digitalWrite(COM4,HIGH);   
 }

 void choose_com2()
{
    digitalWrite(COM1,HIGH);
    digitalWrite(COM2,LOW);
    digitalWrite(COM3,HIGH);
    digitalWrite(COM4,HIGH);  
 }
 void choose_com3()
{
    digitalWrite(COM1,HIGH);
    digitalWrite(COM2,HIGH);
    digitalWrite(COM3,LOW);
    digitalWrite(COM4,HIGH);  
 }
 void choose_com4()
{
    digitalWrite(COM1,HIGH);
    digitalWrite(COM2,HIGH);
    digitalWrite(COM3,HIGH);
    digitalWrite(COM4,LOW);    
 }

 void clear_display()
{
  for(int i=0;i<4;i++)
 {
    choose_com(i);
    digitalWrite(LATCH,LOW);
    shiftOut(DATA,CLOCK,MSBFIRST,0);
    digitalWrite(LATCH,HIGH);
    digitalWrite(LATCH,LOW);
    delay(5);
  }
}
