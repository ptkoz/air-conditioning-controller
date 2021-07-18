#ifndef AIR_CONDITIONING_CONTROLLER_FACTORY_H
#define AIR_CONDITIONING_CONTROLLER_FACTORY_H

#include <Adafruit_GFX.h>
#include "Display.h"

#define WAVESHARE_200x200_PAGE_HEIGHT 16

namespace ACC::Displays {
    /**
     * Factory that creates displays
     */
    class Factory {
        public:
            static Display & createWaveShare3Color200x200Display(char csPin, char dcPin, char rstPin, char busyPin);
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_FACTORY_H
