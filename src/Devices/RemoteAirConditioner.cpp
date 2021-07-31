#include "Devices/RemoteAirConditioner.h"
#include <EEPROM.h>

using namespace ACC::Devices;

void RemoteAirConditioner::initialize() {
    restoreState();
}

AirConditionerStatus RemoteAirConditioner::getStatus() const {
    if (lastPingTimestamp.getMinAgeSeconds() > maxIntervalWithoutPing) {
        return AirConditionerStatus::UNAVAILABLE;
    }

    return isTurnedOn ? AirConditionerStatus::TURNED_ON : AirConditionerStatus::TURNED_OFF;
}

void RemoteAirConditioner::turnOn(bool forceRepeat) {
    if (canTurnOn() && (forceRepeat || getStatus() != AirConditionerStatus::TURNED_ON)) {
        remoteExecutor.execute(0xA2, 0x01);
        lastTurnOnTimestamp = timeSource.currentTimestamp();
        isTurnedOn = true;
        persistState();
    }
}

void RemoteAirConditioner::turnOff(bool forceRepeat) {
    if (canTurnOff() && (forceRepeat || getStatus() != AirConditionerStatus::TURNED_OFF)) {
        remoteExecutor.execute(0xA2, 0x02);
        lastTurnOffTimestamp = timeSource.currentTimestamp();
        isTurnedOn = false;
        persistState();
    }
}

void RemoteAirConditioner::persistState() const {
    EEPROM.put(0x01, isTurnedOn);
}

void RemoteAirConditioner::restoreState() {
    EEPROM.get(0x01, isTurnedOn);
}

void RemoteAirConditioner::acknowledgePing() {
    if (getStatus() == AirConditionerStatus::UNAVAILABLE) {
        // Device came back after a period of being unavailable. Assume it's off.
        isTurnedOn = false;
    }
    lastPingTimestamp = timeSource.currentTimestamp();
}
