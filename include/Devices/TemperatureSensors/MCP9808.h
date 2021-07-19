#ifndef AIR_CONDITIONING_CONTROLLER_MCP9808_H
#define AIR_CONDITIONING_CONTROLLER_MCP9808_H

#include "../TemperatureSensor.h"
#include <Wire.h>
#include <Adafruit_MCP9808.h>

namespace ACC::Devices::TemperatureSensors {
    class MCP9808 : public TemperatureSensor {
        private:
            bool isInitialized;
            uint8_t sensorAddress;
            Adafruit_MCP9808 sensor;
        public:
            explicit MCP9808(uint8_t sensorAddress);
            double getTemperature() override;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_MCP9808_H
