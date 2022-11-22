
#include "signalk_time.h"

namespace sensesp {

SKOutputTime::SKOutputTime(String sk_path, String config_path)
    : TimeString(config_path), SKEmitter(sk_path) {
  load_configuration();
}

String SKOutputTime::as_signalk() {
  DynamicJsonDocument json_doc(1024);
  String json;
  json_doc["path"] = this->sk_path;
  json_doc["value"] = output;
  serializeJson(json_doc, json);
  return json;
}

void SKOutputTime::get_configuration(JsonObject& root) {
  root["sk_path"] = sk_path;
}

static const char SCHEMA[] PROGMEM = R"({
    "type": "object",
    "properties": {
        "sk_path": { "title": "Signal K Path", "type": "string" },
        "value": { "title": "Last value", "type" : "string", "readOnly": true }
    }
  })";

String SKOutputTime::get_config_schema() { return FPSTR(SCHEMA); }

bool SKOutputTime::set_configuration(const JsonObject& config) {
  String expected[] = {"sk_path"};
  for (auto str : expected) {
    if (!config.containsKey(str)) {
      return false;
    }
  }
  sk_path = config["sk_path"].as<String>();
  return true;
}

}  // namespace sensesp
