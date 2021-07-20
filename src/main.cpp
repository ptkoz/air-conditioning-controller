#include <Arduino.h>
#include "Devices/AirConditioner.h"
#include "Displays/Display.h"
#include <IRremote.h>
#include <GxEPD2_3C.h>
#include <Displays/AdafruitGFX/GxEPD2/EPaperDisplayDecorator.h>
#include <Displays/AdafruitGFX/Display200x200.h>
#include <Controller.h>
#include "Devices/TemperatureSensors/MCP9808.h"
#include "Devices/AirConditioners/DimplexPC35AMB.h"

GxEPD2_3C<GxEPD2_154_Z90c, 8> driver(GxEPD2_154_Z90c(10,8,9,7));
ACC::Displays::AdafruitGFX::Display200x200 graphicDisplay(driver);
ACC::Displays::AdafruitGFX::GxEPD2::EPaperDisplayDecorator<GxEPD2_154_Z90c, 8> mainDisplay(graphicDisplay, driver);
ACC::Devices::AirConditioners::DimplexPC35AMB airConditioner(IrSender);
ACC::Devices::TemperatureSensors::MCP9808 temperatureSensor(0x18);
ACC::Controller controller(airConditioner, temperatureSensor, mainDisplay, 22.5);

void setup() {
    driver.init();
    driver.setRotation(1);
    IrSender.begin(3, false);
}

void loop() {
    controller.process();
    delay(10000);
}
