#include <Arduino.h>
#include "Devices/AirConditioner.h"
#include "Displays/Display.h"
#include <GxEPD2_3C.h>
#include <Displays/AdafruitGFX/GxEPD2/EPaperDisplayDecorator.h>
#include <Displays/AdafruitGFX/Display200x200.h>
#include "Devices/TemperatureSensors/MCP9808.h"
#include "Devices/AirConditioners/DimplexPC35AMB.h"

GxEPD2_3C<GxEPD2_154_Z90c, 8> driver(GxEPD2_154_Z90c(10,8,9,7));
ACC::Displays::AdafruitGFX::Display200x200 graphicDisplay(driver);
ACC::Displays::AdafruitGFX::GxEPD2::EPaperDisplayDecorator<GxEPD2_154_Z90c, 8> mainDisplay(graphicDisplay, driver);
ACC::Devices::TemperatureSensors::MCP9808 temperatureSensor(0x18);

void setup() {
    driver.init();
    driver.setRotation(1);
}

void loop() {
    temperatureSensor.measure();
    mainDisplay.setIndoorTemperature(temperatureSensor.getTemperature());
    mainDisplay.draw();
    delay(10000);
}
