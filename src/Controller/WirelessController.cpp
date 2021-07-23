#include "Controller/WirelessController.h"

using ACC::Controller::WirelessController;

void WirelessController::initialize() {
    AltSoftSerial::begin(9600);
    serial.setTimeout(1000);

    pinMode(setPin, OUTPUT);
    digitalWrite(setPin, LOW);
}

void WirelessController::remoteCommand(
    unsigned short address,
    unsigned short command,
    const void * message,
    size_t length
) {
    serial.write(static_cast<const char *>(static_cast<const void *>(&address)), sizeof address);
    serial.write(static_cast<const char *>(static_cast<const void *>(&command)), sizeof command);
    serial.write(static_cast<const char *>(message), length);
    serial.write((char) 0);
}
