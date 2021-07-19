#include <Arduino.h>
#include "Devices/AirConditioner.h"
#include "Displays/Display.h"

#include "Devices/AirConditioners/DimplexPC35AMB.h"
#include "Displays/Factory.h"

ACC::Displays::Display & mainDisplay = ACC::Displays::Factory::createWaveShare3Color200x200Display(10, 8, 9, 7);

void setup() {
    Serial.begin(9600); //change BAUD rate as required
    Serial.println(F("Setting up"));
}

void loop() {
    Serial.println(F("Looping..."));
//    mainDisplay.draw();
    delay(1000);
}
