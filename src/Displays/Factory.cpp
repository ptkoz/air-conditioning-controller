#include <GxEPD2_3C.h>
#include "Displays/Factory.h"
#include "Displays/AdafruitGFX/Display200x200.h"
#include "Displays/AdafruitGFX/GxEPD2/EPaperDisplayDecorator.h"

using namespace ACC::Displays;

Display & Factory::createWaveShare3Color200x200Display(
        char csPin,
        char dcPin,
        char rstPin,
        char busyPin
) {
    static GxEPD2_3C<GxEPD2_154_Z90c, WAVESHARE_200x200_PAGE_HEIGHT> driver(
            GxEPD2_154_Z90c(
                    csPin,
                    dcPin,
                    rstPin,
                    busyPin
            ));

    driver.init();
    driver.setRotation(1);

    static AdafruitGFX::Display200x200 graphicDisplay(driver);

    static AdafruitGFX::GxEPD2::EPaperDisplayDecorator<GxEPD2_154_Z90c, WAVESHARE_200x200_PAGE_HEIGHT> ePaperDisplay(
                graphicDisplay,
                driver
            );

    return ePaperDisplay;
}
