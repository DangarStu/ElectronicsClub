#include  <LiquidCrystal.h>
#include <movingAvg.h>

LiquidCrystal lcd (7, 8, 9, 10, 11, 12);

int houseBankInput = 0;
float vout = 0.0;
float vin = 0.0;
float referenceVoltage = 5.015;
float Resistor1 = 100000.0; // resistance of R1 (100K)
float Resistor2 = 10000.0; // resistance of R2 (10K)
int value = 0;

movingAvg houseBank(10);

void setup()
{
   pinMode(houseBankInput, INPUT);
   lcd.begin(16, 2);
   lcd.print("HOUSE BATTERY BANK");
   
   // CLEAR THE ROLLING AVERAGE BUFFER
   houseBank.begin();
}

void loop()
{
   // READ THE VOLTAGE AT PIN A0
   houseBank.reading(readVoltage(houseBankInput));

   lcd.setCursor(0, 1);
   lcd.print(vin);
   lcd.print("VDC");
   delay(500);
}

float readVoltage(int inputChannel)
{
    long digitalRead = analogRead(inputChannel);

    float measuredVoltage = (digitalRead * referenceVoltage) / 1024.0;
    
    float calculatedVoltage = measuredVoltage / (Resistor2/(Resistor1+Resistor2)); 
   
    return (calculatedVoltage);
    
}
