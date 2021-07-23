#ifndef AIR_CONDITIONING_CONTROLLER_DISPLAY320X240_H
#define AIR_CONDITIONING_CONTROLLER_DISPLAY320X240_H

#include "../Display.h"
#include <Adafruit_GFX.h>

namespace ACC::Displays::AdafruitGFX {
    /**
     * 200x200 display implementation in Adafruit GFX Library
     */
    class Display320x240 : public Display {
        protected:
            Adafruit_GFX & gfx;

            const unsigned int backgroundColor = 0xeefe;
            const unsigned int defaultFontColor = 0x0000;
            const unsigned int warningFontColor = 0xf800;
            const unsigned int separatorColor = 0x001f;

            char currentIndoorTemperature[10] = "- C";
            char currentTargetTemperature[10] = "- C";
            char currentSecondTemperature[10] = "- C";
            char currentOutdoorTemperature[10] = "- C";

            bool hasIndoorTemperatureWarning = false;
            bool hasCoolingIndicator = false;

            /** Draws a single temperature box */
            void drawTemperature(
                    const char * oldTemperature,
                    const char * newTemperature,
                    short xOffset,
                    short yOffset,
                    bool withWarning,
                    const GFXfont * font
            );

            void drawIndoorTemperature(const char * temperature, bool hasWarning);
            void drawTargetTemperature(const char * temperature);
            void drawSecondTemperature(const char * temperature);
            void drawOutdoorTemperature(const char * temperature);
            void drawCoolingIndicator(bool isCooling);
        public:
            explicit Display320x240(Adafruit_GFX & gfx);

            /** Initializes the display */
            virtual void initialize();

            void setIndoorTemperature(double temperature, bool withWarning) override;
            void setTargetTemperature(double temperature) override;
            void setOutdoorTemperature(double temperature) override;
            void setCoolingIndicator(bool isCooling) override;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_DISPLAY320X240_H
