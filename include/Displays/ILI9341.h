#ifndef AIR_CONDITIONING_CONTROLLER_ILI9341_H
#define AIR_CONDITIONING_CONTROLLER_ILI9341_H

#include <Adafruit_ILI9341.h>
#include "Display320x240.h"


namespace ACC::Displays::AdafruitGFX {
    /**
     * TFT LCD ILI9341 display implemented using Adafruit GFX
     */
    class ILI9341 : public Display320x240 {
        private:
            Adafruit_ILI9341 tft;
            char backlightPin;

            const unsigned char backlightDim = 100;

        public:
            ILI9341(char csPin, char dcPin, char mosiPin, char clkPin, char rstPin, char misoPin, char backlightPin):
                Display320x240(tft),
                tft(csPin, dcPin, mosiPin, clkPin, rstPin, misoPin),
                backlightPin(backlightPin) {}

            void initialize() override {
                pinMode(backlightPin, OUTPUT);
                analogWrite(backlightPin, backlightDim);

                tft.begin();
                Display320x240::initialize();
            }
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_ILI9341_H
