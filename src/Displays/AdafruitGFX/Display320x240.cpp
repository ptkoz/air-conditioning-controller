#include "Displays/AdafruitGFX/Display320x240.h"
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>

using namespace ACC::Displays::AdafruitGFX;

Display320x240::Display320x240(Adafruit_GFX & gfx) :
        gfx(gfx) {}

void Display320x240::drawTemperature(
        const char * oldTemperature,
        const char * newTemperature,
        short xOffset,
        short yOffset,
        bool withWarning,
        const GFXfont * font
) {
    int16_t textRectLeft, textRectTop;
    uint16_t textRectWidth, textRectHeight;

    gfx.setFont(font);
    gfx.getTextBounds(oldTemperature, xOffset, yOffset, &textRectLeft, &textRectTop, &textRectWidth, &textRectHeight);
    gfx.fillRect(textRectLeft, textRectTop, (short) textRectWidth, (short) textRectHeight, backgroundColor);

    gfx.setCursor(xOffset, yOffset);
    gfx.setTextColor(withWarning ? warningFontColor : defaultFontColor);
    gfx.print(newTemperature);
}

void Display320x240::initialize() {
    gfx.setRotation(1);

    gfx.fillScreen(backgroundColor);
    gfx.setTextColor(defaultFontColor);
    gfx.setFont(&FreeSans9pt7b);

    gfx.setCursor(5, 20);
    gfx.print(F("Salon"));

    gfx.setCursor(5, 95);
    gfx.print(F("Sypialnia"));

    gfx.setCursor(5, 175);
    gfx.print(F("Za oknem"));

    gfx.drawFastHLine(5, 75, 310, separatorColor);
    gfx.drawFastHLine(5, 155, 310, separatorColor);

    drawIndoorTemperature(currentIndoorTemperature, hasIndoorTemperatureWarning);
    drawTargetTemperature(currentTargetTemperature);
    drawSecondTemperature(currentTargetTemperature);
    drawOutdoorTemperature(currentOutdoorTemperature);
    drawCoolingIndicator(hasCoolingIndicator);
}

void Display320x240::setIndoorTemperature(double temperature, bool withWarning) {
    char buffer[10];
    formatTemperatureString(buffer, true, temperature);

    if (strcmp(buffer, currentIndoorTemperature) != 0 || withWarning != hasIndoorTemperatureWarning) {
        drawIndoorTemperature(buffer, withWarning);
    }
}

void Display320x240::setTargetTemperature(double temperature) {
    char buffer[10];
    formatTemperatureString(buffer, true, temperature);

    if (strcmp(buffer, currentTargetTemperature) != 0) {
        drawTargetTemperature(buffer);
    }
}

void Display320x240::setOutdoorTemperature(double temperature) {
    char buffer[10];
    formatTemperatureString(buffer, true, temperature);

    if (strcmp(buffer, currentOutdoorTemperature) != 0) {
        drawOutdoorTemperature(buffer);
    }
}

void Display320x240::setCoolingIndicator(bool isCooling) {
    if (isCooling != hasCoolingIndicator) {
        drawCoolingIndicator(isCooling);
    }
}

void Display320x240::drawIndoorTemperature(const char * temperature, bool hasWarning) {
    drawTemperature(currentIndoorTemperature, temperature, 5, 60, hasWarning, &FreeSansBold18pt7b);
    strcpy(currentIndoorTemperature, temperature);
    hasIndoorTemperatureWarning = hasWarning;
}

void Display320x240::drawTargetTemperature(const char * temperature) {
    drawTemperature(currentTargetTemperature, temperature, 140, 60, false, &FreeSans9pt7b);
    strcpy(currentTargetTemperature, temperature);
}

void Display320x240::drawSecondTemperature(const char * temperature) {
    drawTemperature(currentIndoorTemperature, temperature, 5, 135, false, &FreeSansBold18pt7b);
    strcpy(currentIndoorTemperature, temperature);
}

void Display320x240::drawOutdoorTemperature(const char * temperature) {
    drawTemperature(currentOutdoorTemperature, temperature, 5, 215, false, &FreeSansBold18pt7b);
    strcpy(currentOutdoorTemperature, temperature);
}

void Display320x240::drawCoolingIndicator(bool isCooling) {
    int16_t textRectLeft, textRectTop;
    uint16_t textRectWidth, textRectHeight;

    gfx.setFont(&FreeSans9pt7b);
    gfx.getTextBounds(
            hasCoolingIndicator ? F("AC: On") : F("AC: Off"),
            240,
            60,
            &textRectLeft,
            &textRectTop,
            &textRectWidth,
            &textRectHeight
    );
    gfx.fillRect(textRectLeft, textRectTop, (short) textRectWidth, (short) textRectHeight, backgroundColor);

    gfx.setCursor(240, 60);

    gfx.print(isCooling ? F("AC: On") : F("AC: Off"));
    hasCoolingIndicator = isCooling;
}
