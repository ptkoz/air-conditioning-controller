#include <Arduino.h>
#include <EEPROM.h>
#include "Displays/ILI9341.h"
#include "Controller/UnitController.h"
#include "Controller/WirelessController.h"
#include "Devices/RemoteAirConditioner.h"
#include "Sensors/SHT35.h"

ACC::Time::Source timeSource;
ACC::Displays::AdafruitGFX::ILI9341 mainDisplay(10, 8, 11, 13, 24, 12, 9);

ACC::Controller::WirelessController wirelessController(Serial, 2);
ACC::Devices::RemoteAirConditioner airConditioner(wirelessController, timeSource);

ACC::Sensors::SHT35 temperatureSensor(0x45);
ACC::Controller::UnitController unitController(temperatureSensor, airConditioner, mainDisplay);

void setup() {
    Serial.begin(9600);
    temperatureSensor.initialize();
    unitController.initialize();
    wirelessController.initialize();
    mainDisplay.initialize();
}

void loop() {
    unitController.process();
    delay(5000);
}

