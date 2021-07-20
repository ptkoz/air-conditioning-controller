#include "Devices/AirConditioners/DimplexPC35AMB.h"


using namespace ACC::Devices::AirConditioners;

/**
 * Constructor that sets up the air conditioner controller with an infra-red emitter that
 * acts like a remote control for the actual unit.
 */
DimplexPC35AMB::DimplexPC35AMB(IRsend & irEmitter) :
        AirConditioner(),
        lastStatusChangeTimestamp(0),
        irFrequency(38),
        irEmitter(irEmitter) {
}

DimplexPC35AMB::~DimplexPC35AMB() = default;

bool DimplexPC35AMB::turnOn() {
    if (!canChangeStatus()) {
        return false;
    }

    const uint16_t signal[] PROGMEM = {
            512, 3508, 504, 500, 512, 496, 500, 504, 508, 500, 508, 496, 504, 504, 504, 1500, 508, 1504, 504, 500, 508,
            500, 500, 532, 476, 504, 508, 500, 508, 496, 500, 508, 504, 508, 512, 496, 500, 504, 508, 500, 508, 500,
            508, 496, 504, 504, 504, 500, 508, 536, 504, 500, 508, 500, 500, 508, 500, 504, 508, 500, 508, 496, 504,
            504, 504, 1516, 500, 508, 504, 504, 504, 500, 508, 500, 500, 504, 504, 504, 508, 1496, 500, 528, 500, 508,
            504, 504, 504, 1496, 500, 508, 504, 504, 504, 500, 508, 1496, 504, 592, 508, 492, 504, 1496, 504, 496, 504,
            1492, 504, 3504, 500
    };
    irEmitter.sendRaw(signal, sizeof(signal) / sizeof(signal[0]), irFrequency);
    lastStatusChangeTimestamp = millis();

    return true;
}

bool DimplexPC35AMB::turnOff() {
    if (!canChangeStatus()) {
        return false;
    }

    const uint16_t signal[] PROGMEM = {
            500, 3516, 500, 504, 508, 504, 504, 500, 500, 504, 504, 504, 504, 500, 508, 500, 500, 516, 504, 500, 508,
            500, 500, 504, 504, 504, 508, 496, 512, 496, 500, 508, 504, 508, 500, 508, 500, 504, 508, 500, 508, 496,
            504, 504, 504, 500, 508, 500, 512, 532, 504, 500, 500, 508, 500, 504, 508, 500, 508, 496, 504, 504, 504,
            504, 504, 1516, 504, 504, 508, 496, 508, 500, 500, 504, 504, 504, 508, 500, 508, 1492, 504, 528, 504, 504,
            504, 500, 508, 1496, 504, 500, 508, 500, 508, 500, 500, 1500, 508, 588, 504, 1496, 512, 488, 508, 492, 508,
            492, 508, 3500, 504
    };
    irEmitter.sendRaw(signal, sizeof(signal) / sizeof(signal[0]), irFrequency);
    lastStatusChangeTimestamp = millis();

    return true;
}

void DimplexPC35AMB::setLowSpeed() {
    const uint16_t signal[] PROGMEM = {
            504, 3512, 504, 500, 508, 500, 500, 504, 504, 508, 500, 500, 500, 508, 504, 1500,
            508, 1504, 504, 500, 508, 416, 596, 492, 504, 504, 508, 496, 500, 508, 504, 504,
            504, 508, 500, 504, 508, 500, 508, 500, 500, 504, 504, 504, 504, 500, 500, 508,
            504, 540, 500, 508, 500, 504, 504, 500, 512, 496, 500, 508, 504, 500, 508, 1496,
            504, 520, 512, 496, 500, 504, 504, 504, 504, 500, 512, 496, 500, 508, 504, 1496,
            500, 532, 508, 500, 500, 508, 500, 1500, 500, 508, 500, 504, 508, 1496, 500, 1504,
            504, 1588, 504, 1496, 500, 1496, 504, 1496, 500, 1496, 504, 3504, 504
    };
    irEmitter.sendRaw(signal, sizeof(signal) / sizeof(signal[0]), irFrequency);
}

void DimplexPC35AMB::setHighSpeed() {
    const uint16_t signal[] PROGMEM = {
            504, 3512, 504, 504, 508, 496, 504, 504, 504, 500, 508, 500, 500, 508, 500, 1500, 512, 1500, 508, 500, 508,
            496, 504, 504, 504, 500, 508, 500, 500, 504, 504, 504, 508, 504, 504, 504, 504, 504, 508, 496, 504, 504,
            504, 500, 508, 500, 500, 504, 508, 536, 500, 508, 504, 500, 508, 500, 500, 504, 504, 504, 508, 500, 508,
            1492, 504, 520, 500, 508, 504, 500, 508, 500, 500, 504, 504, 504, 504, 500, 512, 496, 500, 532, 500, 1500,
            508, 500, 508, 500, 500, 504, 504, 504, 508, 1496, 500, 1500, 508, 1588, 504, 1492, 504, 496, 504, 1496,
            504, 1492, 504, 3508, 500
    };
    irEmitter.sendRaw(signal, sizeof(signal) / sizeof(signal[0]), irFrequency);
}

unsigned long DimplexPC35AMB::getMillisSinceEvent(unsigned long eventTimestamp) {
    unsigned long currentTimestamp = millis();

    if (currentTimestamp >= eventTimestamp) {
        return currentTimestamp - eventTimestamp;
    } else {
        return UINT32_MAX - eventTimestamp + currentTimestamp;
    }
}

bool DimplexPC35AMB::canChangeStatus() const {
    // Only allow turning on / off 5 minutes since last turn on / off
    return DimplexPC35AMB::getMillisSinceEvent(lastStatusChangeTimestamp) > 1000*60*5;
}
