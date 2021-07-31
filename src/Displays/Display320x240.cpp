#include "Displays/Display320x240.h"
#include "Displays/fonts/NumericFontBig.h"
#include "Displays/fonts/NumericFontSmall.h"
#include "Displays/fonts/LabelFont.h"
#include <string.h>

using namespace ACC::Displays;
using ACC::Devices::AirConditionerStatus;

void Display320x240::initialize() {
    gfx.setRotation(3);
    displayInfoScreen();
}

void Display320x240::displayInfoScreen() {
    hasMenuDisplayed = false;
    gfx.fillScreen(backgroundColor);
    gfx.setTextColor(standardFontColor);
    gfx.setFont(&LabelFont);

    gfx.setCursor(5, 20);
    gfx.print("Za oknem");

    gfx.setCursor(5, 95);
    gfx.print("Salon");

    gfx.setCursor(5, 175);
    gfx.print("Sypialnia");

    gfx.drawFastHLine(5, 75, 310, separatorColor);
    gfx.drawFastHLine(5, 155, 310, separatorColor);

    redrawOutdoorTemperature("", outdoorTemperature.getFormattedTemperature());
    redrawPrimaryTemperature("", primaryTemperature.getFormattedTemperature(), standardFontColor);
    redrawPrimaryHumidity("", primaryHumidity.getFormattedHumidity());
    redrawSecondaryTemperature("", secondaryTemperature.getFormattedTemperature());
    redrawSecondaryHumidity("", secondaryHumidity.getFormattedHumidity());

    if (hasAirConditioningSectionVisible) {
        redrawTargetPrimaryTemperature("", targetPrimaryTemperature.getFormattedTemperature());
        char buffer[8];
        getAirConditioningStatusText(buffer, airConditionerStatus);
        redrawAirConditioningStatus("", buffer);
    }
}


void Display320x240::redrawOutdoorTemperature(const char * oldText, const char * newText) {
    redrawText(oldText, newText, 5, 60, backgroundColor, standardFontColor, &NumericFontBig);
}

void Display320x240::redrawPrimaryTemperature(const char * oldText, const char * newText, unsigned int color) {
    redrawText(oldText, newText, 5, 135, backgroundColor, color, &NumericFontBig);
}

void Display320x240::redrawPrimaryHumidity(const char * oldText, const char * newText) {
    redrawText(oldText, newText, 150, 135, backgroundColor, standardFontColor, &NumericFontSmall);
}

void Display320x240::redrawSecondaryTemperature(const char * oldText, const char * newText) {
    redrawText(oldText, newText, 5, 215, backgroundColor, standardFontColor, &NumericFontBig);
}

void Display320x240::redrawSecondaryHumidity(const char * oldText, const char * newText) {
    redrawText(oldText, newText, 150, 215, backgroundColor, standardFontColor, &NumericFontSmall);
}

void Display320x240::redrawTargetPrimaryTemperature(const char * oldText, const char * newText) {
    redrawText(oldText, newText, 240, 135, backgroundColor, standardFontColor, &NumericFontSmall);
}

void Display320x240::redrawAirConditioningStatus(const char * oldText, const char * newNext) {
    redrawText(oldText, newNext, 250, 115, backgroundColor, standardFontColor, &LabelFont);
}

void Display320x240::displayMenuScreen() {
    hasMenuDisplayed = true;
    gfx.fillScreen(menuBackgroundColor);
    gfx.setTextColor(standardFontColor);
    gfx.setFont(&NumericFontSmall);

    gfx.drawRoundRect(75, 90, 80, 40, 5, standardFontColor);
    gfx.setCursor(88, 115);
    gfx.print("+1.0C");

    gfx.drawRoundRect(165, 90, 80, 40, 5, standardFontColor);
    gfx.setCursor(178, 115);
    gfx.print("+0.1C");


    gfx.drawRoundRect(75, 190, 80, 40, 5, standardFontColor);
    gfx.setCursor(88, 215);
    gfx.print("-1.0C");

    gfx.drawRoundRect(165, 190, 80, 40, 5, standardFontColor);
    gfx.setCursor(178, 215);
    gfx.print("-0.1C");

    redrawTargetPrimaryTemperatureConfiguration(
        targetPrimaryTemperature.getFormattedTemperature(),
        targetPrimaryTemperature.getFormattedTemperature()
    );
}

void Display320x240::redrawTargetPrimaryTemperatureConfiguration(const char * oldText, const char * newText) {
    redrawText(oldText, newText, 93, 170, menuBackgroundColor, standardFontColor, &NumericFontBig);
}

void Display320x240::setOutdoorTemperature(const Measures::Temperature & temperature) {
    if (temperature != outdoorTemperature) {
        if (!hasMenuDisplayed) {
            redrawOutdoorTemperature(
                outdoorTemperature.getFormattedTemperature(),
                temperature.getFormattedTemperature()
            );
        }

        outdoorTemperature = temperature;
    }
}

void Display320x240::setPrimaryTemperature(const Measures::Temperature & temperature, bool withWarning) {
    if (primaryTemperature != temperature || withWarning != hasPrimaryTemperatureWarning) {
        if (!hasMenuDisplayed) {
            redrawPrimaryTemperature(
                primaryTemperature.getFormattedTemperature(),
                temperature.getFormattedTemperature(),
                hasPrimaryTemperatureWarning ? warningFontColor : standardFontColor
            );
        }

        primaryTemperature = temperature;
        hasPrimaryTemperatureWarning = withWarning;
    }
}

