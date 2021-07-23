#ifndef AIR_CONDITIONING_CONTROLLER_TEMPERATURESENSOR_H
#define AIR_CONDITIONING_CONTROLLER_TEMPERATURESENSOR_H

#include <Measures/Temperature.h>

namespace ACC::Sensors {
    /**
     * An abstract temperature sensor
     */
    class TemperatureSensor {
        public:
            virtual Measures::Temperature measureTemperature() = 0;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_TEMPERATURESENSOR_H
