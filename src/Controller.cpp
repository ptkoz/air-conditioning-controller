#include "Controller.h"

using namespace ACC;

Controller::Controller(
        Devices::AirConditioner & airConditioner,
        Devices::TemperatureSensor & temperatureSensor,
        Displays::Display & display,
        double targetTemperature
) :
        targetTemperature(targetTemperature),
        isAirConditionerEnabled(false),
        airConditioner(airConditioner),
        temperatureSensor(temperatureSensor),
        display(display) {

}

void Controller::process() {
    temperatureSensor.measure();

    double indoorTemperature = temperatureSensor.getTemperature();

    if (targetTemperature + temperatureTolerance <= indoorTemperature) {
        display.setIndoorTemperatureWarning(targetTemperature + temperatureTolerance < indoorTemperature);
        if (!isAirConditionerEnabled) {
            isAirConditionerEnabled = airConditioner.turnOn();
        }
    } else if (indoorTemperature <= targetTemperature - temperatureTolerance) {
        display.setIndoorTemperatureWarning(indoorTemperature < targetTemperature - temperatureTolerance);
        if (isAirConditionerEnabled) {
            isAirConditionerEnabled = !airConditioner.turnOff();
        }
    } else {
        display.setIndoorTemperatureWarning(false);
    }

    display.setCoolingIndicator(isAirConditionerEnabled);
    display.setTargetTemperature(targetTemperature);
    display.setIndoorTemperature(indoorTemperature);
    display.setCoolingIndicator(isAirConditionerEnabled);
    display.draw();
}