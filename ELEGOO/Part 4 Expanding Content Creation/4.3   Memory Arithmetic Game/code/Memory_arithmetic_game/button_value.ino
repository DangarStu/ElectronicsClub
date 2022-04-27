void translateIR() // takes action based on IR code received
{
       switch(results.value)      
      {
      case BTN_RET:btn_ret();break;       // Clear the input number when pressing RET key
      case BTN_EQ: read_pre_buf();break;  //withdraw
      case BTN_0: if(input_digital_cnt<7)  
                  {
                    save_pre_buf();  //because we need to achieve the function of "BTN_EQ",so we must save the value we pressed always.
                    strcat(buf,"0");
                    //” The string splicing function in string.h will add "0" to form a new string, which can be referred to as the example above.
                    // Example: Enter "2" after 1 and then "5"
                    //                "2",    "21",       "125"
                  }break;              
      case BTN_1: if(input_digital_cnt<7)
                  {
                    save_pre_buf();
                    strcat(buf,"1");
                   } break;
      case BTN_2: if(input_digital_cnt<7)
                  {
                    save_pre_buf();
                    strcat(buf,"2");
                    }break;
      case BTN_3: if(input_digital_cnt<7)
                  {
                    save_pre_buf();
                    strcat(buf,"3");
                    } break;
      case BTN_4: if(input_digital_cnt<7)
                  {
                    save_pre_buf();
                    strcat(buf,"4");
                    }break;
      case BTN_5: if(input_digital_cnt<7)
                  {
                    save_pre_buf();
                    strcat(buf,"5");
                    }break;
      case BTN_6: if(input_digital_cnt<7)
                  {
                    save_pre_buf();
                    strcat(buf,"6");
                    }break;
      case BTN_7: if(input_digital_cnt<7)
                  {
                    save_pre_buf();
                    strcat(buf,"7");
                    }break;
      case BTN_8: if(input_digital_cnt<7)
                  {
                    save_pre_buf();
                    strcat(buf,"8");
                    }break;
      case BTN_9: if(input_digital_cnt<7)
                  {
                    save_pre_buf();
                    strcat(buf,"9");
                    }break; 
       
      case BTN_VOL:judge_TorF();break;   // Confirmation key, press to implement the corresponding algorithm
    }

  delay(200); 
}

void btn_ret() //RET key answer data clear
{
  clr_answer();
  strcpy(buf,empty);
  input_digital_cnt=0;
 }


void read_pre_buf() //Read the last key value
{
  input_digital_cnt--;
  if(btn_cnt>0)
  {
  btn_cnt--;
  clr_answer();
  strcpy(buf,pre_buf[btn_cnt]);
  }
  else if(0==btn_cnt)
  {
     clr_answer();strcpy(buf,empty);
   }
}

void save_pre_buf()//Save the last key we have input.
{
  input_digital_cnt++;
  if(save_buf_flag)
  {
  strcpy(pre_buf[btn_cnt],buf);
  btn_cnt++;
  }
  save_buf_flag=1;
}
