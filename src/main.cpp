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

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

int freeMemory() {
    char top;
#ifdef __arm__
    return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
    return &top - __brkval;
#else  // __arm__
    return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}

int initialFreeMomory = freeMemory();

GxEPD2_3C<GxEPD2_154_Z90c, 8> driver(GxEPD2_154_Z90c(10,8,9,7));
ACC::Displays::AdafruitGFX::Display200x200 graphicDisplay(driver);
ACC::Displays::AdafruitGFX::GxEPD2::EPaperDisplayDecorator<GxEPD2_154_Z90c, 8> mainDisplay(graphicDisplay, driver);
ACC::Time::Source timeSource;
ACC::Devices::AirConditioners::DimplexPC35AMB airConditioner(IrSender, timeSource);
ACC::Devices::TemperatureSensors::MCP9808 temperatureSensor(0x18);
ACC::Controller controller(airConditioner, temperatureSensor, mainDisplay, 23.0);



void setup() {
    driver.init();
    driver.setRotation(1);
    IrSender.begin(3, false);
    Serial.begin(9600);
    Serial.println(initialFreeMomory);
}

void loop() {
    Serial.println(freeMemory());
    controller.process();
    delay(6000);
}

