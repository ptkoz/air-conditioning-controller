#ifndef AIR_CONDITIONING_CONTROLLER_SHT35_H
#define AIR_CONDITIONING_CONTROLLER_SHT35_H

#include "Sensors/TemperatureSensor.h"
#include "Sensors/HumiditySensor.h"
#include <Wire.h>
#include <SHT31.h>
#include <Time/Source.h>

namespace ACC::Sensors {
    /**
     * An SHT35 temperature & humidity sensor
     */
    class SHT35 : public TemperatureSensor, public HumiditySensor {
        private:
            static constexpr unsigned char numberOfMeasures = 3;
            static constexpr unsigned short sensorReadInterval = 1; // seconds

            uint8_t sensorAddress;
            SHT31 sensor;

            const Time::Source & timeSource;
            Time::Timestamp lastSensorRead = Time::Timestamp(-sensorReadInterval);

            unsigned char temperatureMeasureIndex = 0;
            float temperatureMeasures[numberOfMeasures] = {};

            unsigned char humidityMeasureIndex = 0;
            float humidityMeasures[numberOfMeasures] = {};

            void requestMeasurementFromSensor();
        public:
            explicit SHT35(uint8_t sensorAddress, const Time::Source & timeSource):
                sensorAddress(sensorAddress),
                timeSource(timeSource) {}

            void initialize();
            Measures::Temperature measureTemperature() override;
            Measures::Humidity measureHumidity() override;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_SHT35_H
