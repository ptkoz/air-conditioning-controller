#include "Controller/UnitController.h"
#include <EEPROM.h>

using namespace ACC::Controller;
using ACC::Measures::Temperature;

void UnitController::initialize() {
    restoreState();
}

void UnitController::process() {
    Temperature primaryTemperature = primaryTemperatureSensor.measureTemperature();

    if (!isAirConditionerEnabled && targetPrimaryTemperature.isAboveAcOnThreshold(primaryTemperature)) {
        isAirConditionerEnabled = airConditioner.turnOn();
        if (!isAirConditionerEnabled) {
            // we successfully turned it on, save state
            saveState();
        }
    }

    if (isAirConditionerEnabled && targetPrimaryTemperature.isBelowAcOffThreshold(primaryTemperature)) {
        isAirConditionerEnabled = !airConditioner.turnOff();
        if (!isAirConditionerEnabled) {
            // we successfully turned it off, save state
            saveState();
        }
    }

    display.setPrimaryTemperature(
        primaryTemperature,
        targetPrimaryTemperature.isWarningTemperature(primaryTemperature)
    );
    display.setTargetPrimaryTemperature(targetPrimaryTemperature);
    display.setCoolingIndicator(isAirConditionerEnabled);
}

void UnitController::saveState() const {
    EEPROM.put(0x01, isAirConditionerEnabled);
    EEPROM.put(0x02, targetPrimaryTemperature.getTemperature());
}

void UnitController::restoreState() {
    double restoredTargetTemperature;
    EEPROM.get(0x01, isAirConditionerEnabled);
    EEPROM.get(0x02, restoredTargetTemperature);

    targetPrimaryTemperature = TargetTemperature(restoredTargetTemperature);
}
