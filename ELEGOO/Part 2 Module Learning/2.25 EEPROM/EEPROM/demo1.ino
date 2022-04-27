void test1 (void)
{
  char company[7] = {"elegoo"};
  char company2[7] = {"0"};
  
  for(int i=0 ; i<6 ;i++ )
  {
  EEPROM.write(i,company[i]);
  }

   for(int i=0 ; i<6 ;i++ )
  {
   company2[i] = EEPROM.read(i);
  }

  Serial.print("company:");
  Serial.println(company2);
  Serial.println("***********************************************************");
}
