#ifndef AIR_CONDITIONING_CONTROLLER_REMOTEAIRCONDITIONER_H
#define AIR_CONDITIONING_CONTROLLER_REMOTEAIRCONDITIONER_H

#include "Devices/AirConditioner.h"
#include "Controller/RemoteCommandExecutor.h"
#include "Time/Source.h"

namespace ACC::Devices {
    /**
     * Air conditioner implementation for a remote device controller over HC-12
     */
    class RemoteAirConditioner : public AirConditioner {
        private:
            /** Minimum amount of time that needs to pass between turn off and turn on (and vice versa) */
            static constexpr unsigned short minGracePeriodSeconds = 300; // seconds

            /** After this amount of time without a ping we'll consider remote AC unit not available */
            static constexpr unsigned short maxIntervalWithoutPing = 180; // seconds

            /** Remote command executor */
            Controller::RemoteCommand::Executor & remoteExecutor;

            /** Reliable source of time */
            const Time::Source & timeSource;

            /** Timestamp of most recent "turn on" operation on the device */
            Time::Timestamp lastTurnOnTimestamp = Time::Timestamp(0);

            /** Timestamp of most recent "turn off" operation on the device */
            Time::Timestamp lastTurnOffTimestamp = Time::Timestamp(0);

            /** Timestamp of last received ping (negative value to consider unavailable until first ping arrives) */
            Time::Timestamp lastPingTimestamp = Time::Timestamp(-maxIntervalWithoutPing);

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
                Controller::RemoteCommand::Executor & remoteExecutor,
                const Time::Source & timeSource
            ):
                remoteExecutor(remoteExecutor),
                timeSource(timeSource) {}

            /**
             * Returns true if we recently received a ping from remote device.
             */
            bool isAvailable() override {
                return lastPingTimestamp.getMinAgeSeconds() <= maxIntervalWithoutPing;
            }

            /**
             * Acknowledges that a ping arrived from the device
             */
            void acknowledgePing() {
                lastPingTimestamp = timeSource.currentTimestamp();
            }

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
