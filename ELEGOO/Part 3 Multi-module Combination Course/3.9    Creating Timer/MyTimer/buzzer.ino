void buzzer_init(const uint8_t buzzer)
{
  pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output
 }


void time_out()
{
  while(flag_begin && number==0)
   {
     delay(100);
     digitalWrite(BUZZER,HIGH); 
     digitalWrite(LED,LOW);
     delay(100);
     digitalWrite(BUZZER,LOW);
     delay(100);
     digitalWrite(LED,HIGH);
   }    
}
