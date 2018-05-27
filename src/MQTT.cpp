#include "MQTT.h"

MQTT::MQTT() {}

void MQTT::publish(PubSubClient& client, const char* topic, const char* payload) {
  client.publish(topic, payload);
}

void MQTT::publish(PubSubClient& client, const char* topic, const String payload) {
  client.publish(topic, payload.c_str());
}

void MQTT::publish(PubSubClient& client, const char* topic, const float payload) {
  client.publish(topic, String(payload).c_str());
}

void MQTT::publish(PubSubClient& client, const char* topic, const int payload) {
  client.publish(topic, String(payload).c_str());
}