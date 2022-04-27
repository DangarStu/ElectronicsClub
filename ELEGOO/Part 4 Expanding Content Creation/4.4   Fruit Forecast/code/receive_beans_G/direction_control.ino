void MPU_init()
{  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1  inner power management register of MPU6050
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  }

void update_Ac()
{ Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);//stop the twi
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  }

//to control your car turn right
void Control_right()
{
    if(AcY>5000)      
  {
        if(car[0]==B00000011)
      {
        car[0]=B00000111;
        car[1]=B00000101;
      }
       if(car[0]==B11000000)
         {
          car[0]=B00000011;
          car[1]=B00000010;
         }
         else{
          car[0]=car[0]<<1;
          car[1]=car[1]<<1;
         }
        lc.setRow(0,7,car[0]);
        lc.setRow(0,6,car[1]);
        delay(car_display_speed);
        lc.clearDisplay(0);
        delay(car_display_speed); 
  }
}

//to control your car turn left
   void Control_left()
{
     if(AcY<-5000)      
  {
       
       if(car[0]==B11000000)
       {
        car[0]=B11100000;
        car[1]=B10100000;
       }
       
       if(car[0]==B00000011)
         {
          beans_falling();
          car[0]=B11000000;
          car[1]=B01000000;
         }
         else
        { 
        car[0]=car[0]>>1;
        car[1]=car[1]>>1;
        }
        
        lc.setRow(0,7,car[0]);
        lc.setRow(0,6,car[1]);
        delay(car_display_speed);
        lc.clearDisplay(0);
        delay(car_display_speed);
  }
}
