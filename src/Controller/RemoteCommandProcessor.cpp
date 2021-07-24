#include "Controller/RemoteCommandProcessor.h"

using ACC::Controller::RemoteCommand::Processor;

void Processor::initialize() {
    pinMode(setPin, OUTPUT);
    digitalWrite(setPin, LOW);

    stream.print("AT+C003");
    while (stream.read() != -1);

    stream.print("AT+FU1");
    while (stream.read() != -1);

    stream.print("AT+B9600");
    while (stream.read() != -1);

    pinMode(setPin, INPUT);
    digitalWrite(setPin, LOW);

    stream.setTimeout(1000);
}

void Processor::execute(
    unsigned short address,
    unsigned short command,
    const void * message,
    size_t length
) {
    stream.write(static_cast<const char *>(static_cast<const void *>(&address)), sizeof address);
    stream.write(static_cast<const char *>(static_cast<const void *>(&command)), sizeof command);
    stream.write(static_cast<const char *>(message), length);
    stream.write((char) 0);
}

void ACC::Controller::RemoteCommand::Processor::process() {
    if (lastOutdoorSensorReceive.getMinAgeSeconds() > sensorTimeout) {
        display.setOutdoorTemperature(Measures::Temperature());
        lastOutdoorSensorReceive = timeSource.currentTimestamp();
    }

    if (lastSecondarySensorReceive.getMinAgeSeconds() > sensorTimeout) {
        display.setSecondaryTemperature(Measures::Temperature());
        display.setSecondaryHumidity(Measures::Humidity());
        lastSecondarySensorReceive = timeSource.currentTimestamp();
    }

    if (stream.available()) {
        unsigned short address;
        if (stream.readBytes(static_cast<char *>(static_cast<void *>(&address)), sizeof address) != sizeof address) {
            // unable ro read address, broken transmission?
            return;
        }

        if (address != listenAddress) {
            // advance to the end of the message
            stream.find((unsigned char) 0);
            return;
        }

        unsigned short command;
        if (stream.readBytes(static_cast<char *>(static_cast<void *>(&command)), sizeof command) != sizeof command) {
            // unable to read command, broken transmission?
            return;
        }

        switch (command) {
            case setSecondaryTemperatureAndHumidity: {
                double values[2];
                size_t length = 2 * sizeof values[0];

                if (stream.readBytes(static_cast<char *>(static_cast<void *>(&values)), length) == length) {
                    // temperature * humidity read
                    display.setSecondaryTemperature(Measures::Temperature(values[0]));
                    display.setSecondaryHumidity(Measures::Humidity(values[1]));
                    lastSecondarySensorReceive = timeSource.currentTimestamp();
                    return;
                }

                stream.find((unsigned char) 0);
                break;
            }
            case setOutdoorTemperature: {
                double value;
                size_t length = sizeof value;

                if (stream.readBytes(static_cast<char *>(static_cast<void *>(&value)), length) == length) {
                    // temperature * humidity read
                    display.setOutdoorTemperature(Measures::Temperature(value));
                    lastOutdoorSensorReceive = timeSource.currentTimestamp();
                    return;
                }

                stream.find((unsigned char) 0);
                break;
            }
            default: {
                stream.find((unsigned char) 0);
                break;
            }
        }
    }
}
