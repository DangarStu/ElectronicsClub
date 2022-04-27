void T_voice_effect()
{tone(BUZZER, NOTE_F5, 500);}


void F_voice_effect()
{tone(BUZZER, NOTE_GS2, 500);}


void end_voice_effect()
{
  int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
  
  int thisNote;
  
  if(T_cnt==QUESTION_TOTAL_NUM)
  {
      for (thisNote = 8; thisNote >= 0; thisNote--) 
      {
        tone(BUZZER, melody[thisNote], 100);
        delay(100);
      }
  }
  else
  {
     for (thisNote = 0; thisNote < 8; thisNote++) 
     {
        tone(BUZZER, melody[thisNote], 100);
        delay(100);
     }
   }
}
