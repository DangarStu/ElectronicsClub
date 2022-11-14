// This was used to read the popular GM coolant sensor 12146312 
// The serial print is for oil temperature change this as needed
// The sensor needed 2.2K and 550 ohm resistors in series
// No display options are used here other than serial print for testing
// This sketch uses analog pin 0 to read the sensor
// The serial rate was bumped up to 115200 from 9600
// Output is in fahrenheit

#include  <LiquidCrystal.h>
#include <movingAvg.h>
#include <math.h>         //loads the more advanced math functions

movingAvg coolant(10);

#define tempSensor  0

LiquidCrystal lcd (7, 8, 9, 10, 11, 12);

void setup() { 
  pinMode(tempSensor, INPUT);
  lcd.begin(16, 2);
  lcd.print("COOLANT TEMPERATURE");
   
  // CLEAR THE ROLLING AVERAGE BUFFER
  coolant.begin();       //This function gets called when the Arduino starts
  Serial.begin(9600);   //This code sets up the Serial port at 115200 baud rate
}
 
//Function to perform the fancy math of the Steinhart-Hart equation
float Thermister(int RawADC) {  
 float Temp;
 Temp = log(((10240000/RawADC) - 10000));
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 
 // Convert Kelvin to Celsius
 Temp = Temp - 273.15;              
 return Temp;
}
 
void loop() {                     
  //Create an integer variable
  int val;
                          
  //Variable to hold a temperature value
  double temp;   
           
  //Read the analog port 0 and store the value in val
  val=analogRead(tempSensor);
        
  //Runs the fancy math on the raw analog value
  coolant.reading(Thermister(val));   
  Serial.print ("Temp C: "); // Change this if monitoring another type of fluid
  Serial.println(temp);   //Print the value to the serial port
  lcd.setCursor(0, 1);
  lcd.print(coolant.getAvg());
  lcd.print("Deg C");
  delay(1000);            //Wait one second before we do it again
}
