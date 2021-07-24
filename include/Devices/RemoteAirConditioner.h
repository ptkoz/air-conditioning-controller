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
            /** Minimum amount of time that needs to pass between turn off and turn on (and vice versa) */
            static constexpr unsigned short minGracePeriodSeconds = 300;

            /** Remote command executor */
            Controller::WirelessExecutor & wirelessExecutor;

            /** Reliable source of time */
            const Time::Source & timeSource;

            /** Timestamp of most recent "turn on" operation on the device */
            Time::Timestamp lastTurnOnTimestamp = Time::Timestamp(0);

            /** Timestamp of most recent "turn off" operation on the device */
            Time::Timestamp lastTurnOffTimestamp = Time::Timestamp(0);

            /** Checks whether the device can be turned on or are we in the grace period after recent turn off */
            bool canTurnOn() {
                return lastTurnOffTimestamp.getMinAgeSeconds() > minGracePeriodSeconds;
            }

            /** Checks whether the device can be turned off or are we in the grace period after recent turn on */
            bool canTurnOff() {
                return lastTurnOnTimestamp.getMinAgeSeconds() > minGracePeriodSeconds;
            }

        public:
            /** Constructor */
            explicit RemoteAirConditioner(
                Controller::WirelessExecutor & wirelessExecutor,
                const Time::Source & timeSource
            ):
                wirelessExecutor(wirelessExecutor),
                timeSource(timeSource) {}

            /**
             * Turns on the device on if possible. Device cannot be turned on in grace period after turn off.
             *
             * @return true if signal to turn on has been sent, false otherwise
             */
            bool turnOn() override;

            /**
             * Turns off the device on if possible. Device cannot be turned off in grace period after turn on.
             *
             * @return true if signal to turn off has been sent, false otherwise
             */
            bool turnOff() override;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_REMOTEAIRCONDITIONER_H
