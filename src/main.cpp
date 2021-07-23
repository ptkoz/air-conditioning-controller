#include <Arduino.h>
#include "Displays/ILI9341.h"
#include "Controller/UnitController.h"
#include "Devices/RemoteAirConditioner.h"
#include "Sensors/SHT35.h"

ACC::Time::Source timeSource;
ACC::Devices::RemoteAirConditioner airConditioner;
ACC::Sensors::SHT35 temperatureSensor(0x45);
ACC::Displays::AdafruitGFX::ILI9341 mainDisplay(10, 8, 11, 13, 24, 12, 9);
ACC::Controller::UnitController controller(temperatureSensor, airConditioner, mainDisplay);

void setup() {
    mainDisplay.initialize();
    temperatureSensor.initialize();
}

void loop() {
    controller.process();
    delay(6000);
}

