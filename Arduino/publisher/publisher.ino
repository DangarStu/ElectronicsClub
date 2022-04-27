
#include <ArduinoMqttClient.h>
#include <WiFi.h>
#include "arduino_secrets.h"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org";
int        port     = 1883;
const char topic0[]  = "house_voltage";
const char topic1[]  = "starter_voltage";
const char topic2[]  = "12v_voltage";

//set interval for sending messages (milliseconds)
const long interval = 8000;
unsigned long previousMillis = 0;

int count = 0;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  // INITIALISE THE LCD SCREEN
  pinMode(houseBankInput, INPUT);
  lcd.begin(16, 2);
  lcd.print("HOUSE BATTERY BANK");
   
   // CLEAR THE ROLLING AVERAGE BUFFER
   houseBank.begin();
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();

  unsigned long currentMillis = millis();

    // THE VOLTAGES FROM A0, A1 and A2
    int Rvalue0 = analogRead(A0);
    int Rvalue1 = analogRead(A1);
    int Rvalue2 = analogRead(A2);

    Serial.print("Sending message to topic: ");
    Serial.println(topic0);
    Serial.println(Rvalue0);

    Serial.print("Sending message to topic: ");
    Serial.println(topic1);
    Serial.println(Rvalue1);

    Serial.print("Sending message to topic: ");
    Serial.println(topic2);
    Serial.println(Rvalue2);

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic0);
    mqttClient.print(Rvalue0);
    mqttClient.endMessage();

    mqttClient.beginMessage(topic1);
    mqttClient.print(Rvalue1);
    mqttClient.endMessage();

    mqttClient.beginMessage(topic2);
    mqttClient.print(Rvalue2);
    mqttClient.endMessage();

    Serial.println();

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
