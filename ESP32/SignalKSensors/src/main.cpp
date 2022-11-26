// Signal K application template file.
//
// This application demonstrates core SensESP concepts in a very
// concise manner. You can build and upload the application as is
// and observe the value changes on the serial port monitor.
//
// You can use this source file as a basis for your own projects.
// Remove the parts that are not relevant to you, and add your own code
// for external hardware libraries.

#include "sensesp/sensors/analog_input.h"
#include "sensesp/sensors/digital_input.h"
#include "sensesp/sensors/sensor.h"
#include "sensesp/signalk/signalk_output.h"
#include "sensesp/system/lambda_consumer.h"
#include "sensesp_app_builder.h"
#include "sensesp/transforms/analogvoltage.h"
#include "sensesp/transforms/curveinterpolator.h"
#include "sensesp/transforms/linear.h"
#include "sensesp/transforms/voltagedivider.h"

using namespace sensesp;

reactesp::ReactESP app;

class TemperatureInterpreter : public CurveInterpolator {
 public:

  TemperatureInterpreter(String config_path = "")
      : CurveInterpolator(NULL, config_path) {

    // Seed the CurveInterpolator with the resistances and temperatures from the
    // sensor datasheet.
    float data_points[23][2] = {
      {10, 5728}, {15, 4496}, {20, 3555}, {25, 2830}, {30, 2268}, {35, 1828}, {40, 1483},
      {45, 1210}, {50, 992}, {55, 819}, {60, 679}, {65, 566}, {70, 475}, {75, 400},
      {80, 338}, {85, 287}, {90, 244.8}, {95, 209.7}, {100, 180.3}, {105, 155.6},
      {110, 134.7}, {115, 117.1}, {120, 102.2}
    };

    clear_samples();

    for (int index=0; index < 23; index++) {
      add_sample(CurveInterpolator::Sample(data_points[index][0], data_points[index][1]));
    }
  }
};

// The setup function performs one-time application initialization.
void setup() {
#ifndef SERIAL_DEBUG_DISABLED
  SetupSerialDebug(115200);
#endif

  // Construct the global SensESPApp() object
  SensESPAppBuilder builder;
  sensesp_app = (&builder)
                    // Set a custom hostname for the app.
                    ->set_hostname("outboard")
                    // Optionally, hard-code the WiFi and Signal K server
                    // settings. This is normally not needed.
                    ->set_wifi("D-Link DVA-2800", "Landrover")
                    //->set_sk_server("192.168.10.3", 80)
                    ->get_app();

  // GPIO number to use for the analog input
  const uint8_t collantAnalogInputPin = 36;

  // Voltage sent into the voltage divider circuit that includes the analog
  // sender
  const float Vin = 3.3;
  // The resistance, in ohms, of the fixed resistor (R1) in the voltage divider
  // circuit
  const float R1 = 316.0;

  // Define how often (in milliseconds) new samples are acquired
  const unsigned int kAnalogInputReadInterval = 500;

  // Define the produced value at the maximum input voltage (3.3V).
  // A value of 3.3 gives output equal to the input voltage.
  const float kAnalogInputScale = 4096;

  // An AnalogInput gets the value from the microcontroller's AnalogIn pin,
  // which is a value from 0 to 1023.
  // ESP32 has many pins that can be used for AnalogIn, and they're
  // expressed here as the XX in GPIOXX.
  auto* analog_input = new AnalogInput(collantAnalogInputPin);

    // The "Signal K path" identifies the output of this sensor to the Signal K
  // network.
  // To find valid Signal K Paths that fits your need you look at this link:
  // https://signalk.org/specification/1.4.0/doc/vesselsBranch.html
  const char* sk_path = "coolant.outboard.temperature";

  // If you are creating a new Signal K path that does not
  // already exist in the specification, it is best to
  // define "metadata" that describes your new value. This
  // metadata will be reported to the server upon the first
  // time your sensor reports its value(s) to the server
  SKMetadata* metadata = new SKMetadata();
  metadata->description_ = "Coolant Temperature";
  metadata->display_name_ = "Coolant Temperature";
  metadata->short_name_ = "Coolant Temp";
  metadata->units_ = "C";

  /* Translating the number returned by AnalogInput into a temperature, and
     sending it to Signal K, requires several transforms. Wire them up in
     sequence:
     - convert the value from the AnalogIn pin into an AnalogVoltage()
     - convert voltage into ohms with VoltageDividerR2()
     - find the Kelvin value for the given ohms value with
     TemperatureInterpreter()
     - use Linear() in case you want to calibrate the output at runtime
     - send calibrated Kelvin value to Signal K with SKOutputNumber()
  */
  analog_input->connect_to(new AnalogVoltage())
      ->connect_to(new VoltageDividerR2(R1, Vin, "/coolant/temp/sender"))
      ->connect_to(new TemperatureInterpreter("/coolant/temp/curve"))
      ->connect_to(new Linear(1.0, 273.0, "/collant/temp/calibrate"))
      ->connect_to(
          new SKOutputFloat(sk_path, "/coolant/temp/sk", metadata));

  // Set highWaterAlarmDigitalOutputPin to high to activate the high water alarm.
  const uint8_t highWaterAlarmDigitalOutputPin = 15;
  pinMode(highWaterAlarmDigitalOutputPin, OUTPUT);


  // Read GPIO 14 every time it changes
  const uint8_t highWaterAlarmDigitalInputPin = 14;
  auto* highWaterSwitch =
      new DigitalInputChange(highWaterAlarmDigitalInputPin, INPUT_PULLUP, CHANGE);

  // Connect the digital input to a lambda consumer that prints out the
  // value every time it changes.
  highWaterSwitch->connect_to(new LambdaConsumer<bool>(
      [](bool switchOn) { 
        debugD("High water switch state changed: %d", switchOn);
        if (switchOn) {
          // Switch is on so turn the alarm on.
          digitalWrite(highWaterAlarmDigitalOutputPin, HIGH);
        } else {
           digitalWrite(highWaterAlarmDigitalOutputPin, HIGH); 
        }
      }));

  // Connect digital input 2 to Signal K output.
  highWaterSwitch->connect_to(new SKOutputBool(
      "sensors.high_water_alarm.value",          // Signal K path
      "/sensors/high_water_alarm/value",         // configuration path
      new SKMetadata("",                       // No units for boolean values
                     "High water alarm")  // Value description
      ));

  // Create another digital input, this time with RepeatSensor. This approach
  // can be used to connect external sensor library to SensESP!
  const uint8_t kDigitalInput2Pin = 13;
  const unsigned int kDigitalInput2Interval = 1000;

  // Configure the pin. Replace this with your custom library initialization
  // code!
  pinMode(kDigitalInput2Pin, INPUT_PULLUP);

  // Define a new RepeatSensor that reads the pin every 100 ms.
  // Replace the lambda function internals with the input routine of your custom
  // library.

  auto* digital_input2 = new RepeatSensor<bool>(
      kDigitalInput2Interval,
      [kDigitalInput2Pin]() { 
        return digitalRead(kDigitalInput2Pin); 
      });

  // Connect digital input 2 to Signal K output.
  digital_input2->connect_to(new SKOutputBool(
      "sensors.high_water_alarm.value",          // Signal K path
      "/sensors/high_water_alarm/value",         // configuration path
      new SKMetadata("",                       // No units for boolean values
                     "High water alarm")  // Value description
      ));

  // Start networking, SK server connections and other SensESP internals
  sensesp_app->start();
}

void loop() { app.tick(); }
