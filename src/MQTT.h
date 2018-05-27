
#ifndef _MQTT_H_
#define _MQTT_H_

#include <PubSubClient.h>

class MQTT {
    public: 
        MQTT();

        void publish(PubSubClient& client, const char* topic, const char* payload);
        void publish(PubSubClient& client, const char* topic, const String payload);
        void publish(PubSubClient& client, const char* topic, const float payload);
        void publish(PubSubClient& client, const char* topic, const int payload);
};


#endif
