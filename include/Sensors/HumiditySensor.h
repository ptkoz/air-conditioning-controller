#ifndef AIR_CONDITIONING_CONTROLLER_HUMIDITYSENSOR_H
#define AIR_CONDITIONING_CONTROLLER_HUMIDITYSENSOR_H

#include <Measures/Humidity.h>

namespace ACC::Sensors {
    /**
     * An abstract temperature sensor
     */
    class HumiditySensor {
        public:
            virtual Measures::Humidity measureHumidity() = 0;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_TEMPERATURESENSOR_H
