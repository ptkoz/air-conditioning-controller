#ifndef AIR_CONDITIONING_CONTROLLER_DISPLAY320X240_H
#define AIR_CONDITIONING_CONTROLLER_DISPLAY320X240_H

#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include "Display.h"
#include "Time/Source.h"

namespace ACC::Displays {
    /**
     * 320x240 display implementation in Adafruit GFX Library
     */
    class Display320x240 : public Display {
        protected:
            static constexpr unsigned int backgroundColor = 0x0000;
            static constexpr unsigned int menuBackgroundColor = 0x6041;
            static constexpr unsigned int standardFontColor = 0xffff;
            static constexpr unsigned int warningFontColor = 0xFCB3;
            static constexpr unsigned int separatorColor = 0x79A1;

            static constexpr unsigned char trustworthyTouchDuration = 10; // milliseconds
            static constexpr unsigned char menuDisableInactivityTimeout = 15; // seconds

            Adafruit_GFX & gfx;
            TouchScreen & touchScreen;
            const Time::Source & timeSource;

            Measures::Temperature outdoorTemperature = Measures::Temperature();
            Measures::Temperature primaryTemperature = Measures::Temperature();
            Measures::Temperature targetPrimaryTemperature = Measures::Temperature();
            Measures::Temperature secondaryTemperature = Measures::Temperature();

            Measures::Humidity primaryHumidity = Measures::Humidity();
            Measures::Humidity secondaryHumidity = Measures::Humidity();
            Devices::AirConditionerStatus airConditionerStatus = Devices::AirConditionerStatus::UNAVAILABLE;

            bool hasPrimaryTemperatureWarning = false;
            bool hasAirConditioningSectionVisible = false;
            bool hasMenuDisplayed = false;

            /** The point on the screen that is being touched */
            TSPoint touchPoint = TSPoint(-1, -1, -1);

            /** The timestamp when the last potential touch event started */
            Time::Timestamp touchStartTimestamp = Time::Timestamp();

            /** The timestamp when the last trustworthy touch event occurred */
            Time::Timestamp lastTouchTimestamp = Time::Timestamp();

            void getAirConditioningStatusText(char * buffer, Devices::AirConditionerStatus status);

            /** Redraws text box in given cursor position */
            void redrawText(
                const char * oldText,
                const char * newText,
                short xOffset,
                short yOffset,
                unsigned int bgColor,
                unsigned int color,
                const GFXfont * font
            );

            void redrawOutdoorTemperature(const char * oldText, const char * newText);
            void redrawPrimaryTemperature(const char * oldText, const char * newText, unsigned int color);
            void redrawPrimaryHumidity(const char * oldText, const char * newText);
            void redrawTargetPrimaryTemperature(const char * oldText, const char * newText);
            void redrawAirConditioningStatus(const char * oldText, const char * newNext);
            void redrawSecondaryTemperature(const char * oldText, const char * newText);
            void redrawSecondaryHumidity(const char * oldText, const char * newText);

            void redrawMenuControls();
            void redrawTargetPrimaryTemperatureConfiguration(const char * oldText, const char * newText);

            bool inline isBackButtonTouched() const;
            bool inline isAcYesButtonTouched() const;
            bool inline isAcNoButtonTouched() const;
            bool inline isAddTemp1ButtonTouched() const;
            bool inline isAddTemp2ButtonTouched() const;
            bool inline isSubTemp1ButtonTouched() const;
            bool inline isSubTemp2ButtonTouched() const;

            void displayMenuScreen();
            void displayInfoScreen();
        public:
            Display320x240(Adafruit_GFX & gfx, TouchScreen & touchScreen, const Time::Source & timeSource):
                gfx(gfx),
                touchScreen(touchScreen),
                timeSource(timeSource) {}

            virtual void initialize();

            void setOutdoorTemperature(const Measures::Temperature & temperature) override;
            void setPrimaryTemperature(const Measures::Temperature & temperature, bool withWarning) override;
            void setPrimaryHumidity(const Measures::Humidity & humidity) override;
            void setSecondaryTemperature(const Measures::Temperature & temperature) override;
            void setSecondaryHumidity(const Measures::Humidity & humidity) override;

            void setAirConditioningSectionVisibility(bool isVisible) override;
            void setTargetPrimaryTemperature(const Measures::Temperature & temperature) override;
            void setAirConditionerStatus(Devices::AirConditionerStatus status) override;

            /** Process touch events and save outcome for further processing */
            void processTouch();

            bool hasAirConditioningManagementStatusChangeRequest() override;
            bool getRequestedAirConditioningManagementStatus() override;
            bool hasTargetPrimaryTemperatureChangeRequest() override;
            float getRequestedPrimaryTargetTemperature() override;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_DISPLAY320X240_H
