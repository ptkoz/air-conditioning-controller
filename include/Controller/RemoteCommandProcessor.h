#ifndef AIR_CONDITIONING_CONTROLLER_REMOTECOMMANDPROCESSOR_H
#define AIR_CONDITIONING_CONTROLLER_REMOTECOMMANDPROCESSOR_H

#include <Stream.h>
#include <Time/Timestamp.h>
#include <Time/Source.h>
#include "RemoteCommandExecutor.h"
#include "Displays/Display.h"

namespace ACC::Controller::RemoteCommand {
    /**
     * Wireless controller reads remote commands and reacts to them. It can also sent commands to other devices.
     */
    class Processor : public Executor {
        private:
            /** Address to listen commands for */
            static constexpr unsigned short listenAddress = 0xA1;

            /** Recognized commands */
            static constexpr unsigned short setSecondaryTemperatureAndHumidity = 0x21;

            /** Recognized commands */
            static constexpr unsigned short setOutdoorTemperature = 0x41;

            /**
             * If we don't get a new reading from remote sensor after this number of seconds we will reset the display
             * to indicate sensor is unavailable.
             */
            static constexpr unsigned short sensorTimeout = 1800; // seconds, means 30 minutes

            Displays::Display & display;
            Stream & stream;
            unsigned char setPin;
            const Time::Source & timeSource;

            Time::Timestamp lastSecondarySensorReceive = Time::Timestamp();
            Time::Timestamp lastOutdoorSensorReceive = Time::Timestamp();

            void enterATMode();
            void leaveATMode();
        public:
            explicit Processor(
                Displays::Display & display,
                Stream & dataStream,
                unsigned char setPin,
                const Time::Source & timeSource
            ):
                display(display),
                stream(dataStream),
                setPin(setPin),
                timeSource(timeSource) {}

            void initialize();
            void process();

            void execute(
                unsigned short address,
                unsigned short command,
                const void * message,
                size_t length
            ) override;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_REMOTECOMMANDPROCESSOR_H
