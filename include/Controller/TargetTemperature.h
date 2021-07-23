#ifndef AIR_CONDITIONING_CONTROLLER_TARGETTEMPERATURE_H
#define AIR_CONDITIONING_CONTROLLER_TARGETTEMPERATURE_H

#include "Measures/Temperature.h"

namespace ACC::Controller {
    class TargetTemperature : public Measures::Temperature {
        private:
            static constexpr double acBoundary = 0.5f;
            static constexpr double warningBoundary = 0.6f;
        public:
            /** Construct from temperature value */
            explicit TargetTemperature(double temperature):
                Measures::Temperature(temperature) {};

            explicit TargetTemperature():
                Measures::Temperature() {}

            /** Checks if given temperature is higher than the threshold that enables AC */
            bool isAboveAcOnThreshold(const Measures::Temperature & temperature) const {
                return temperature.getTemperature() > rawValue + acBoundary;
            }

            /** Checks if given temperature is lower than the threshold that disables AC */
            bool isBelowAcOffThreshold(const Measures::Temperature & temperature) const {
                return temperature.getTemperature() < rawValue - acBoundary;
            }

            /** Checks if given temperature is beyond a warning threshold (any direction) */
            bool isWarningTemperature(const Measures::Temperature & temperature) const {
                if (temperature.getTemperature() > rawValue + warningBoundary) {
                    return true;
                }

                if (temperature.getTemperature() < rawValue - warningBoundary) {
                    return true;
                }

                return false;
            }
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_TARGETTEMPERATURE_H
