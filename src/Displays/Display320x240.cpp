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
    redrawMenuControls();
}

void Display320x240::redrawTargetPrimaryTemperatureConfiguration(const char * oldText, const char * newText) {
    redrawText(oldText, newText, 87, 195, menuBackgroundColor, standardFontColor, &NumericFontBig);
}

void Display320x240::redrawMenuControls() {
    gfx.setFont(&LabelFont);
    gfx.setTextColor(standardFontColor);
    gfx.setCursor(5, 20);
    gfx.print("Sterowanie AC");

    gfx.drawRoundRect(5, 30, 100, 50, 5, standardFontColor);
    gfx.fillRoundRect(6, 31, 98, 48, 5, hasAirConditioningSectionVisible ? standardFontColor : menuBackgroundColor);
    gfx.setTextColor(hasAirConditioningSectionVisible ? menuBackgroundColor : standardFontColor);
    gfx.setCursor(42, 60);
    gfx.print("TAK");

    gfx.drawRoundRect(115, 30, 100, 50, 5, standardFontColor);
    gfx.fillRoundRect(116, 31, 98, 48, 5, hasAirConditioningSectionVisible ? menuBackgroundColor : standardFontColor);
    gfx.setTextColor(hasAirConditioningSectionVisible ? standardFontColor : menuBackgroundColor);
    gfx.setCursor(152, 60);
    gfx.print("NIE");

    gfx.drawRoundRect(225, 30, 90, 50, 5, standardFontColor);
    gfx.fillRoundRect(226, 31, 88, 48, 5, backgroundColor);
    gfx.setTextColor(standardFontColor);
    gfx.setCursor(236, 60);
    gfx.print("POWROT");

    if (hasAirConditioningSectionVisible) {
        gfx.setTextColor(standardFontColor);
        gfx.setFont(&NumericFontSmall);

        gfx.drawRoundRect(5, 140, 80, 40, 5, standardFontColor);
        gfx.fillRoundRect(6, 141, 78, 38, 5, menuBackgroundColor);
        gfx.setCursor(18, 165);
        gfx.print("-0.1C");

        gfx.drawRoundRect(5, 190, 80, 40, 5, standardFontColor);
        gfx.fillRoundRect(6, 191, 78, 38, 5, menuBackgroundColor);
        gfx.setCursor(18, 215);
        gfx.print("-1.0C");

        gfx.drawRoundRect(235, 140, 80, 40, 5, standardFontColor);
        gfx.fillRoundRect(236, 141, 78, 38, 5, menuBackgroundColor);
        gfx.setCursor(248, 165);
        gfx.print("+0.1C");

        gfx.drawRoundRect(235, 190, 80, 40, 5, standardFontColor);
        gfx.fillRoundRect(236, 191, 78, 38, 5, menuBackgroundColor);
        gfx.setCursor(248, 215);
        gfx.print("+1.0C");

        redrawTargetPrimaryTemperatureConfiguration(
            targetPrimaryTemperature.getFormattedTemperature(),
            targetPrimaryTemperature.getFormattedTemperature()
        );
    } else {
        gfx.fillRoundRect(5, 140, 80, 40, 5, menuBackgroundColor);
        gfx.fillRoundRect(5, 190, 80, 40, 5, menuBackgroundColor);
        gfx.fillRoundRect(235, 140, 80, 40, 5, menuBackgroundColor);
        gfx.fillRoundRect(235, 190, 80, 40, 5, menuBackgroundColor);
        redrawTargetPrimaryTemperatureConfiguration(
            targetPrimaryTemperature.getFormattedTemperature(),
            ""
        );
    }
}

bool inline Display320x240::isBackButtonTouched() const {
    return touchPoint.x >= 225 && touchPoint.x <= 315 && touchPoint.y >= 30 && touchPoint.y <= 80;
}

bool inline Display320x240::isAcYesButtonTouched() const {
    return touchPoint.x >= 5 && touchPoint.x <= 105 && touchPoint.y >= 30 && touchPoint.y <= 80;
}

bool inline Display320x240::isAcNoButtonTouched() const {
    return touchPoint.x >= 115 && touchPoint.x <= 215 && touchPoint.y >= 30 && touchPoint.y <= 80;
}

bool inline Display320x240::isAddTemp1ButtonTouched() const {
    return touchPoint.x >= 235 && touchPoint.x <= 315 && touchPoint.y >= 140 && touchPoint.y <= 180;
}

