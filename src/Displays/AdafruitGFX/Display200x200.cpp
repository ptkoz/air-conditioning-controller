#include "Displays/AdafruitGFX/Display200x200.h"
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>

using namespace ACC::Displays::AdafruitGFX;

Display200x200::Display200x200(Adafruit_GFX &gfx) :
        gfx(gfx) {

}

void Display200x200::draw() {
    char buffer[20];

    temperatureToString(buffer, hasIndoorTemperature, indoorTemperature);
    drawTemperature((const char *)F("Indoor"), buffer, 0, false, true);

    temperatureToString(buffer, hasTargetTemperature, targetTemperature);
    drawTemperature((const char *)F("Target"), buffer, 60, false, true);

    temperatureToString(buffer, hasOutdoorTemperature, outdoorTemperature);
    drawTemperature((const char *)F("Outdoor"), buffer, 120, false, false);
}

void Display200x200::drawTemperature(
        const char label[],
        const char temperature[],
        short xOffset,
        bool withLeftBorder,
        bool withRightBorder
) {
    if (withLeftBorder) {
        gfx.drawFastVLine(xOffset + 5, 5, 50, 0x0000);
    }

    if (withRightBorder) {
        gfx.drawFastVLine(xOffset + 5 + 60, 5, 50, 0x0000);
    }

    gfx.setTextColor(0x0000);

    gfx.setCursor(xOffset + 10, 5);
    gfx.setFont(&FreeSansBold12pt7b);
    gfx.print(label);

    int16_t textRectLeft, textRectTop;
    uint16_t textRectWidth, textRectHeight;

    gfx.getTextBounds(temperature, 0, 0, &textRectLeft, &textRectTop, &textRectWidth, &textRectHeight);
    gfx.setCursor((60 - textRectWidth) / 2 + 10, 25);
    gfx.setFont(&FreeSansBold24pt7b);
    gfx.print(temperature);
}
