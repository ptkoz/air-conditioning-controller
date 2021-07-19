#include "Devices/TemperatureSensors/MCP9808.h"

using namespace ACC::Devices::TemperatureSensors;

MCP9808::MCP9808(uint8_t sensorAddress): sensorAddress(sensorAddress), isInitialized(false) {

}

double MCP9808::getTemperature() {
    if (!isInitialized) {
        isInitialized = true;
        sensor.begin(sensorAddress);
        sensor.setResolution(3);
    }

    return sensor.readTempC();
}
