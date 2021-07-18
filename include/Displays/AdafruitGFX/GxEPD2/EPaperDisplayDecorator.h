#ifndef AIR_CONDITIONING_CONTROLLER_EPAPERDISPLAYDECORATOR_H
#define AIR_CONDITIONING_CONTROLLER_EPAPERDISPLAYDECORATOR_H

#include "../../Display.h"
#include <GxEPD2_3C.h>

namespace ACC::Displays::AdafruitGFX::GxEPD2 {
    /**
     * Display decorator that wraps another AdafruitGFX display. Under the hood those
     * two needs to use the very same driver instance.
     */
    template<typename DRIVER, const uint16_t PAGE_HEIGHT>
    class EPaperDisplayDecorator : public Display {
        private:
            Display & decoratedDisplay;
            GxEPD2_3C<DRIVER, PAGE_HEIGHT> & driver;
            bool isRedrawRequired;
        public:
            explicit EPaperDisplayDecorator(Display & decoratedDisplay, GxEPD2_3C<DRIVER, PAGE_HEIGHT> & driver);
            void setIndoorTemperature(float temperature) override;
            void setOutdoorTemperature(float temperature) override;
            void setTargetTemperature(float temperature) override;
            void setCoolingIndicator(bool isCooling) override;
            void draw() override;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_EPAPERDISPLAYDECORATOR_H
