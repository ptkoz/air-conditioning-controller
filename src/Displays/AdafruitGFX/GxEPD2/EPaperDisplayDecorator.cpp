#include "Displays/Factory.h"
#include "Displays/AdafruitGFX/GxEPD2/EPaperDisplayDecorator.h"

using namespace ACC::Displays::AdafruitGFX::GxEPD2;

template<typename DRIVER, const uint16_t PAGE_HEIGHT>
EPaperDisplayDecorator<DRIVER, PAGE_HEIGHT>::EPaperDisplayDecorator(
        Display & decoratedDisplay,
        GxEPD2_3C<DRIVER, PAGE_HEIGHT> & driver
):
        decoratedDisplay(decoratedDisplay), driver(driver), isRedrawRequired(true) {

}

template<typename DRIVER, const uint16_t PAGE_HEIGHT>
void EPaperDisplayDecorator<DRIVER, PAGE_HEIGHT>::setIndoorTemperature(float temperature) {
    if (indoorTemperature != temperature) {
        Display::setIndoorTemperature(temperature);
        isRedrawRequired = true;
    }
}

template<typename DRIVER, const uint16_t PAGE_HEIGHT>
void EPaperDisplayDecorator<DRIVER, PAGE_HEIGHT>::setOutdoorTemperature(float temperature) {
    if (outdoorTemperature != temperature) {
        Display::setOutdoorTemperature(temperature);
        isRedrawRequired = true;
    }
}

template<typename DRIVER, const uint16_t PAGE_HEIGHT>
void EPaperDisplayDecorator<DRIVER, PAGE_HEIGHT>::setTargetTemperature(float temperature) {
    if (targetTemperature != temperature) {
        Display::setTargetTemperature(temperature);
        isRedrawRequired = true;
    }
}

template<typename DRIVER, const uint16_t PAGE_HEIGHT>
void EPaperDisplayDecorator<DRIVER, PAGE_HEIGHT>::setCoolingIndicator(bool isCooling) {
    if (isCoolingEnabled != isCooling) {
        Display::setCoolingIndicator(isCooling);
        isRedrawRequired = true;
    }
}

template<typename DRIVER, const uint16_t PAGE_HEIGHT>
void EPaperDisplayDecorator<DRIVER, PAGE_HEIGHT>::draw() {
    if (isRedrawRequired) {
        driver.firstPage();
        do {
            decoratedDisplay.draw();
        } while (driver.nextPage());
    }
}

namespace ACC::Displays::AdafruitGFX::GxEPD2 {
    template
    class EPaperDisplayDecorator<GxEPD2_154_Z90c, WAVESHARE_200x200_PAGE_HEIGHT>;
}