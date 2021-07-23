#ifndef AIR_CONDITIONING_CONTROLLER_SHT35_H
#define AIR_CONDITIONING_CONTROLLER_SHT35_H

#include "Sensors/TemperatureSensor.h"
#include <Wire.h>
#include <SHT31.h>

#define SHT35_NUMBER_OF_TEMPERATURE_MEASURES 5

namespace ACC::Sensors {
    /**
     * An SHT35 temperature & humidity sensor
     */
    class SHT35 : public TemperatureSensor {
        private:
            uint8_t sensorAddress;
            SHT31 sensor;

            unsigned char measureIndex;
            double measures[SHT35_NUMBER_OF_TEMPERATURE_MEASURES];
        public:
            explicit SHT35(uint8_t sensorAddress);

            void initialize();
            Measures::Temperature measureTemperature() override;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_SHT35_H
