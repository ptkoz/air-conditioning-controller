#include "Displays/AdafruitGFX/Display200x200.h"
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>

using namespace ACC::Displays::AdafruitGFX;

Display200x200::Display200x200(Adafruit_GFX &gfx) :
        gfx(gfx) {

}

void Display200x200::draw() {
    char buffer[10];

    formatTemperatureString(buffer, hasIndoorTemperature, indoorTemperature);
    drawTemperature("In", buffer, 5, true);

    formatTemperatureString(buffer, hasTargetTemperature, targetTemperature);
    drawTemperature("Set", buffer, 70, true);

    formatTemperatureString(buffer, hasOutdoorTemperature, outdoorTemperature);
    drawTemperature("Out", buffer, 135, false);

    gfx.setCursor(10, 80);
    gfx.setFont(&FreeSansBold9pt7b);
    gfx.print("AC: ");
    gfx.print(isCoolingEnabled ? "On" : "Off");
}

void Display200x200::drawTemperature(
        const char label[],
        const char temperature[],
        short xOffset,
        bool withRightBorder
) {
    if (withRightBorder) {
        gfx.drawFastVLine(xOffset + 65, 5, 50, 0x0000);
    }

    gfx.drawFastHLine(xOffset + 5, 60, 55, 0x0000);
    gfx.setTextColor(0x0000);

    int16_t textRectLeft, textRectTop;
    uint16_t textRectWidth, textRectHeight;

    gfx.setFont(&FreeSans9pt7b);
    gfx.getTextBounds(label, 0, 0, &textRectLeft, &textRectTop, &textRectWidth, &textRectHeight);
    gfx.setCursor(xOffset + 5, 15);
    gfx.print(label);

    gfx.setFont(&FreeSansBold9pt7b);
    gfx.getTextBounds(temperature, 0, 0, &textRectLeft, &textRectTop, &textRectWidth, &textRectHeight);
    gfx.setCursor(xOffset + (65 - textRectWidth) / 2, 45);
    gfx.print(temperature);
}
