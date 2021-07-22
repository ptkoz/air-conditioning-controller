#include "Controller.h"
#include <Arduino.h>
#include <EEPROM.h>

using namespace ACC;

Controller::Controller(
        Devices::AirConditioner & airConditioner,
        Devices::TemperatureSensor & temperatureSensor,
        Displays::Display & display,
        const Time::Source & timeSource
) :
        targetTemperature(0),
        isAirConditionerEnabled(false),
        airConditioner(airConditioner),
        temperatureSensor(temperatureSensor),
        display(display),
        timeSource(timeSource) {
    restoreState();
}

void Controller::process() {
    temperatureSensor.measure();

    double indoorTemperature = temperatureSensor.getTemperature();

    evaluateAirConditioningStatusChange(indoorTemperature);

    display.setCoolingIndicator(isAirConditionerEnabled);
    display.setTargetTemperature(targetTemperature);
    display.setIndoorTemperature(indoorTemperature, hasIndoorTemperatureWarning(indoorTemperature));
    display.setCoolingIndicator(isAirConditionerEnabled);
}

void Controller::evaluateAirConditioningStatusChange(double indoorTemperature) {
    if (targetTemperature + acThreshold < indoorTemperature) {
        if (!isAirConditionerEnabled) {
            isAirConditionerEnabled = airConditioner.turnOn();
            if (isAirConditionerEnabled) saveState();
        }
    } else if (indoorTemperature < targetTemperature - acThreshold) {
        if (isAirConditionerEnabled) {
            isAirConditionerEnabled = !airConditioner.turnOff();
            if (!isAirConditionerEnabled) saveState();
        }
    }
}

bool Controller::hasIndoorTemperatureWarning(double indoorTemperature) {
    if (targetTemperature + warningThreshold < indoorTemperature ||
        indoorTemperature < targetTemperature - targetTemperature) {
        return true;
    } else {
        return false;
    }
}

void Controller::saveState() const {
    EEPROM.put(0x01, isAirConditionerEnabled);
    EEPROM.put(0x02, targetTemperature);
}

void Controller::restoreState() {
    EEPROM.get(0x01, isAirConditionerEnabled);
    EEPROM.get(0x02, targetTemperature);
}
