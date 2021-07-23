#include "Displays/Display320x240.h"
#include "Displays/fonts/NumericFontBig.h"
#include "Displays/fonts/NumericFontSmall.h"
#include "Displays/fonts/LabelFont.h"

using namespace ACC::Displays;

Display320x240::Display320x240(Adafruit_GFX & gfx):
    gfx(gfx) {}

void Display320x240::initialize() {
    gfx.setRotation(1);

    gfx.fillScreen(backgroundColor);
    gfx.setTextColor(standardFontColor);
    gfx.setFont(&LabelFont);

    gfx.setCursor(5, 20);
    gfx.print(F("Za oknem"));

    gfx.setCursor(5, 95);
    gfx.print(F("Salon"));

    gfx.setCursor(5, 175);
    gfx.print(F("Sypialnia"));

    gfx.drawFastHLine(5, 75, 310, separatorColor);
    gfx.drawFastHLine(5, 155, 310, separatorColor);

    redrawOutdoorTemperature("", outdoorTemperature.getFormattedTemperature());
    redrawPrimaryTemperature("", primaryTemperature.getFormattedTemperature(), standardFontColor);
    redrawPrimaryHumidity("", primaryHumidity.getFormattedHumidity());
    redrawTargetPrimaryTemperature("", targetPrimaryTemperature.getFormattedTemperature());
    redrawCoolingIndicator("", "AC: Off");
    redrawSecondaryTemperature("", secondaryTemperature.getFormattedTemperature());
    redrawSecondaryHumidity("", secondaryHumidity.getFormattedHumidity());
}

void Display320x240::redrawOutdoorTemperature(const char * oldText, const char * newText) {
    redrawText(oldText, newText, 5, 60, standardFontColor, &NumericFontBig);
}

void Display320x240::redrawPrimaryTemperature(const char * oldText, const char * newText, unsigned int color) {
    redrawText(oldText, newText, 5, 135, color, &NumericFontBig);
}

void Display320x240::redrawPrimaryHumidity(const char * oldText, const char * newText) {
    redrawText(oldText, newText, 150, 135, standardFontColor, &NumericFontSmall);
}

void Display320x240::redrawTargetPrimaryTemperature(const char * oldText, const char * newText) {
    redrawText(oldText, newText, 240, 135, standardFontColor, &NumericFontSmall);
}

void Display320x240::redrawCoolingIndicator(const char * oldText, const char * newNext) {
    redrawText(oldText, newNext, 240, 115, standardFontColor, &NumericFontSmall);
}

void Display320x240::redrawSecondaryTemperature(const char * oldText, const char * newText) {
    redrawText(oldText, newText, 5, 215, standardFontColor, &NumericFontBig);
}

void Display320x240::redrawSecondaryHumidity(const char * oldText, const char * newText) {
    redrawText(oldText, newText, 150, 215, standardFontColor, &NumericFontSmall);
}

void Display320x240::setOutdoorTemperature(const Measures::Temperature & temperature) {
    if (temperature != outdoorTemperature) {
        redrawOutdoorTemperature(
            outdoorTemperature.getFormattedTemperature(),
            temperature.getFormattedTemperature()
        );
        outdoorTemperature = temperature;
    }
}

void Display320x240::setPrimaryTemperature(const Measures::Temperature & temperature, bool withWarning) {
    if (primaryTemperature != temperature || withWarning != hasPrimaryTemperatureWarning) {
        redrawPrimaryTemperature(
            primaryTemperature.getFormattedTemperature(),
            temperature.getFormattedTemperature(),
            hasPrimaryTemperatureWarning ? warningFontColor : standardFontColor
        );
        primaryTemperature = temperature;
        hasPrimaryTemperatureWarning = withWarning;
    }
}

void Display320x240::setPrimaryHumidity(const ACC::Measures::Humidity & humidity) {
    if (primaryHumidity != humidity) {
        redrawPrimaryHumidity(
            primaryHumidity.getFormattedHumidity(),
            humidity.getFormattedHumidity()
        );
        primaryHumidity = humidity;
    }
}

void Display320x240::setTargetPrimaryTemperature(const Measures::Temperature & temperature) {
    if (targetPrimaryTemperature != temperature) {
        redrawTargetPrimaryTemperature(
            targetPrimaryTemperature.getFormattedTemperature(),
            temperature.getFormattedTemperature()
        );
        targetPrimaryTemperature = temperature;
    }
}

void Display320x240::setCoolingIndicator(bool isCooling) {
    if (hasCoolingIndicator != isCooling) {
        redrawCoolingIndicator(
            hasCoolingIndicator ? "AC: On" : "AC: Off",
            isCooling ? "AC: On" : "AC: Off"
        );
        hasCoolingIndicator = isCooling;
    }
}

void Display320x240::setSecondaryTemperature(const Measures::Temperature & temperature) {
    if (secondaryTemperature != temperature) {
        redrawSecondaryTemperature(
            secondaryTemperature.getFormattedTemperature(),
            temperature.getFormattedTemperature()
        );
        secondaryTemperature = temperature;
    }
}

void Display320x240::setSecondaryHumidity(const ACC::Measures::Humidity & humidity) {
    if (secondaryHumidity != humidity) {
        redrawSecondaryHumidity(
            secondaryHumidity.getFormattedHumidity(),
            humidity.getFormattedHumidity()
        );
        secondaryHumidity = humidity;
    }
}

void Display320x240::redrawText(
    const char * oldText,
    const char * newText,
    short xOffset,
    short yOffset,
    unsigned int color,
    const GFXfont * font
) {
    int16_t textRectLeft, textRectTop;
    uint16_t textRectWidth, textRectHeight;

    gfx.setFont(font);
    gfx.getTextBounds(oldText, xOffset, yOffset, &textRectLeft, &textRectTop, &textRectWidth, &textRectHeight);
    gfx.fillRect(textRectLeft, textRectTop, (short) textRectWidth, (short) textRectHeight, backgroundColor);

    gfx.setCursor(xOffset, yOffset);
    gfx.setTextColor(color);
    gfx.print(newText);
}