bool inline Display320x240::isAddTemp2ButtonTouched() const {
    return touchPoint.x >= 235 && touchPoint.x <= 315 && touchPoint.y >= 190 && touchPoint.y <= 230;
}

bool inline Display320x240::isSubTemp1ButtonTouched() const {
    return touchPoint.x >= 5 && touchPoint.x <= 85 && touchPoint.y >= 140 && touchPoint.y <= 180;
}

bool inline Display320x240::isSubTemp2ButtonTouched() const {
    return touchPoint.x >= 5 && touchPoint.x <= 85 && touchPoint.y >= 190 && touchPoint.y <= 230;
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

        if (hasMenuDisplayed) {
            redrawMenuControls();
        }
    }
}

void Display320x240::setTargetPrimaryTemperature(const Measures::Temperature & temperature) {
    if (targetPrimaryTemperature != temperature) {
        if (hasAirConditioningSectionVisible) {
            if (!hasMenuDisplayed) {
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
            touchPoint.z = currentPoint.z;
        } else if (touchStartTimestamp.getMinAgeMillis() > trustworthyTouchDuration) {
            // the touch lasts longer than 10ms, record as trustworthy touch
            lastTouchTimestamp = timeSource.currentTimestamp();

            if (hasMenuDisplayed) {
                // save coordinates, so we know what element in the menu user interacted with */
                touchPoint.x = (int16_t) (map(currentPoint.y, 90, 910, gfx.width(), 0));
                touchPoint.y = (int16_t) (gfx.height() - map(currentPoint.x, 120, 920, gfx.height(), 0));
                touchPoint.z = currentPoint.z;

                if (isBackButtonTouched()) {
                    // exit immediately
                    displayInfoScreen();
                }

            } else {
                // enable the menu
                displayMenuScreen();
            }
        }
    } else {
        // Adafruit touchscreen seems to float a lot, don't release until at least 10ms passes from initial touch start.
        // This way we effectively check whether touch has begun and still continues after 10ms, rather that checking
        // whether it continues for 10ms consecutively.
        if (touchPoint.z > touchScreen.pressureThreshhold &&
            touchStartTimestamp.getMinAgeMillis() > trustworthyTouchDuration) {
            // touch released, reset values
            touchPoint.x = touchPoint.y = touchPoint.z = -1;
        }

        // if nothing is being touched for grace e period, close menu
        if (hasMenuDisplayed && lastTouchTimestamp.getMinAgeSeconds() > menuDisableInactivityTimeout) {
            displayInfoScreen();
        }
    }
}

bool Display320x240::hasAirConditioningManagementStatusChangeRequest() {
    return isAcYesButtonTouched() || isAcNoButtonTouched();
}

bool Display320x240::getRequestedAirConditioningManagementStatus() {
    if (isAcYesButtonTouched()) {
        return true;
    }

    if (isAcNoButtonTouched()) {
        return false;
    }

    return hasAirConditioningSectionVisible;
}

bool Display320x240::hasTargetPrimaryTemperatureChangeRequest() {
    return isAddTemp1ButtonTouched() || isAddTemp2ButtonTouched() || isSubTemp1ButtonTouched() ||
           isSubTemp2ButtonTouched();
}

double Display320x240::getRequestedPrimaryTargetTemperature() {
    double requestedTargetTemperature = targetPrimaryTemperature.getTemperature();

    if (isAddTemp1ButtonTouched()) {
        requestedTargetTemperature = targetPrimaryTemperature.getTemperature() + 0.1f;
    }

    if (isAddTemp2ButtonTouched()) {
        requestedTargetTemperature = targetPrimaryTemperature.getTemperature() + 1.0f;
    }

    if (isSubTemp1ButtonTouched()) {
        requestedTargetTemperature = targetPrimaryTemperature.getTemperature() - 0.1f;
    }

    if (isSubTemp2ButtonTouched()) {
        requestedTargetTemperature = targetPrimaryTemperature.getTemperature() - 1.0f;
    }

    if (requestedTargetTemperature > 30.0f) {
        requestedTargetTemperature = 30.0f;
    }

    if (requestedTargetTemperature < 17.0f) {
        requestedTargetTemperature = 17.0f;
    }

    return requestedTargetTemperature;
}
