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
void EPaperDisplayDecorator<DRIVER, PAGE_HEIGHT>::setIndoorTemperature(double temperature) {
    isRedrawRequired = isRedrawRequired || !hasIndoorTemperature ||
                       isTemperatureSignificantlyDifferent(indoorTemperature, temperature);

    Display::setIndoorTemperature(temperature);
    decoratedDisplay.setIndoorTemperature(temperature);
}

template<typename DRIVER, const uint16_t PAGE_HEIGHT>
void EPaperDisplayDecorator<DRIVER, PAGE_HEIGHT>::setOutdoorTemperature(double temperature) {
    isRedrawRequired = isRedrawRequired || !hasOutdoorTemperature ||
                       isTemperatureSignificantlyDifferent(outdoorTemperature, temperature);

    Display::setOutdoorTemperature(temperature);
    decoratedDisplay.setOutdoorTemperature(temperature);
}

template<typename DRIVER, const uint16_t PAGE_HEIGHT>
void EPaperDisplayDecorator<DRIVER, PAGE_HEIGHT>::setTargetTemperature(double temperature) {
    isRedrawRequired = isRedrawRequired || !hasTargetTemperature ||
                       isTemperatureSignificantlyDifferent(targetTemperature, temperature);

    Display::setTargetTemperature(temperature);
    decoratedDisplay.setTargetTemperature(temperature);
}

template<typename DRIVER, const uint16_t PAGE_HEIGHT>
void EPaperDisplayDecorator<DRIVER, PAGE_HEIGHT>::setCoolingIndicator(bool isCooling) {
    isRedrawRequired = isRedrawRequired || isCooling != isCoolingEnabled;
    Display::setCoolingIndicator(isCooling);
    decoratedDisplay.setCoolingIndicator(isCooling);
}

template<typename DRIVER, const uint16_t PAGE_HEIGHT>
void EPaperDisplayDecorator<DRIVER, PAGE_HEIGHT>::draw() {
    if (isRedrawRequired) {
        driver.firstPage();
        do {
            decoratedDisplay.draw();
        } while (driver.nextPage());
        isRedrawRequired = false;
    }
}

template<typename DRIVER, const uint16_t PAGE_HEIGHT>
bool EPaperDisplayDecorator<DRIVER, PAGE_HEIGHT>::isTemperatureSignificantlyDifferent(double previous, double current) {
    char buff1[6];
    char buff2[6];

    Display::temperatureToString(buff1, previous);
    Display::temperatureToString(buff2, current);

    return strcmp(buff1, buff2) != 0;
}

namespace ACC::Displays::AdafruitGFX::GxEPD2 {
    template
    class EPaperDisplayDecorator<GxEPD2_154_Z90c, 8>;
}