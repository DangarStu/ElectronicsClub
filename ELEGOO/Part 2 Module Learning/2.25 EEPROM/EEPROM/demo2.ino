template<typename T> 
void EEPROM_write(T data1,int address)
{ 
  union data{
     T my_type;
     char charbuf[];
  } data2;

  data2.my_type=data1;
    
   for(int i=address ; i<sizeof(data1) ;i++ )
  {
    EEPROM.write(i , data2.charbuf[i]);
  }
  
}

template<typename T> 
T EEPROM_read(T data ,int address)
{ 
    union data{
       T my_type;
       char charbuf[];
    } data2;

   for(int i=address ; i<sizeof(T) ;i++ )
  {
    data2.charbuf[i] = EEPROM.read(i);
  }
    return data2.my_type;
  
}
