#include "Devices/RemoteAirConditioner.h"
#include <EEPROM.h>
#include <Persistence/Addresses.h>

using namespace ACC::Devices;

AirConditionerStatus RemoteAirConditioner::getStatus() const {
    if (lastPingTimestamp.getMinAgeSeconds() > maxIntervalWithoutPing) {
        return AirConditionerStatus::UNAVAILABLE;
    }

    bool isTurnedOn;
    EEPROM.get(Persistence::Address::acStatus, isTurnedOn);

    return isTurnedOn ? AirConditionerStatus::TURNED_ON : AirConditionerStatus::TURNED_OFF;
}

void RemoteAirConditioner::turnOn(bool forceRepeat) {
    if (canTurnOn() && (forceRepeat || getStatus() != AirConditionerStatus::TURNED_ON)) {
        remoteExecutor.execute(0xA2, 0x01);
        lastTurnOnTimestamp = timeSource.currentTimestamp();
        EEPROM.put(Persistence::Address::acStatus, true);
    }
}

void RemoteAirConditioner::turnOff(bool forceRepeat) {
    if (canTurnOff() && (forceRepeat || getStatus() != AirConditionerStatus::TURNED_OFF)) {
        remoteExecutor.execute(0xA2, 0x02);
        lastTurnOffTimestamp = timeSource.currentTimestamp();
        EEPROM.put(Persistence::Address::acStatus, false);
    }
}

void RemoteAirConditioner::acknowledgePing() {
    if (getStatus() == AirConditionerStatus::UNAVAILABLE) {
        // Device came back after a period of being unavailable. Assume it's off.
        EEPROM.put(Persistence::Address::acStatus, false);
    }
    lastPingTimestamp = timeSource.currentTimestamp();
}
