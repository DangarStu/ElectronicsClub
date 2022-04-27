void main_run()
{
   reminder_set();           // When entering the game, the first line shows "Begin counting!
   produce_question();       // Generate Random Numbers and Display Topics
   end_display();           // Show the end of the game, scoring interface
   if(irrecv.decode(&results)) // have we received an IR signal?
   {
      translateIR();       // After choosing the difficulty,the function is used to Record answers press the corresponding key to produce the effect
      irrecv.resume(); // receive the next value
    }  
}

void produce_question()   // after Question 5 does not produce random numbers
{
  if(var_flag&&(qut_cnt!=QUESTION_TOTAL_NUM))
  {
    var1 = random(999);
    var2 = random(999); 
    var3 = random(9999999); 
    var_flag=0;
  
    if(remrun_flag==0)  // When it's not the first level 
    {
    lcd.setCursor(0,1);
    lcd.print(var1);
    
      if(mulrun_flag)   //if is level 3
        lcd.print("X");
      if(addrun_flag)   //if is level 2
        lcd.print("+");
    
    lcd.print(var2);
    lcd.print("=");
    lcd.print(buf);
  
    delay(2000);
    lcd.clear();
    }
    
   if(remrun_flag)   // When it's  the first level 
  {
    lcd.setCursor(0,1);
    lcd.print(var3);
    delay(2000);
    lcd.clear();
   }
 }
   lcd.setCursor(0,1);
   lcd.print(buf);
}

void judge_TorF()
{
  input_digital_cnt=0;
  result=atoi(buf);
  
  if(mulrun_flag)  // Judge whether the multiplication answer is correct
  {
    if(result==var1*var2) correct();
    else  error();
  }

  if(addrun_flag) // Judging whether the additive answer is correct
  {
    if(result==var1+var2) correct();
       else  {error();}
  }

  if(remrun_flag) // Judging whether the answer to numeration is correct
  {
    if(result==var3)   correct();
       else  {error();}
  }
}

void error()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("sorry......");
  lcd.setCursor(0,1);  
  lcd.print("you are wrong");  // Display the content when the answer is wrong        
  F_voice_effect();           // Sound effect
  delay(555);
  var_flag=1;
  lcd.clear();
  btn_ret();                // Clear up the answers to the previous question
  btn_cnt=0;            
  qut_cnt++;        // Number of questions plus 1
}

void correct()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Congratulations!");
  lcd.setCursor(0,1);
  lcd.print("you got it right");
  T_light_effect();
  T_voice_effect();    
  var_flag=1;
  lcd.clear();
  btn_ret();
  btn_cnt=0;
  T_cnt++;
  qut_cnt++;
}
