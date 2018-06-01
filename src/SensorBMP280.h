
#ifndef _SENSOR_BMP280_H_
#define _SENSOR_BMP280_H_

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "Sensor.h"

class SensorBMP280 : public Sensor {
    public:
        SensorBMP280();

        void init();
        void measure();

} ;

#endif