#include "Devices/RemoteAirConditioner.h"


using namespace ACC::Devices;


bool RemoteAirConditioner::turnOn() {
    if (!canTurnOn()) {
        return false;
    }

    wirelessExecutor.remoteCommand(0xA2, 0x01);
    lastTurnOnTimestamp = timeSource.currentTimestamp();
    return true;
}

bool RemoteAirConditioner::turnOff() {
    if (!canTurnOff()) {
        return false;
    }

    wirelessExecutor.remoteCommand(0xA2, 0x02);
    lastTurnOffTimestamp = timeSource.currentTimestamp();
    return true;
}
