#ifndef AIR_CONDITIONING_CONTROLLER_SHT35_H
#define AIR_CONDITIONING_CONTROLLER_SHT35_H

#include "Sensors/TemperatureSensor.h"
#include <Wire.h>
#include <SHT31.h>

namespace ACC::Sensors {
    /**
     * An SHT35 temperature & humidity sensor
     */
    class SHT35 : public TemperatureSensor {
        private:
            static constexpr unsigned char numberOfTemperatureMeasures = 3;
            uint8_t sensorAddress;
            SHT31 sensor;

            unsigned char measureIndex;
            double measures[numberOfTemperatureMeasures];
        public:
            explicit SHT35(uint8_t sensorAddress);

            void initialize();
            Measures::Temperature measureTemperature() override;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_SHT35_H
