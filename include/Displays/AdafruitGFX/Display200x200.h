#ifndef AIR_CONDITIONING_CONTROLLER_DISPLAY200X200_H
#define AIR_CONDITIONING_CONTROLLER_DISPLAY200X200_H

#include "../Display.h"
#include <Adafruit_GFX.h>

namespace ACC::Displays::AdafruitGFX {
    /**
     * 200x200 display implementation in Adafruit GFX Library
     */
    class Display200x200 : public Display {
        private:
            Adafruit_GFX & gfx;

            /** Draws a single temperature box */
            void drawTemperature(
                    const char label[],
                    const char temperature[],
                    short xOffset,
                    bool withRightBorder,
                    bool withWarning
            );
        public:
            explicit Display200x200(Adafruit_GFX & gfx);
            void draw() override;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_DISPLAY200X200_H
