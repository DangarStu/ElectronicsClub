#ifndef _sk_value_listener_H
#define _sk_value_listener_H

#include <ArduinoJson.h>

#include "sensesp/system/observable.h"
#include "sensesp/system/valueproducer.h"
#include "signalk_listener.h"

namespace sensesp {

/**
 * @brief An ValueProducer that listens to specific Signal K paths
 * and emits its value whenever it changes.
 */
template <class T>
class SKValueListener : public SKListener, public ValueProducer<T> {
 public:
  /**
   * @param sk_path The Signal K path you want to listen to for value changes
   * @param listen_delay The minimum interval between updates in ms
   */
  SKValueListener(String sk_path, int listen_delay = 1000)
      : SKListener(sk_path, listen_delay) {
    if (sk_path == "") {
      debugE("SKValueListener: User has provided no sk_path to listen to.");
    }
  }

  void parse_value(const JsonObject& json) override {
    this->emit(json["value"].as<T>());
  }
};

typedef SKValueListener<float> FloatSKListener;
typedef SKValueListener<int> IntSKListener;
typedef SKValueListener<bool> BoolSKListener;
typedef SKValueListener<String> StringSKListener;

}  // namespace sensesp

#endif
