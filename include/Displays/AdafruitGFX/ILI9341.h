#ifndef AIR_CONDITIONING_CONTROLLER_ILI9341_H
#define AIR_CONDITIONING_CONTROLLER_ILI9341_H

#include <Adafruit_ILI9341.h>
#include "Display320x240.h"


namespace ACC::Displays::AdafruitGFX {
    class ILI9341 : public Display320x240 {
        private:
            Adafruit_ILI9341 tft;
            char backlightPin;

        public:
            ILI9341(char csPin, char dcPin, char mosiPin, char clkPin, char rstPin, char misoPin, char backlightPin) :
                    Display320x240(tft),
                    tft(csPin, dcPin, mosiPin, clkPin, rstPin, misoPin),
                    backlightPin(backlightPin) {}

            void begin() override {
                pinMode(backlightPin, OUTPUT);
                analogWrite(backlightPin, 50);

                tft.begin();
                Display320x240::begin();
            }
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_ILI9341_H
