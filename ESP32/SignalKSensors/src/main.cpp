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

// Prototypes
float convertAnalogToTemperature(unsigned int);

  // Voltage sent into the voltage divider circuit that includes the analog
  // sender
  const float Vin = 3.3;
  // The resistance, in ohms, of the fixed resistor (R1) in the voltage divider
  // circuit
  const float R1 = 316.0;

class TemperatureInterpreter : public CurveInterpolator {
 public:
  TemperatureInterpreter(String config_path = "")
      : CurveInterpolator(NULL, config_path) {
    // Populate a lookup table tp translate the ohm values returned by
    // our temperature sender to degrees Kelvin
    clear_samples();
    // addSample(CurveInterpolator::Sample(knownOhmValue, knownKelvin));
    add_sample(CurveInterpolator::Sample(5728, 10));
    add_sample(CurveInterpolator::Sample(4496, 15));
    add_sample(CurveInterpolator::Sample(3555, 20));
    add_sample(CurveInterpolator::Sample(2830, 25));
    add_sample(CurveInterpolator::Sample(2268, 30));
    add_sample(CurveInterpolator::Sample(1828, 35));
    add_sample(CurveInterpolator::Sample(1483, 40));
    add_sample(CurveInterpolator::Sample(1210, 45));
    add_sample(CurveInterpolator::Sample(992, 50));
    add_sample(CurveInterpolator::Sample(819, 55));
    add_sample(CurveInterpolator::Sample(679, 60));
    add_sample(CurveInterpolator::Sample(566, 65));
    add_sample(CurveInterpolator::Sample(475, 70));
    add_sample(CurveInterpolator::Sample(400, 75));
    add_sample(CurveInterpolator::Sample(338, 80));
    add_sample(CurveInterpolator::Sample(287, 85));
    add_sample(CurveInterpolator::Sample(245, 90));
    add_sample(CurveInterpolator::Sample(210, 95));
    add_sample(CurveInterpolator::Sample(180, 100));
    add_sample(CurveInterpolator::Sample(156, 105));
    add_sample(CurveInterpolator::Sample(135, 110));
    add_sample(CurveInterpolator::Sample(117, 115));
    add_sample(CurveInterpolator::Sample(102, 120));

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

  // An AnalogInput gets the value from the microcontroller's AnalogIn pin,
  // which is a value from 0 to 1023.
  // ESP32 has many pins that can be used for AnalogIn, and they're
  // expressed here as the XX in GPIOXX.
  auto* analog_input = new AnalogInput(36);

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
      ->connect_to(new Linear(1.0, 0.0, "/collant/temp/calibrate"))
      ->connect_to(
          new SKOutputFloat(sk_path, "/coolant/temp/sk", metadata));

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
