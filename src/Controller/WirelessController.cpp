#include "Controller/WirelessController.h"

using ACC::Controller::WirelessController;

void WirelessController::initialize() {
    pinMode(setPin, OUTPUT);
    digitalWrite(setPin, LOW);

    dataStream.print("AT+C003");
    while(dataStream.read() != -1);

    dataStream.print("AT+FU1");
    while(dataStream.read() != -1);

    dataStream.print("AT+B9600");
    while(dataStream.read() != -1);

    pinMode(setPin, INPUT);
    digitalWrite(setPin, LOW);

    dataStream.setTimeout(1000);
}

void WirelessController::remoteCommand(
    unsigned short address,
    unsigned short command,
    const void * message,
    size_t length
) {
    dataStream.write(static_cast<const char *>(static_cast<const void *>(&address)), sizeof address);
    dataStream.write(static_cast<const char *>(static_cast<const void *>(&command)), sizeof command);
    dataStream.write(static_cast<const char *>(message), length);
    dataStream.write((char) 0);
}
