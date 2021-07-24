#include "Controller/UnitController.h"
#include <EEPROM.h>

using namespace ACC::Controller;
using ACC::Measures::Temperature;
using ACC::Measures::Humidity;

void UnitController::initialize() {
    restoreState();
}

void UnitController::process() {
    if (lastTemperatureUpdate.getMinAgeSeconds() >= temperatureUpdateInterval) {
        Temperature temperature = temperatureSensor.measureTemperature();
        Humidity humidity = humiditySensor.measureHumidity();


        if (isAcManagementEnabled) {
            toggleAirConditioning(temperature);
        }

        updateDisplayData(temperature, humidity);
        lastTemperatureUpdate = timeSource.currentTimestamp();
    }

    if (lastEvaluationTimestamp.getMinAgeSeconds() >= statusEvaluationInterval && isAcManagementEnabled) {
        Temperature temperature = temperatureSensor.measureTemperature();
        evaluateAirConditioningStatus(temperature);

        lastEvaluationTimestamp = timeSource.currentTimestamp();
        refTemperature = temperature;
    }
}

void UnitController::toggleAirConditioning(const Temperature & temperature) {
    bool wasAirConditioningEnabled = isAcEnabled;

    if (!isAcEnabled && targetTemperature.isTemperatureAboveRange(temperature)) {
        isAcEnabled = airConditioner.turnOn();
    }

    if (isAcEnabled && targetTemperature.isTemperatureBellowRange(temperature)) {
        isAcEnabled = !airConditioner.turnOff();
    }

    if (wasAirConditioningEnabled != isAcEnabled) {
        // we successfully attempted turning AC On or Off, save state and reference temperature for further evaluation
        persistState();
        lastEvaluationTimestamp = timeSource.currentTimestamp();
        refTemperature = temperature;
    }
}

void UnitController::updateDisplayData(const Temperature & temperature, const Humidity & humidity) {
    display.setPrimaryTemperature(
        temperature,
        targetTemperature.isWarningTemperature(temperature)
    );
    display.setTargetPrimaryTemperature(targetTemperature);
    display.setCoolingIndicator(isAcEnabled);
    display.setPrimaryHumidity(humidity);
}

void UnitController::evaluateAirConditioningStatus(const Temperature & temperature) {
    if (isAcEnabled && targetTemperature.isTemperatureAboveRange(temperature) && !(temperature < refTemperature)) {
        // AC should be on, but the temperature has not fallen significantly in last interval
        airConditioner.turnOn();
    }

    if (!isAcEnabled && targetTemperature.isTemperatureBellowRange(temperature) && temperature < refTemperature) {
        // AC should be off, but the temperature is still falling
        airConditioner.turnOff();
    }
}

void UnitController::persistState() const {
    EEPROM.put(0x01, isAcEnabled);
    EEPROM.put(0x02, targetTemperature.getTemperature());
}

void UnitController::restoreState() {
    double restoredTargetTemperature;
    EEPROM.get(0x01, isAcEnabled);
    EEPROM.get(0x02, restoredTargetTemperature);

    targetTemperature = TargetTemperature(restoredTargetTemperature);
}
