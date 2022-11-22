#include "sensesp_app.h"

#include "sensesp/net/discovery.h"
#include "sensesp/net/networking.h"
#include "sensesp/net/ota.h"
#include "sensesp/system/system_status_led.h"
#include "sensesp/transforms/debounce.h"

namespace sensesp {

SensESPApp* SensESPApp::get() {
  if (instance_ == nullptr) {
    instance_ = new SensESPApp();
  }
  return (SensESPApp*)instance_;
}

/**
 * @brief Perform initialization of SensESPApp once builder configuration is
 * done.
 *
 * This should be only called from the builder!
 *
 */
void SensESPApp::setup() {
  // call the parent setup()
  SensESPBaseApp::setup();

  // create the networking object
  networking_ =
      new Networking("/System/WiFi Settings", ssid_, wifi_password_,
                     SensESPBaseApp::get_hostname(), wifi_manager_password_);

  if (ota_password_ != nullptr) {
    // create the OTA object
    ota_ = new OTA(ota_password_);
  }

  // create the HTTP server
  this->http_server_ = new HTTPServer();

  // create the SK delta object
  sk_delta_queue_ = new SKDeltaQueue();

  // create the websocket client
  this->ws_client_ = new WSClient("/System/Signal K Settings", sk_delta_queue_,
                                  sk_server_address_, sk_server_port_);

  // connect the system status controller
  this->networking_->connect_to(&system_status_controller_);
  this->ws_client_->connect_to(&system_status_controller_);

  // create the MDNS discovery object
  mdns_discovery_ = new MDNSDiscovery();

  // create the wifi disconnect watchdog
  this->system_status_controller_
      .connect_to(new DebounceTemplate<SystemStatus>(
          3 * 60 * 1000  // 180 s = 180000 ms = 3 minutes
          ))
      ->connect_to(new LambdaConsumer<SystemStatus>([](SystemStatus input) {
        debugD("Got system status: %d", (int)input);
        if (input == SystemStatus::kWifiDisconnected ||
            input == SystemStatus::kWifiNoAP) {
          debugW("Unable to connect to wifi for too long; restarting.");
          ReactESP::app->onDelay(1000, []() { ESP.restart(); });
        }
      }));

  // create a system status led and connect it

  if (system_status_led_ == NULL) {
    system_status_led_ = new SystemStatusLed(LED_PIN);
  }
  this->system_status_controller_.connect_to(system_status_led_);
  this->ws_client_->get_delta_count_producer().connect_to(system_status_led_);
}

ObservableValue<String>* SensESPApp::get_hostname_observable() {
  return hostname_;
}

SensESPApp* sensesp_app;

}  // namespace sensesp
