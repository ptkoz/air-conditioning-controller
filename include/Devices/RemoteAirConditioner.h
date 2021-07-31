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

            /** Timestamp of last received ping */
            Time::Timestamp lastPingTimestamp = Time::Timestamp(0);

            /**
             * Can we turn on? (prevents turning on when we are in the grace period after turn off
             */
            bool canTurnOn() const {
                return getStatus() != AirConditionerStatus::UNAVAILABLE &&
                lastTurnOffTimestamp.getMinAgeSeconds() >= minGracePeriodSeconds;
            }

            /**
             * Can we turn off? (prevents turning off when we are in the grace period after turn on
             */
            bool canTurnOff() const {
                return getStatus() != AirConditionerStatus::UNAVAILABLE &&
                lastTurnOnTimestamp.getMinAgeSeconds() >= minGracePeriodSeconds;
            }
        public:
            explicit RemoteAirConditioner(
                Controller::RemoteCommand::Executor & remoteExecutor,
                const Time::Source & timeSource
            ):
                remoteExecutor(remoteExecutor),
                timeSource(timeSource) {}

            /**
             * Initializes the remote Air Conditioner
             */
            void initialize();

            /**
             * Gets the AC current status
             */
            AirConditionerStatus getStatus() const override;

            /**
             * Turns on the device on if possible. Device cannot be turned on in grace period after turn off.
             * When force repeat is specified, the signal will be send even when we expect it to be already turned on.
             */
            void turnOn(bool forceRepeat = false) override;

            /**
             * Turns off the device on if possible. Device cannot be turned off in grace period after turn on.
             * When force repeat is specified, the signal will be send even when we expect it to be already turned off.
             */
            void turnOff(bool forceRepeat = false) override;

            /**
             * Acknowledges that a ping arrived from the device
             */
            void acknowledgePing();
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_REMOTEAIRCONDITIONER_H
