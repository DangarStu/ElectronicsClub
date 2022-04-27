//www.elegoo.com
//2016.12.8

// define pins
#define BLUE 9
#define GREEN 6
#define RED 5
int pirPin = 12; // Input for HC-S501
int pirValue; // Place to store read PIR Value

void setup()
{
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

// main loop
void loop()
{
  
  pirValue = digitalRead(pirPin);
  Serial.println(digitalRead(pirPin));
  if (pirValue == 1) {
    for (int i = 0; i < 20; i++) {
      analogWrite(BLUE, 255);
      analogWrite(RED, 255);
      analogWrite(GREEN, 255);
      if (digitalRead(pirPin)) {
        i = 0;
      }
      delay(10);
    }

  }
  else {
    analogWrite(BLUE, 0);
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
  }


}
