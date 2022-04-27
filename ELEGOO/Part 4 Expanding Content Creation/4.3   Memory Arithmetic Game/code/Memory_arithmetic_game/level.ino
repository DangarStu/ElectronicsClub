void level_choose()
{
 
    while(menu_flag)// Enter the Difficulty Selection Interface at the End or Beginning
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" level choose:");
      lcd.setCursor(0,1);
      lcd.print("   level:");
      delay(100);// The above is the difficulty of choosing the interface
 
       if (irrecv.decode(&results)) // When the key is pressed
       {
          translateIR_level();
          irrecv.resume(); // receive the next value
        }  
    }
}

void translateIR_level()
{
 switch(results.value)// Determine which key is pressed
  {
    case BTN_1: menu_flag=0;      //no longer display menu.
                lcd.print("1");delay(2000);
                lcd.clear();
                remrun_flag=1;   // Begin to Enter Difficulty 1 Memory Game
                strcpy(buf,empty); break;  // Clear the "1" display you just entered
    case BTN_2: menu_flag=0;lcd.print("2");delay(2000);   // Choose Difficulty 2, Write as Difficulty 1
    lcd.clear();addrun_flag=1;strcpy(buf,empty);break;
    case BTN_3: menu_flag=0;lcd.print("3");delay(2000);  // Choose Difficulty 3, Write as Difficulty 1
    lcd.clear();mulrun_flag=1;strcpy(buf,empty); break;   
    default:
    lcd.clear(); 
    lcd.setCursor(0,0);
    lcd.print("you should ");
    lcd.setCursor(0,1);
    lcd.print("write 1/2/3");
    delay(2000);
    lcd.clear(); 
    results.value=0;
    break;
   } 
  }
