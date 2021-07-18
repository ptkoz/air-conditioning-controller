#ifndef AIR_CONDITIONING_CONTROLLER_DISPLAY_H
#define AIR_CONDITIONING_CONTROLLER_DISPLAY_H

#include <stdio.h>
#include <WString.h>

namespace ACC::Displays {
    /**
     * Information display for Air Conditioning Controller
     */
    class Display {
        protected:
            bool hasIndoorTemperature = false;
            float indoorTemperature = 0;

            bool hasOutdoorTemperature = false;
            float outdoorTemperature = 0;

            bool hasTargetTemperature = false;
            float targetTemperature = 0;

            bool isCoolingEnabled = false;

            virtual void temperatureToString(char * buffer, bool hasTemperature, float temperature) {
                if (!hasTemperature) {
                    sprintf(buffer, (const char *)F("- °C"));
                } else {
                    sprintf(buffer, (const char *)F("%.1f"), (double) temperature);
                }
            }

        public:
            /** Sets indoor temperature visible on the display */
            virtual void setIndoorTemperature(float temperature) {
                hasIndoorTemperature = true;
                indoorTemperature = temperature;
            }

            /** Sets outdoor temperature visible on the display */
            virtual void setOutdoorTemperature(float temperature) {
                hasOutdoorTemperature = true;
                outdoorTemperature = temperature;
            }

            /** Sets requested target cooling temperature visible on the display */
            virtual void setTargetTemperature(float temperature) {
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
