#include "Displays/AdafruitGFX/Display200x200.h"
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>

using namespace ACC::Displays::AdafruitGFX;

Display200x200::Display200x200(Adafruit_GFX &gfx) :
        gfx(gfx) {

}

void Display200x200::draw() {
    char indoorTempString[10];
    char outdoorTempString[10];
    char targetTempString[10];

    temperatureToString(indoorTempString, hasIndoorTemperature, indoorTemperature);
    drawTemperature("Indoor", indoorTempString, 0, false, true);

    temperatureToString(targetTempString, hasTargetTemperature, targetTemperature);
    drawTemperature("Target", targetTempString, 60, false, true);

    temperatureToString(outdoorTempString, hasOutdoorTemperature, outdoorTemperature);
    drawTemperature("Outdoor", outdoorTempString, 120, false, false);
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

    int16_t textRectLeft, textRectTop;
    uint16_t textRectWidth, textRectHeight;

    gfx.setFont(&FreeSans9pt7b);
    gfx.getTextBounds(label, 0, 0, &textRectLeft, &textRectTop, &textRectWidth, &textRectHeight);
    Serial.println(textRectTop, textRectHeight);
    gfx.setCursor(xOffset + 5, textRectTop + textRectHeight);
    gfx.print(label);

    gfx.setFont(&FreeSansBold12pt7b);
    gfx.getTextBounds(temperature, 0, 0, &textRectLeft, &textRectTop, &textRectWidth, &textRectHeight);
    gfx.setCursor((60 - textRectWidth) / 2 + 10, 25 + textRectTop + textRectHeight);
    gfx.print(temperature);
}
