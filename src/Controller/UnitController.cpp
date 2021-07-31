#include "Controller/UnitController.h"
#include <EEPROM.h>
#include <Persistence/Addresses.h>

using namespace ACC::Controller;
using ACC::Measures::Temperature;
using ACC::Measures::Humidity;
using ACC::Devices::AirConditionerStatus;

void UnitController::process() {
    if (lastTemperatureUpdate.getMinAgeSeconds() >= temperatureUpdateInterval) {
        if (isAcManagementEnabled()) {
            toggleAirConditioning();
        }
        updateDisplayData();
        lastTemperatureUpdate = timeSource.currentTimestamp();
    }

    if (lastEvaluationTimestamp.getMinAgeSeconds() >= statusEvaluationInterval) {
        if (isAcManagementEnabled()) {
            evaluateAirConditioningStatus();
        }
        lastEvaluationTimestamp = timeSource.currentTimestamp();
    }

    if (display.hasPendingInteraction()) {
        display.isMenuModeEnabled()
        ? display.enterInfoMode()
        : display.enterMenuMode();
    }
}

void UnitController::toggleAirConditioning() {
    TargetTemperature targetTemperature = getTargetTemperature();
    Temperature temperature = temperatureSensor.measureTemperature();
    AirConditionerStatus previousStatus = airConditioner.getStatus();

    if (targetTemperature.isTemperatureAboveRange(temperature)) {
        airConditioner.turnOn();
    }

    if (targetTemperature.isTemperatureBellowRange(temperature)) {
        airConditioner.turnOff();
    }

    if (previousStatus != airConditioner.getStatus()) {
        // we successfully attempted turning AC On or Off, re-evaluate AC status comparing against current measures
        lastEvaluationTimestamp = timeSource.currentTimestamp();
        refTemperature = temperature;
    }
}

void UnitController::evaluateAirConditioningStatus() {
    TargetTemperature targetTemperature = getTargetTemperature();
    Temperature temperature = temperatureSensor.measureTemperature();

    if (targetTemperature.isTemperatureAboveRange(temperature) && !(temperature < refTemperature)) {
        // AC should be on, but the temperature has not fallen significantly in last interval
        airConditioner.turnOn(true);
    }

    if (targetTemperature.isTemperatureBellowRange(temperature) && temperature < refTemperature) {
        // AC should be off, but the temperature is still significantly falling
        airConditioner.turnOff(true);
    }

    refTemperature = temperature;
}

void UnitController::updateDisplayData() {
    TargetTemperature targetTemperature = getTargetTemperature();
    Temperature temperature = temperatureSensor.measureTemperature();
    Humidity humidity = humiditySensor.measureHumidity();
    Devices::AirConditionerStatus airConditionerStatus = airConditioner.getStatus();

    display.setPrimaryTemperature(temperature,targetTemperature.isWarningTemperature(temperature));
    display.setTargetPrimaryTemperature(targetTemperature);
    display.setAirConditionerStatus(airConditionerStatus);
    display.setPrimaryHumidity(humidity);
}

TargetTemperature UnitController::getTargetTemperature() {
    double value;
    EEPROM.get(Persistence::Address::targetTemperature, value);

    return TargetTemperature(value);
}

bool UnitController::isAcManagementEnabled() {
    bool value;
    EEPROM.get(Persistence::Address::acManagementEnabled, value);

    return value;
}


