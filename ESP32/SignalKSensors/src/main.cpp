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

using namespace sensesp;

reactesp::ReactESP app;

// Prototypes
float convertAnalogToTemperature(unsigned int);

class TemperatureInterpreter : public CurveInterpolator {
 public:
  TemperatureInterpreter(String config_path = "")
      : CurveInterpolator(NULL, config_path) {
    // Populate a lookup table tp translate the ohm values returned by
    // our temperature sender to degrees Kelvin
    clear_samples();
    // addSample(CurveInterpolator::Sample(knownOhmValue, knownKelvin));
    add_sample(CurveInterpolator::Sample(10, 5728));
    add_sample(CurveInterpolator::Sample(15, 4496));
    add_sample(CurveInterpolator::Sample(20, 3555));
    add_sample(CurveInterpolator::Sample(25, 2830));
    add_sample(CurveInterpolator::Sample(30, 2268));
    add_sample(CurveInterpolator::Sample(35, 1828));
    add_sample(CurveInterpolator::Sample(40, 1483));
    add_sample(CurveInterpolator::Sample(45, 1210));
    add_sample(CurveInterpolator::Sample(50, 992));
    add_sample(CurveInterpolator::Sample(55, 819));
    add_sample(CurveInterpolator::Sample(60, 679));
    add_sample(CurveInterpolator::Sample(65, 566));
    add_sample(CurveInterpolator::Sample(70, 475));
    add_sample(CurveInterpolator::Sample(75, 400));
    add_sample(CurveInterpolator::Sample(80, 338));
    add_sample(CurveInterpolator::Sample(85, 287));
    add_sample(CurveInterpolator::Sample(90, 244.8));
    add_sample(CurveInterpolator::Sample(95, 209.7));
    add_sample(CurveInterpolator::Sample(100, 180.3));
    add_sample(CurveInterpolator::Sample(105, 155.6));
    add_sample(CurveInterpolator::Sample(110, 134.7));
    add_sample(CurveInterpolator::Sample(115, 117.1));
    add_sample(CurveInterpolator::Sample(120, 102.2));
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
  const uint8_t kAnalogInputPin = 36;

  // Define how often (in milliseconds) new samples are acquired
  const unsigned int kAnalogInputReadInterval = 500;

  // Define the produced value at the maximum input voltage (3.3V).
  // A value of 3.3 gives output equal to the input voltage.
  const float kAnalogInputScale = 4096;

  // Create a new Analog Input Sensor that reads an analog input pin
  // periodically.
  auto* analog_input = new AnalogInput(
      kAnalogInputPin, kAnalogInputReadInterval, "", kAnalogInputScale);

  // Add an observer that prints out the current value of the analog input
  // every time it changes.
  analog_input->attach([analog_input]() {
    debugD("Analogue input value: %f", analog_input->get());
    debugD("Transformed value: %f", convertAnalogToTemperature(analog_input->get()));
  });

  // Set GPIO pin 15 to output and toggle it every 650 ms

  const uint8_t kDigitalOutputPin = 15;
  const unsigned int kDigitalOutputInterval = 650;
  pinMode(kDigitalOutputPin, OUTPUT);
  app.onRepeat(kDigitalOutputInterval, [kDigitalOutputPin]() {
    digitalWrite(kDigitalOutputPin, !digitalRead(kDigitalOutputPin));
  });

  // Read GPIO 14 every time it changes

  const uint8_t kDigitalInput1Pin = 14;
  auto* digital_input1 =
      new DigitalInputChange(kDigitalInput1Pin, INPUT_PULLUP, CHANGE);

  // Connect the digital input to a lambda consumer that prints out the
  // value every time it changes.

  // Test this yourself by connecting pin 15 to pin 14 with a jumper wire and
  // see if the value changes!

  digital_input1->connect_to(new LambdaConsumer<bool>(
      [](bool input) { debugD("Digital input value changed: %d", input); }));

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

  // Again, test this yourself by connecting pin 15 to pin 13 with a jumper
  // wire and see if the value changes!

  auto* digital_input2 = new RepeatSensor<bool>(
      kDigitalInput2Interval,
      [kDigitalInput2Pin]() { return digitalRead(kDigitalInput2Pin); });

  // Connect the analog input to Signal K output. This will publish the
  // analog input value to the Signal K server every time it changes.
  analog_input->connect_to(new SKOutputFloat(
      "sensors.coolant.degrees",         // Signal K path
      "/sensors/coolant/degrees",        // configuration path, used in the
                                              // web UI and for storing the
                                              // configuration
      new SKMetadata("C",                     // Define output units
                     "Coolant temperature in Celcius")  // Value description
      ));

  // Connect digital input 2 to Signal K output.
  digital_input2->connect_to(new SKOutputBool(
      "sensors.digital_input2.value",          // Signal K path
      "/sensors/digital_input2/value",         // configuration path
      new SKMetadata("",                       // No units for boolean values
                     "Digital input 2 value")  // Value description
      ));

  // Start networking, SK server connections and other SensESP internals
  sensesp_app->start();
}

// ADC Value to Temperature for NTC Thermistor.
// Author: James Sleeman http://sparks.gogo.co.nz/ntc.html
// Licence: BSD (see footer for legalese)
//
// Thermistor characteristics:
//   Nominal Resistance 2830 at 25°C
//   Beta Value 3912.07
//
// Usage Examples:
//   float bestAccuracyTemperature    = convertAnalogToTemperature(analogRead(analogPin));
//   float lesserAccuracyTemperature  = approximateTemperatureFloat(analogRead(analogPin));
//   int   lowestAccuracyTemperature  = approximateTemperatureInt(analogRead(analogPin));
//
// Better accuracy = more resource (memory, flash) demands, the approximation methods 
// will only produce reasonable results in the range 50-100°C
//
//
// Thermistor Wiring:
//   Vcc -> Thermistor -> [316 Ohm Resistor] -> Gnd
//                     |
//                     \-> analogPin
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/** Calculate the temperature in °C from ADC (analogRead) value.
 *
 *  This conversion should generate reasonably accurate results over a large range of 
 *  the thermistor, it implements a 'Beta' approximation for a thermistor
 *  having Beta of 3912.07, and nominal values of 2830Ω at 25°C
 *
 *  @param {int} The result of an ADC conversion (analogRead) in the range 0 to 4096
 *  @return  {float} Temperature in °C
 */

float  convertAnalogToTemperature(unsigned int analogReadValue)
{
  // If analogReadValue is 0, we would otherwise cause a Divide-By-Zero,
  // Treat as crazy out-of-range temperature.
  if(analogReadValue == 0) return -1000.0;
  return (1/((log(((316.0 * (4096.0 - analogReadValue)) / analogReadValue)/2830.0)/3912.1) + (1 / (273.15 + 25.000)))) - 273.15;
}

void loop() { app.tick(); }
