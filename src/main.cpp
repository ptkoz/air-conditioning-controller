#include <Arduino.h>
#include "Displays/ILI9341.h"
#include "Controller/UnitController.h"
#include "Controller/RemoteCommandProcessor.h"
#include "Devices/RemoteAirConditioner.h"
#include "Sensors/SHT35.h"

ACC::Time::Source timeSource;
ACC::Displays::AdafruitGFX::ILI9341 mainDisplay(10, 8, 11, 13, 24, 12, 9);

ACC::Controller::RemoteCommand::Processor remoteCommandProcessor(mainDisplay, Serial, 2, timeSource);
ACC::Devices::RemoteAirConditioner airConditioner(remoteCommandProcessor, timeSource);

ACC::Sensors::SHT35 sht35Sensor(0x45, timeSource);
ACC::Controller::UnitController unitController(sht35Sensor, sht35Sensor, airConditioner, mainDisplay, timeSource);

void setup() {
    Serial.begin(9600);
    sht35Sensor.initialize();
    unitController.initialize();
    remoteCommandProcessor.initialize();
    mainDisplay.initialize();
}

void loop() {
    unitController.process();
    remoteCommandProcessor.process();
}

