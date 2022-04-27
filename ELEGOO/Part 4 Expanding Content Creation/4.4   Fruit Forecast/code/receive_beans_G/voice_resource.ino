void ending_music1()
{
  tone(BUZZER, melody[2], duration);
  delay(music_speed);
  tone(BUZZER, melody[2], duration);
  delay(music_speed);
  tone(BUZZER, melody[1], duration);
  delay(music_speed);
  tone(BUZZER, melody[2], duration);
  delay(music_speed);
  tone(BUZZER, melody[2], duration);
  delay(music_speed);
  }

void ending_music2()
{
  tone(BUZZER, melody[5], duration);
  delay(music_speed);
  tone(BUZZER, melody[2], duration);
  delay(music_speed);
  tone(BUZZER, melody[3], duration);
  delay(music_speed);
  tone(BUZZER, melody[1], duration);
  delay(music_speed);
  tone(BUZZER, melody[2], duration);
  delay(music_speed);
  }

void start_music()
{
  tone(BUZZER, melody[3], duration);
  delay(music_speed);
  tone(BUZZER, melody[5], duration);
  delay(music_speed);
  tone(BUZZER, melody[3], duration);
  delay(music_speed);
  tone(BUZZER, melody[2], duration);
  delay(music_speed);
  tone(BUZZER, melody[1], duration);
  delay(music_speed);
   }

   
void success_receive_voice()
{
  tone(BUZZER, NOTE_F5, duration);
  }

  void fail_receive_voice()
{
  tone(BUZZER, NOTE_GS2, duration);
  }

void mid_click_voice()
{
  tone(BUZZER, melody[4], duration);
  }

  void win_music()
{
  int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
  int thisNote;
  for (thisNote = BUZZER; thisNote >=0; thisNote--) 
   {
    tone(BUZZER, melody[thisNote], 100);
    delay(100);
    }
}
