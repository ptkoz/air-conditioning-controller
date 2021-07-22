#ifndef AIR_CONDITIONING_CONTROLLER_DISPLAY_H
#define AIR_CONDITIONING_CONTROLLER_DISPLAY_H

#include <WString.h>
#include "stdio.h"

namespace ACC::Displays {
    /**
     * Information display for Air Conditioning Controller
     */
    class Display {
        protected:
            static void formatTemperatureString(char buffer[], bool hasTemperature, double temperature) {
                if (!hasTemperature) {
                    strcpy(buffer, "- C");
                } else {
                    Display::temperatureToString(buffer, temperature);
                    strcat(buffer, " C");
                }
            }

            static void temperatureToString(char buffer[], double temperature) {
                dtostrf(temperature, 5, 1, buffer);
            }

        public:
            /** Sets indoor temperature visible on the display */
            virtual void setIndoorTemperature(double temperature, bool withWarning) = 0;

            /** Sets outdoor temperature visible on the display */
            virtual void setOutdoorTemperature(double temperature) = 0;

            /** Sets requested target cooling temperature visible on the display */
            virtual void setTargetTemperature(double temperature) = 0;

            /** Set indicator status for whether air conditioning is enabled or not */
            virtual void setCoolingIndicator(bool isCooling) = 0;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_DISPLAY_H
