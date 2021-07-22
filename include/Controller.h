#ifndef AIR_CONDITIONING_CONTROLLER_CONTROLLER_H
#define AIR_CONDITIONING_CONTROLLER_CONTROLLER_H

#include "Devices/AirConditioner.h"
#include "Devices/TemperatureSensor.h"
#include "Displays/Display.h"
#include "Time/Source.h"

namespace ACC {
    class Controller {
        private:
            double targetTemperature;
            const double acThreshold = 0.5;
            const double warningThreshold = 0.6;
            bool isAirConditionerEnabled;

            Devices::AirConditioner & airConditioner;
            Devices::TemperatureSensor & temperatureSensor;
            Displays::Display & display;
            const Time::Source & timeSource;

            void evaluateAirConditioningStatusChange(double indoorTemperature);
            bool hasIndoorTemperatureWarning(double indoorTemperature);

            void saveState() const;
            void restoreState();

        public:
            explicit Controller(
                    Devices::AirConditioner & airConditioner,
                    Devices::TemperatureSensor & temperatureSensor,
                    Displays::Display & display,
                    const Time::Source & timeSource
            );

            void process();
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_CONTROLLER_H
