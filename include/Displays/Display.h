#ifndef AIR_CONDITIONING_CONTROLLER_DISPLAY_H
#define AIR_CONDITIONING_CONTROLLER_DISPLAY_H

#include "Measures/Temperature.h"
#include "Measures/Humidity.h"
#include "Devices/AirConditioner.h"

namespace ACC::Displays {
    /**
     * Information display for Air Conditioning Controller
     */
    class Display {
        public:
            /** Sets outdoor temperature */
            virtual void setOutdoorTemperature(const Measures::Temperature & temperature) = 0;

            /** Sets the primary temperature */
            virtual void setPrimaryTemperature(const Measures::Temperature & temperature, bool withWarning) = 0;

            /** Sets the primary humidity */
            virtual void setPrimaryHumidity(const Measures::Humidity & humidity) = 0;

            /** Sets the secondary temperature */
            virtual void setSecondaryTemperature(const Measures::Temperature & temperature) = 0;

            /** Sets the secondary humidity */
            virtual void setSecondaryHumidity(const Measures::Humidity & humidity) = 0;

            /** Sets the visibility of the air conditioning section */
            virtual void setAirConditioningSectionVisibility(bool isVisible) = 0;

            /** Sets the target for the primary temperature */
            virtual void setTargetPrimaryTemperature(const Measures::Temperature & temperature) = 0;

            /** Set indicator status for whether air conditioning is enabled or not */
            virtual void setAirConditionerStatus(Devices::AirConditionerStatus status) = 0;

            /** Returns true if user has requested to change air conditioning management status */
            virtual bool hasAirConditioningManagementStatusChangeRequest() = 0;

            /** Returns requested air conditioning management status */
            virtual bool getRequestedAirConditioningManagementStatus() = 0;

            /** Returns true if user has requested to change target temperature  */
            virtual bool hasTargetPrimaryTemperatureChangeRequest() = 0;

            /** Returns requested target primary temperature */
            virtual float getRequestedPrimaryTargetTemperature() = 0;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_DISPLAY_H
