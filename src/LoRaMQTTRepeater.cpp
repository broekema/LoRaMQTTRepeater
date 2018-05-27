/*
    LoRaMQTTRepeater

    Copyright 2018 Chris Broekema

    LoRaMQTTRepeater is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    kwh-meter is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Arduino.h>

/* #include <NTPClient.h> */
#include <WiFi.h>
#include <Update.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <ESPmDNS.h>

#include "LoRaMQTTRepeater.h"

/* int  sensor_value; */
/* boolean state = false;  // state == 1 -> sensor == high */
/* unsigned long count = 0; */

/* WiFiUDP ntpUDP; */
/* NTPClient timeClient(ntpUDP, NTP_HOST, NTP_OFFSET, NTP_UPDATE_INTERVAL); */

WiFiClient eClient;
PubSubClient pubsubClient(MQTT_SERVER, MQTT_PORT, NULL, eClient);

void setup_wifi() {
  //  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
#ifdef DEBUG
    Serial.println(".");
#endif
    delay(500);
  }

#ifdef DEBUG
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
#endif
}

void setup_OTA() {
  ArduinoOTA.setPort(8266);
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.setPassword(OTA_PASSWORD);
  ArduinoOTA.onStart([]() { Serial.println("Start"); });
  ArduinoOTA.onEnd([]() { Serial.println("End");});
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
#ifdef DEBUG
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
#endif
    });
#ifdef DEBUG
  ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println(F("Auth Failed"));
      else if (error == OTA_BEGIN_ERROR) Serial.println(F("Begin Failed"));
      else if (error == OTA_CONNECT_ERROR) Serial.println(F("Connect Failed"));
      else if (error == OTA_RECEIVE_ERROR) Serial.println(F("Receive Failed"));
      else if (error == OTA_END_ERROR) Serial.println(F("End Failed"));
    });
#endif
  ArduinoOTA.begin();
}


void setup() {
  Serial.begin(SERIAL_BAUD);
  //  pinMode(sensorPin, INPUT);
#ifdef DEBUG
  Serial.println("kWh meter initializing");
#endif
  delay(1500);

  setup_wifi();
  setup_OTA();
  delay(1500);
}

boolean reconnect_mqtt() {
  // Loop until we're reconnected
  while (!pubsubClient.connected()) {
    if (pubsubClient.connect(MQTT_GATEWAY_NAME, MQTT_WILL_TOPIC, MQTT_WILL_QOS, MQTT_WILL_RETAIN, MQTT_WILL_MESSAGE)) {
#ifdef DEBUG
	Serial.println("Connected to broker ");
#endif
	pubsubClient.publish(MQTT_WILL_TOPIC, MQTT_GATEWAY_ANNOUNCEMENT, MQTT_WILL_RETAIN);
	pubsubClient.publish(MQTT_VERSION_TOPIC, VERSION, MQTT_WILL_RETAIN);
      } else {
#ifdef DEBUG
	Serial.println("failed, rc=" + String(pubsubClient.state()));
	Serial.println("try again in 5s");
#endif
	// Wait 5 seconds before retrying
	delay(5000);
    }
  }
  return pubsubClient.connected();
}

void loop() {
  setup();

  for (;;) {
    // house-keeping - MQTT, NTP and ArduinoOTA
    if (!pubsubClient.connected()) {
      reconnect_mqtt() ;
    }
    pubsubClient.loop();       // MQTT
    ArduinoOTA.handle(); // OTA
  }
}
