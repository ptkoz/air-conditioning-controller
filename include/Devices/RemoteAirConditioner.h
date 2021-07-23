#ifndef AIR_CONDITIONING_CONTROLLER_REMOTEAIRCONDITIONER_H
#define AIR_CONDITIONING_CONTROLLER_REMOTEAIRCONDITIONER_H

#include "Devices/AirConditioner.h"
#include "Time/Source.h"

namespace ACC::Devices {
    /**
     * Air conditioner implementation for a remote device controller over HC-12
     */
    class RemoteAirConditioner : public AirConditioner {
        public:
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

#endif //AIR_CONDITIONING_CONTROLLER_REMOTEAIRCONDITIONER_H
