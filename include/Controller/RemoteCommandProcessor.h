#ifndef AIR_CONDITIONING_CONTROLLER_REMOTECOMMANDPROCESSOR_H
#define AIR_CONDITIONING_CONTROLLER_REMOTECOMMANDPROCESSOR_H

#include <Stream.h>
#include "Time/Timestamp.h"
#include "Time/Source.h"
#include "Devices/RemoteAirConditioner.h"
#include "Displays/Display.h"
#include "RemoteCommandRadio.h"

namespace ACC::Controller::RemoteCommand {
    /**
     * Wireless controller reads remote commands and reacts to them. It can also sent commands to other devices.
     */
    class Processor {
        private:
            /** Address to listen commands for */
            static constexpr unsigned short listenAddress = 0xA1;

            /** Recognized commands */
            static constexpr unsigned short setSecondaryTemperatureAndHumidity = 0x21;
            static constexpr unsigned short setOutdoorTemperature = 0x41;
            static constexpr unsigned short acReceiverPing = 0x90;

            /**
             * If we don't get a new reading from remote sensor after this number of seconds we will reset the display
             * to indicate sensor is unavailable.
             */
            static constexpr unsigned short sensorTimeout = 1800; // seconds, means 30 minutes

            Displays::Display & display;
            Devices::RemoteAirConditioner & remoteAirConditioner;
            Stream & stream;
            const Time::Source & timeSource;

            Time::Timestamp lastSecondarySensorReceive = Time::Timestamp();
            Time::Timestamp lastOutdoorSensorReceive = Time::Timestamp();
        public:
            explicit Processor(
                Displays::Display & display,
                Devices::RemoteAirConditioner & remoteAirConditioner,
                const Radio & radio,
                const Time::Source & timeSource
            ):
                display(display),
                remoteAirConditioner(remoteAirConditioner),
                stream(radio.getStream()),
                timeSource(timeSource) {}

            void process();
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_REMOTECOMMANDPROCESSOR_H
