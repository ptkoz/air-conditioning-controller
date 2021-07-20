#ifndef AIR_CONDITIONING_CONTROLLER_DIMPLEXPC35AMB_H
#define AIR_CONDITIONING_CONTROLLER_DIMPLEXPC35AMB_H

#include "Devices/AirConditioner.h"
#include "Time/Source.h"
#include <IRSend.h>

namespace ACC::Devices::AirConditioners {
    /**
     * Air conditioner implementation for Dimplex device
     */
    class DimplexPC35AMB : public AirConditioner {
        private:
            /** Reliable source of time */
            const Time::Source & timeSource;

            /** Timestamp of last device status change */
            Time::Timestamp lastStatusChange;

            /** IR Emitter frequency */
            const unsigned char irFrequency;

            /** IR emitter that sends signals to the device */
            IRsend & irEmitter;

            /** Whether device can be turned on / off */
            bool canChangeStatus() const;
        public:
            /** Initializes the device with an IR receiver */
            explicit DimplexPC35AMB(IRsend & irEmitter, const Time::Source & timeSource);

            /**
             * Turns on the device on if possible. Device cannot be turned on in grace period after previous turn on / off.
             *
             * @return true if signal to turn on has been sent, false otherwise
             */
            bool turnOn() override;

            /**
             * Turns off the device on if possible. Device cannot be turned on in grace period after previous turn on / off.
             *
             * @return true if signal to turn off has been sent, false otherwise
             */
            bool turnOff() override;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_DIMPLEXPC35AMB_H
