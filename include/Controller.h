#ifndef AIR_CONDITIONING_CONTROLLER_CONTROLLER_H
#define AIR_CONDITIONING_CONTROLLER_CONTROLLER_H

#include "Devices/AirConditioner.h"
#include "Devices/TemperatureSensor.h"
#include "Displays/Display.h"

namespace ACC {
    class Controller {
        private:
            double targetTemperature;
            const double temperatureTolerance = 0.5;
            bool isAirConditionerEnabled;

            Devices::AirConditioner & airConditioner;
            Devices::TemperatureSensor & temperatureSensor;
            Displays::Display & display;

        public:
            explicit Controller(
                    Devices::AirConditioner & airConditioner,
                    Devices::TemperatureSensor & temperatureSensor,
                    Displays::Display & display,
                    double targetTemperature
            );

            void process();
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_CONTROLLER_H
