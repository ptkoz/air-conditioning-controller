#include "Devices/TemperatureSensors/MCP9808.h"

using namespace ACC::Devices::TemperatureSensors;

MCP9808::MCP9808(uint8_t sensorAddress): sensorAddress(sensorAddress), isInitialized(false), measureIndex(0) {

}

void MCP9808::measure() {
    if (!isInitialized) {
        isInitialized = true;
        sensor.begin(sensorAddress);
        sensor.setResolution(3);

        for (double & measure : measures) {
            measure = sensor.readTempC();
        }
    }

    measures[measureIndex++ % 5] = sensor.readTempC();
}

double MCP9808::getTemperature() {
    double sum = 0;
    char count = 0;
    for (double measure : measures) {
        sum += measure;
        count++;
    }

    return sum / count;
}


