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

#define VERSION "0.1"

#include "LoRa.h"
#include "SensorBMP280.h"

#define WIFI_SSID     ""
#define WIFI_PASSWORD ""
#include "local_wifi.h"

#define SERIAL_BAUD 115200

/// Arduino OTA configuration
#define OTA_HOSTNAME "LORA"
#define OTA_PASSWORD "OTA_PASSWORD"

/// MQTT configuration
#define MQTT_SERVER "10.5.1.5"
#define MQTT_PORT   1883
#define MQTT_ROOT   "Peizerweg217/"

#define MQTT_GATEWAY_NAME "LoRaRepeater/"
#define MQTT_WILL_TOPIC MQTT_ROOT MQTT_GATEWAY_NAME "LWT"
#define MQTT_WILL_RETAIN true
#define MQTT_WILL_QOS 0
#define MQTT_WILL_MESSAGE "Offline"
#define MQTT_GATEWAY_ANNOUNCEMENT "Online"
#define MQTT_VERSION_TOPIC MQTT_ROOT MQTT_GATEWAY_NAME "version"
