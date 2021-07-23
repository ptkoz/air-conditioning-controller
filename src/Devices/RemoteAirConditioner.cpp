#include "Devices/RemoteAirConditioner.h"


using namespace ACC::Devices;


bool RemoteAirConditioner::turnOn() {
    if (!canChangeStatus()) {
        return false;
    }

    wirelessExecutor.remoteCommand(0xA2, 0x01);
    lastStatusChange = timeSource.currentTimestamp();
    return true;
}

bool RemoteAirConditioner::turnOff() {
    if (!canChangeStatus()) {
        return false;
    }

    wirelessExecutor.remoteCommand(0xA2, 0x02);
    lastStatusChange = timeSource.currentTimestamp();
    return true;
}
