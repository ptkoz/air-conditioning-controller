#include "Sensors/SHT35.h"

using namespace ACC::Sensors;

SHT35::SHT35(uint8_t sensorAddress):
    sensorAddress(sensorAddress),
    measureIndex(0),
    measures{} {

}

void SHT35::initialize() {
    sensor.begin(sensorAddress);
    sensor.heatOff();

    for (double & measure : measures) {
        sensor.read(true);
        measure = sensor.getTemperature();
    }
}

ACC::Measures::Temperature SHT35::measureTemperature() {
    sensor.read(false);
    measures[measureIndex++ % numberOfTemperatureMeasures] = sensor.getTemperature();

    double sum = 0;
    char count = 0;
    for (double measure : measures) {
        sum += measure;
        count++;
    }

    return Measures::Temperature(sum / count);
}


