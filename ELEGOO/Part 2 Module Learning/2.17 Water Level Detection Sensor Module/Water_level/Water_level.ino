//www.elegoo.com
//2016.12.9

int adc_id = 0;
int HistoryValue = 0;
char printBuffer[128];

void setup()
{
  Serial.begin(9600);
}

void loop()
{
    int value = analogRead(adc_id); // get adc value
/*&& (logical AND) operator truth table
false&&false=false
false&&true=false
true&&false=false
true&&true=true

|| (logical OR) operator truth table
false||false=false
false||true=true
true||false=true
true||true=true
print level when the change is greater than or less than 10。
*/
    if(((HistoryValue>=value) && ((HistoryValue - value) > 10)) || ((HistoryValue<value) && ((value - HistoryValue) > 10)))
    {
      sprintf(printBuffer,"ADC %d level is %d\n",adc_id, value);
    //Convert binary numbers "adc_id" and "value" into strings, and store the whole string "ADC "adc_id" level is "value"\n"in C.
      
      Serial.print(printBuffer);
      HistoryValue = value;
    }
}