void Display320x240::setPrimaryHumidity(const ACC::Measures::Humidity & humidity) {
    if (primaryHumidity != humidity) {
        if (!hasMenuDisplayed) {
            redrawPrimaryHumidity(
                primaryHumidity.getFormattedHumidity(),
                humidity.getFormattedHumidity()
            );
        }

        primaryHumidity = humidity;
    }
}

void Display320x240::setSecondaryTemperature(const Measures::Temperature & temperature) {
    if (secondaryTemperature != temperature) {
        if (!hasMenuDisplayed) {
            redrawSecondaryTemperature(
                secondaryTemperature.getFormattedTemperature(),
                temperature.getFormattedTemperature()
            );
        }

        secondaryTemperature = temperature;
    }
}

void Display320x240::setSecondaryHumidity(const ACC::Measures::Humidity & humidity) {
    if (secondaryHumidity != humidity) {
        if (!hasMenuDisplayed) {
            redrawSecondaryHumidity(
                secondaryHumidity.getFormattedHumidity(),
                humidity.getFormattedHumidity()
            );
        }

        secondaryHumidity = humidity;
    }
}

void Display320x240::setAirConditioningSectionVisibility(bool isVisible) {
    if (isVisible != hasAirConditioningSectionVisible) {
        if (!hasMenuDisplayed) {
            if (isVisible) {
                redrawTargetPrimaryTemperature("", targetPrimaryTemperature.getFormattedTemperature());

                char acStatusString[8];
                getAirConditioningStatusText(acStatusString, airConditionerStatus);
                redrawAirConditioningStatus("", acStatusString);
            } else {
                redrawTargetPrimaryTemperature(targetPrimaryTemperature.getFormattedTemperature(), "");

                char acStatusString[8];
                getAirConditioningStatusText(acStatusString, airConditionerStatus);
                redrawAirConditioningStatus(acStatusString, "");
            }
        }

        hasAirConditioningSectionVisible = isVisible;
    }
}

void Display320x240::setTargetPrimaryTemperature(const Measures::Temperature & temperature) {
    if (targetPrimaryTemperature != temperature) {
        if (!hasMenuDisplayed && hasAirConditioningSectionVisible) {
            redrawTargetPrimaryTemperature(
                targetPrimaryTemperature.getFormattedTemperature(),
                temperature.getFormattedTemperature()
            );
        } else if (hasMenuDisplayed) {
            redrawTargetPrimaryTemperatureConfiguration(
                targetPrimaryTemperature.getFormattedTemperature(),
                temperature.getFormattedTemperature()
            );
        }

        targetPrimaryTemperature = temperature;
    }
}


void Display320x240::setAirConditionerStatus(AirConditionerStatus status) {
    if (airConditionerStatus != status) {
        if (!hasMenuDisplayed && hasAirConditioningSectionVisible) {
            char oldText[8], newText[8];
            getAirConditioningStatusText(oldText, airConditionerStatus);
            getAirConditioningStatusText(newText, status);
            redrawAirConditioningStatus(oldText, newText);
        }

        airConditionerStatus = status;
    }
}

void Display320x240::getAirConditioningStatusText(char * buffer, AirConditionerStatus status) {
    switch (status) {
        case AirConditionerStatus::TURNED_ON:
            strcpy(buffer, "AC: On");
            break;
        case AirConditionerStatus::TURNED_OFF:
            strcpy(buffer, "AC: Off");
            break;
        default:
            strcpy(buffer, "AC: n/a");
            break;
    }
}

void Display320x240::redrawText(
    const char * oldText,
    const char * newText,
    short xOffset,
    short yOffset,
    unsigned int bgColor,
    unsigned int color,
    const GFXfont * font
) {
    int16_t textRectLeft, textRectTop;
    uint16_t textRectWidth, textRectHeight;

    gfx.setFont(font);
    gfx.getTextBounds(oldText, xOffset, yOffset, &textRectLeft, &textRectTop, &textRectWidth, &textRectHeight);
    gfx.fillRect(textRectLeft, textRectTop, (short) textRectWidth, (short) textRectHeight, bgColor);

    gfx.setCursor(xOffset, yOffset);
    gfx.setTextColor(color);
    gfx.print(newText);
}

void Display320x240::processTouch() {
    TSPoint currentPoint = touchScreen.getPoint();

    if (currentPoint.z > touchScreen.pressureThreshhold) {
        if (touchPoint.z == -1) {
            // this is the start of the touch, record values
            touchStartTimestamp = timeSource.currentTimestamp();
        }

        if (touchStartTimestamp.getMinAgeMillis() > 10) {
            // the touch lasts longer than 10ms, save the point touched
            touchPoint.x = (int16_t) (map(currentPoint.y, 90, 910, gfx.width(), 0));
            touchPoint.y = (int16_t) (gfx.height() - map(currentPoint.x, 120, 920, gfx.height(), 0));
            touchPoint.z = currentPoint.z;
        }
    } else if (touchPoint.z > touchScreen.pressureThreshhold) {
        // touch released, reset values
        touchPoint.x = touchPoint.y = touchPoint.z = -1;
    }
}

bool Display320x240::hasAirConditioningManagementStatusChangeRequest() {
    return false;
}

bool Display320x240::getRequestedAirConditioningManagementStatus() {
    return false;
}

bool Display320x240::hasTargetPrimaryTemperatureChangeRequest() {
    return false;
}

double Display320x240::getRequestedPrimaryTargetTemperature() {
    return 0;
}

