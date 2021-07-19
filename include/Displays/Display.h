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
            bool hasIndoorTemperature = false;
            double indoorTemperature = 0;

            bool hasOutdoorTemperature = false;
            double outdoorTemperature = 0;

            bool hasTargetTemperature = false;
            double targetTemperature = 0;

            bool isCoolingEnabled = false;

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
            virtual void setIndoorTemperature(double temperature) {
                hasIndoorTemperature = true;
                indoorTemperature = temperature;
            }

            /** Sets outdoor temperature visible on the display */
            virtual void setOutdoorTemperature(double temperature) {
                hasOutdoorTemperature = true;
                outdoorTemperature = temperature;
            }

            /** Sets requested target cooling temperature visible on the display */
            virtual void setTargetTemperature(double temperature) {
                hasTargetTemperature = true;
                targetTemperature = temperature;
            }

            /** Set indicator status for whether air conditioning is enabled or not */
            virtual void setCoolingIndicator(bool isCooling) {
                isCoolingEnabled = isCooling;
            }

            /** Ensure all the latest information is displayed on the screen */
            virtual void draw() = 0;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_DISPLAY_H
