void buzzer_init(const uint8_t buzzer)
{
  pinMode(buzzer,OUTPUT);
 }


void time_out()
{
   while(flag_begin && number==0)
          time_out_effect(); 

   while(alarm_value == dt.hour*100+dt.minute)
          time_out_effect();
}

void time_out_effect()
{
    if(alarm_value == dt.hour*100+dt.minute)
    {
      flag_alarm_ring = 1; 
      flag_alarm_set = 0;
      flag_alarm_set_ok = 0;
      EEPROM.write(3,flag_alarm_set_ok);
     }
     clear_display();   
     rgb_color();
     digitalWrite(BUZZER,HIGH); 
     rgb_color();
     digitalWrite(BUZZER,LOW);
     rgb_color();
     rgb_light();
  }
