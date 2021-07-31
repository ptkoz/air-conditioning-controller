#include <Arduino.h>
#include "Displays/ILI9341.h"
#include "Controller/UnitController.h"
#include "Controller/RemoteCommandRadio.h"
#include "Controller/RemoteCommandProcessor.h"
#include "Controller/RemoteCommandExecutor.h"
#include "Devices/RemoteAirConditioner.h"
#include "Sensors/SHT35.h"

ACC::Time::Source timeSource;
ACC::Displays::AdafruitGFX::ILI9341 mainDisplay(timeSource, 10, 8, 11, 13, 24, 12, 9, 6, A3, A2, 7, 200);

ACC::Controller::RemoteCommand::Radio radio(Serial, 2);
ACC::Controller::RemoteCommand::Executor remoteCommandExecutor(radio);

ACC::Devices::RemoteAirConditioner airConditioner(remoteCommandExecutor, timeSource);

ACC::Controller::RemoteCommand::Processor remoteCommandProcessor(mainDisplay, airConditioner, radio, timeSource);

ACC::Sensors::SHT35 sht35Sensor(0x45, timeSource);
ACC::Controller::UnitController unitController(sht35Sensor, sht35Sensor, airConditioner, mainDisplay, timeSource);

void setup() {
    Serial.begin(9600);
    radio.initialize();
    sht35Sensor.initialize();
    mainDisplay.initialize();
}

void loop() {
    unitController.process();
    remoteCommandProcessor.process();
}

