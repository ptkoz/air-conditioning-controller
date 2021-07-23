#ifndef AIR_CONDITIONING_CONTROLLER_DISPLAY320X240_H
#define AIR_CONDITIONING_CONTROLLER_DISPLAY320X240_H

#include "Display.h"
#include <Adafruit_GFX.h>

namespace ACC::Displays {
    /**
     * 320x240 display implementation in Adafruit GFX Library
     */
    class Display320x240 : public Display {
        protected:
            static constexpr unsigned int backgroundColor = 0x0000;
            static constexpr unsigned int standardFontColor = 0xffff;
            static constexpr unsigned int warningFontColor = 0xfa00;
            static constexpr unsigned int separatorColor = 0x001f;

            Adafruit_GFX & gfx;

            Measures::Temperature outdoorTemperature = Measures::Temperature();
            Measures::Temperature primaryTemperature = Measures::Temperature();
            Measures::Temperature targetPrimaryTemperature = Measures::Temperature();
            Measures::Temperature secondaryTemperature = Measures::Temperature();

            Measures::Humidity primaryHumidity = Measures::Humidity();
            Measures::Humidity secondaryHumidity = Measures::Humidity();

            bool hasPrimaryTemperatureWarning = false;
            bool hasCoolingIndicator = false;

            /** Redraws text box in given cursor position */
            void redrawText(
                const char * oldText,
                const char * newText,
                short xOffset,
                short yOffset,
                unsigned int color,
                const GFXfont * font
            );

            void redrawOutdoorTemperature(const char * oldText, const char * newText);
            void redrawPrimaryTemperature(const char * oldText, const char * newText, unsigned int color);
            void redrawPrimaryHumidity(const char * oldText, const char * newText);
            void redrawTargetPrimaryTemperature(const char * oldText, const char * newText);
            void redrawCoolingIndicator(const char * oldText, const char * newNext);
            void redrawSecondaryTemperature(const char * oldText, const char * newText);
            void redrawSecondaryHumidity(const char * oldText, const char * newText);
        public:
            explicit Display320x240(Adafruit_GFX & gfx);
            virtual void initialize();

            void setOutdoorTemperature(const Measures::Temperature & temperature) override;
            void setPrimaryTemperature(const Measures::Temperature & temperature, bool withWarning) override;
            void setPrimaryHumidity(const Measures::Humidity & humidity) override;
            void setTargetPrimaryTemperature(const Measures::Temperature & temperature) override;
            void setCoolingIndicator(bool isCooling) override;
            void setSecondaryTemperature(const Measures::Temperature & temperature) override;
            void setSecondaryHumidity(const Measures::Humidity & humidity) override;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_DISPLAY320X240_H
