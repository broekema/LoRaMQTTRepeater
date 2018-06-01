#include <SensorBMP280.h>

Adafruit_BME280 mySensor;

SensorBMP280::SensorBMP280() {


}
void SensorBMP280::init() {
    mySensor.begin();

    mySensor.setSampling(Adafruit_BME280::MODE_FORCED,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X1, // humidity
                    Adafruit_BME280::FILTER_OFF   );
}
void SensorBMP280::measure() {
    mySensor.takeForcedMeasurement();

    mySensor.readTemperature();
    mySensor.readHumidity();
    mySensor.readPressure();

}