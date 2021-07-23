#include "Devices/TemperatureSensors/SHT35.h"

using namespace ACC::Devices::TemperatureSensors;

SHT35::SHT35(uint8_t sensorAddress): sensorAddress(sensorAddress), measureIndex(0) {

}

void SHT35::initialize() {
    sensor.begin(sensorAddress);
    sensor.read(true);

    for (double & measure : measures) {
        measure = sensor.getTemperature();
    }
}

void SHT35::measure() {
    sensor.read(false);
    measures[measureIndex++ % SHT35_NUMBER_OF_TEMPERATURE_MEASURES] = sensor.getTemperature();
}

double SHT35::getTemperature() {
    double sum = 0;
    char count = 0;
    for (double measure : measures) {
        sum += measure;
        count++;
    }

    return sum / count;
}


