#ifndef _SENSESP_UI_UI_OUTPUT_H_
#define _SENSESP_UI_UI_OUTPUT_H_
#include <ArduinoJson.h>

#include <functional>
#include <map>

#include "Arduino.h"
#include "sensesp/system/observablevalue.h"
#include "sensesp/system/valueconsumer.h"
#include "sensesp/system/valueproducer.h"

namespace sensesp {

constexpr char kUIOutputDefaultGroup[] = "Default";
constexpr int kUIOutputDefaultOrder = 1000;

class UIOutputBase : virtual public Observable {
 protected:
  String name_;
  String group_ = kUIOutputDefaultGroup;
  int order_ = kUIOutputDefaultOrder;
  static std::map<String, UIOutputBase*> ui_outputs_;

 public:
  UIOutputBase(String name, String group, int order)
      : name_(name), group_(group), order_(order) {
    ui_outputs_[name] = this;
  }

  String& get_name() { return name_; }

  virtual void set_json(const JsonObject& obj) {}

  static const std::map<String, UIOutputBase*>* get_ui_outputs() {
    return &ui_outputs_;
  }
};

template <typename T>
class UILambdaOutput : public UIOutputBase {
 private:
  std::function<T()> value_function_;

 public:
  UILambdaOutput(String name, std::function<T()> function,
                 String group = kUIOutputDefaultGroup,
                 int order = kUIOutputDefaultOrder)
      : UIOutputBase(name, group, order), value_function_(function) {}

  T get() { return value_function_(); }

  void set_json(const JsonObject& obj) override {
    JsonObject output = obj.createNestedObject(name_);
    output["Value"] = get();
    output["Group"] = group_;
    output["Order"] = order_;
  }
};

extern std::map<String, UIOutputBase*> ui_outputs;

template <typename T>
class UIOutput : public UIOutputBase,
                 public ObservableValue<T>,
                 public ValueConsumer<T> {
 public:
  UIOutput(String name)
      : UIOutputBase(name, kUIOutputDefaultGroup, kUIOutputDefaultOrder) {}

  UIOutput(String name, T value, String group = kUIOutputDefaultGroup,
           int order = kUIOutputDefaultOrder)
      : UIOutputBase(name, group, order) {
    this->ObservableValue<T>::emit(value);
  }

  void set_json(const JsonObject& obj) override {
    JsonObject output = obj.createNestedObject(name_);
    output["Value"] = ObservableValue<T>::get();
    output["Group"] = group_;
    output["Order"] = order_;
  }

  void set_input(T new_value, uint8_t input_channel = 0) override {
    this->ValueProducer<T>::emit(new_value);
  }
};
}  // namespace sensesp

#endif
