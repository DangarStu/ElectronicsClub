void reminder_set()
{
  lcd.setCursor(0,0);
   lcd.print("Begin counting!!");
  }

  
void clr_answer()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Begin counting!!");
  lcd.setCursor(0,1);
  }


void end_display()
{
  if(QUESTION_TOTAL_NUM==qut_cnt)
  {
      menu_flag=1;
      mulrun_flag=0;
      addrun_flag=0;
      remrun_flag=0;
      var_flag=1;
      qut_cnt=0;  
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("test ending");
      lcd.setCursor(0,1);
      lcd.print("   score:");
      lcd.print(T_cnt);
      //end_light_effect();
      end_voice_effect();
      T_cnt=0;
      delay(1000);
      lcd.clear();
    
    }
  }
