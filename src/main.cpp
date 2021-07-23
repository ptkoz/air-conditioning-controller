#include <Arduino.h>
#include "Displays/ILI9341.h"
#include "Controller/UnitController.h"
#include "Controller/WirelessController.h"
#include "Devices/RemoteAirConditioner.h"
#include "Sensors/SHT35.h"

ACC::Time::Source timeSource;
ACC::Displays::AdafruitGFX::ILI9341 mainDisplay(4, 12, 5, 7, 24, 6, 11);

ACC::Controller::WirelessController wirelessController(10);
ACC::Devices::RemoteAirConditioner airConditioner(wirelessController, timeSource);

ACC::Sensors::SHT35 temperatureSensor(0x45);
ACC::Controller::UnitController unitController(temperatureSensor, airConditioner, mainDisplay);

void setup() {
    temperatureSensor.initialize();
    wirelessController.initialize();
    mainDisplay.initialize();
}

void loop() {
    unitController.process();
    delay(6000);
}

