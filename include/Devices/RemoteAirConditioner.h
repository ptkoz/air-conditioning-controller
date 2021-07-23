#ifndef AIR_CONDITIONING_CONTROLLER_REMOTEAIRCONDITIONER_H
#define AIR_CONDITIONING_CONTROLLER_REMOTEAIRCONDITIONER_H

#include "Devices/AirConditioner.h"
#include "Controller/WirelessExecutor.h"
#include "Time/Source.h"

namespace ACC::Devices {
    /**
     * Air conditioner implementation for a remote device controller over HC-12
     */
    class RemoteAirConditioner : public AirConditioner {
        private:
            /** Minimum amount of time that needs to pass between two status changes */
            static constexpr unsigned short minGracePeriodSeconds = 300;

            /** Remote command executor */
            Controller::WirelessExecutor & wirelessExecutor;

            /** Reliable source of time */
            const Time::Source & timeSource;

            /** Timestamp of last device status change */
            Time::Timestamp lastStatusChange;

            /** Checks whether the device can change status or not */
            bool canChangeStatus() {
                return lastStatusChange.getMinAgeSeconds() > minGracePeriodSeconds;
            }

        public:
            /** Constructor */
            explicit RemoteAirConditioner(
                Controller::WirelessExecutor & wirelessExecutor,
                const Time::Source & timeSource
            ):
                wirelessExecutor(wirelessExecutor),
                timeSource(timeSource),
                lastStatusChange(0) {}

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
