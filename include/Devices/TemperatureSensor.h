#ifndef AIR_CONDITIONING_CONTROLLER_TEMPERATURESENSOR_H
#define AIR_CONDITIONING_CONTROLLER_TEMPERATURESENSOR_H

namespace ACC::Devices {
    class TemperatureSensor {
        public:
            virtual short int getTemperature() = 0;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_TEMPERATURESENSOR_H
