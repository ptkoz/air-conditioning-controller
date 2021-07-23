#include <Arduino.h>
#include "Displays/AdafruitGFX/ILI9341.h"
#include "Controller.h"
#include "Devices/AirConditioners/RemoteAirConditioner.h"
#include "Devices/TemperatureSensors/SHT35.h"

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

ACC::Displays::AdafruitGFX::ILI9341 mainDisplay(10, 8, 11, 13, 24, 12, 9);
ACC::Time::Source timeSource;
ACC::Devices::AirConditioners::RemoteAirConditioner airConditioner;
ACC::Devices::TemperatureSensors::SHT35 temperatureSensor(0x45);
ACC::Controller controller(airConditioner, temperatureSensor, mainDisplay, timeSource);

void setup() {
    Wire.begin();
    Wire.setClock(100000);
    Serial.begin(9600);
    mainDisplay.initialize();
    temperatureSensor.initialize();
}

void loop() {
    Serial.println(freeMemory());
    controller.process();
    delay(6000);
}

