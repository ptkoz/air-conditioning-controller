/*
 * IRSend.cpp.h
 *
 *  Contains common functions for sending
 *
 *  This file is part of Arduino-IRremote https://github.com/Arduino-IRremote/Arduino-IRremote.
 *
 ************************************************************************************
 * MIT License
 *
 * Copyright (c) 2009-2021 Ken Shirriff, Rafi Khan, Armin Joachimsmeyer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 ************************************************************************************
 */

#include "IRremoteInt.h"
//#include "digitalWriteFast.h"

__attribute((error("Version > 3.0.1"))) void UsageError(const char *details);

/** \addtogroup Sending Sending IR data for multiple protocols
 * @{
 */

// The sender instance
IRsend IrSender;

IRsend::IRsend() {
#if defined(IR_SEND_PIN)
    sendPin = IR_SEND_PIN; // take IR_SEND_PIN as default
#endif
    setLEDFeedback(0, false);
}

IRsend::IRsend(uint8_t aSendPin) {
    sendPin = aSendPin;
}
void IRsend::setSendPin(uint8_t aSendPin) {
    sendPin = aSendPin;
}

/**
 * Initializes the send and feedback pin
 * @param aSendPin The Arduino pin number, where a IR sender diode is connected.
 * @param aLEDFeedbackPin if 0, then take board specific FEEDBACK_LED_ON() and FEEDBACK_LED_OFF() functions
 */
void IRsend::begin(uint8_t aSendPin, bool aEnableLEDFeedback, uint8_t aLEDFeedbackPin) {
    sendPin = aSendPin;
    setLEDFeedback(aLEDFeedbackPin, aEnableLEDFeedback);
}

/**
 * Deprecated function without send pin parameter
 * @param aLEDFeedbackPin if 0, then take board specific FEEDBACK_LED_ON() and FEEDBACK_LED_OFF() functions
 */
void IRsend::begin(bool aEnableLEDFeedback, uint8_t aLEDFeedbackPin) {

}

/**
 * Deprecated function without send pin parameter
 * @param aIRSendData The values of protocol, address, command and repeat flag are taken for sending.
 * @param aNumberOfRepeats Number of repeats to send after the initial data.
 */
size_t IRsend::write(IRData *aIRSendData, uint_fast8_t aNumberOfRepeats) {
    return 1;
}

/**
 * Function using an 16 byte timing array for every purpose.
 * Raw data starts with a Mark. No leading space as in received timing data!
 */
void IRsend::sendRaw(const uint16_t aBufferWithMicroseconds[], uint_fast8_t aLengthOfBuffer, uint_fast8_t aIRFrequencyKilohertz) {
// Set IR carrier frequency
    enableIROut(aIRFrequencyKilohertz);

    /*
     * Raw data starts with a mark.
     */
    for (uint_fast8_t i = 0; i < aLengthOfBuffer; i++) {
        if (i & 1) {
            // Odd
            space(aBufferWithMicroseconds[i]);
        } else {
            mark(aBufferWithMicroseconds[i]);
        }
    }

    IRLedOff();  // Always end with the LED off
}

/**
 * Function using an 8 byte timing array to save program space
 * Raw data starts with a Mark. No leading space as in received timing data!
 */
void IRsend::sendRaw(const uint8_t aBufferWithTicks[], uint_fast8_t aLengthOfBuffer, uint_fast8_t aIRFrequencyKilohertz) {

}

/**
 * Function using an 16 byte timing array in FLASH for every purpose.
 * Raw data starts with a Mark. No leading space as in received timing data!
 */
void IRsend::sendRaw_P(const uint16_t aBufferWithMicroseconds[], uint_fast8_t aLengthOfBuffer, uint_fast8_t aIRFrequencyKilohertz) {

}

/**
 * Function using an 8 byte timing array in FLASH to save program space
 * Raw data starts with a Mark. No leading space as in received timing data!
 */
void IRsend::sendRaw_P(const uint8_t aBufferWithTicks[], uint_fast8_t aLengthOfBuffer, uint_fast8_t aIRFrequencyKilohertz) {

}

/**
 * Sends PulseDistance data
 * The output always ends with a space
 */
void IRsend::sendPulseDistanceWidthData(unsigned int aOneMarkMicros, unsigned int aOneSpaceMicros, unsigned int aZeroMarkMicros,
        unsigned int aZeroSpaceMicros, uint32_t aData, uint8_t aNumberOfBits, bool aMSBfirst, bool aSendStopBit) {

    if (aMSBfirst) {  // Send the MSB first.
        // send data from MSB to LSB until mask bit is shifted out
        for (uint32_t tMask = 1UL << (aNumberOfBits - 1); tMask; tMask >>= 1) {
            if (aData & tMask) {
                TRACE_PRINT('1');
                mark(aOneMarkMicros);
                space(aOneSpaceMicros);
            } else {
                TRACE_PRINT('0');
                mark(aZeroMarkMicros);
                space(aZeroSpaceMicros);
            }
        }
    } else {  // Send the Least Significant Bit (LSB) first / MSB last.
        for (uint_fast8_t bit = 0; bit < aNumberOfBits; bit++, aData >>= 1)
            if (aData & 1) {  // Send a 1
                TRACE_PRINT('1');
                mark(aOneMarkMicros);
                space(aOneSpaceMicros);
            } else {  // Send a 0
                TRACE_PRINT('0');
                mark(aZeroMarkMicros);
                space(aZeroSpaceMicros);
            }
    }
    if (aSendStopBit) {
        TRACE_PRINT('S');
        mark(aZeroMarkMicros); // seems like this is used for stop bits
    }
    TRACE_PRINTLN("");
}

/*
 * Sends Biphase data MSB first
 * Always send start bit, do not send the trailing space of the start bit
 * 0 -> mark+space
 * 1 -> space+mark
 * The output always ends with a space
 */
void IRsend::sendBiphaseData(unsigned int aBiphaseTimeUnit, uint32_t aData, uint_fast8_t aNumberOfBits) {

// do not send the trailing space of the start bit
    mark(aBiphaseTimeUnit);

    TRACE_PRINT('S');
    uint8_t tLastBitValue = 1; // Start bit is a 1

// Data - Biphase code MSB first
    for (uint32_t tMask = 1UL << (aNumberOfBits - 1); tMask; tMask >>= 1) {
        if (aData & tMask) {
            TRACE_PRINT('1');
            space(aBiphaseTimeUnit);
            mark(aBiphaseTimeUnit);
            tLastBitValue = 1;

        } else {
            TRACE_PRINT('0');
#if defined(SEND_PWM_BY_TIMER) || defined(USE_NO_SEND_PWM)
            if (tLastBitValue) {
                // Extend the current mark in order to generate a continuous signal without short breaks
                delayMicroseconds(aBiphaseTimeUnit);
            } else {
                mark(aBiphaseTimeUnit);
            }
#else
            (void) tLastBitValue; // to avoid compiler warnings
            mark(aBiphaseTimeUnit); // can not eventually delay here, we must call mark to generate the signal
#endif
            space(aBiphaseTimeUnit);
            tLastBitValue = 0;
        }
    }
    TRACE_PRINTLN("");
}

/**
 * Sends an IR mark for the specified number of microseconds.
 * The mark output is modulated at the PWM frequency if USE_NO_SEND_PWM is not defined.
 * The output is guaranteed to be OFF / inactive after after the call of the function.
 * This function may affect the state of feedback LED.
 */
void IRsend::mark(unsigned int aMarkMicros) {
    setFeedbackLED(true);

#if defined(SEND_PWM_BY_TIMER) || defined(ESP32)
    ENABLE_SEND_PWM_BY_TIMER; // Enable timer or ledcWrite() generated PWM output
    customDelayMicroseconds(aMarkMicros);
    IRLedOff();

#elif defined(USE_NO_SEND_PWM)
    digitalWrite(sendPin, LOW); // Set output to active low.
    customDelayMicroseconds(aMarkMicros);
    IRLedOff();

#else
    unsigned long start = micros();
    unsigned long nextPeriodEnding = start;
    unsigned long tMicros;
    do {
//        digitalToggleFast(IR_TIMING_TEST_PIN);
        // Output the PWM pulse
        noInterrupts(); // do not let interrupts extend the short on period
        digitalWrite(sendPin, HIGH); // 4.3 us from do{ to pin setting
        delayMicroseconds(periodOnTimeMicros); // this is normally implemented by a blocking wait

        // Output the PWM pause
        digitalWrite(sendPin, LOW);
        interrupts(); // Enable interrupts -to keep micros correct- for the longer off period 3.4 us until receive ISR is active (for 7 us + pop's)
        nextPeriodEnding += periodTimeMicros;
        do {
            tMicros = micros(); // we have only 4 us resolution for and AVR @16MHz
//            digitalToggleFast(IR_TIMING_TEST_PIN); // 3.0 us per call @16MHz
        } while (tMicros < nextPeriodEnding);  // 3.4 us @16MHz
    } while (tMicros - start < aMarkMicros);
    setFeedbackLED(false);
#  endif
}

/**
 * Just switch the IR sending LED off to send an IR space
 * A space is "no output", so the PWM output is disabled.
 * This function may affect the state of feedback LED.
 */
void IRsend::IRLedOff() {
#if defined(SEND_PWM_BY_TIMER) || defined(ESP32)
    DISABLE_SEND_PWM_BY_TIMER; // Disable PWM output
#elif defined(USE_NO_SEND_PWM)
    digitalWrite(sendPin, HIGH); // Set output to inactive high.
#else
    digitalWrite(sendPin, LOW);
#endif

    setFeedbackLED(false);
}

/**
 * Sends an IR space for the specified number of microseconds.
 * A space is "no output", so just wait.
 */
void IRsend::space(unsigned int aSpaceMicros) {
    customDelayMicroseconds(aSpaceMicros);
}

/**
 * Custom delay function that circumvents Arduino's delayMicroseconds 16 bit limit
 * and is (mostly) not extended by the duration of interrupt codes like the millis() interrupt
 */
void IRsend::customDelayMicroseconds(unsigned long aMicroseconds) {
    unsigned long start = micros();
    // overflow invariant comparison :-)
    while (micros() - start < aMicroseconds) {
    }
}

/**
 * Enables IR output.  The kHz value controls the modulation frequency in kilohertz.
 * The IR output will be on pin 3 (OC2B).
 * This routine is designed for 36-40 kHz; if you use it for other values, it's up to you
 * to make sure it gives reasonable results.  (Watch out for overflow / underflow / rounding.)
 * TIMER2 is used in phase-correct PWM mode, with OCR2A controlling the frequency and OCR2B
 * controlling the duty cycle.
 * There is no prescaling, so the output frequency is 16 MHz / (2 * OCR2A)
 * To turn the output on and off, we leave the PWM running, but connect and disconnect the output pin.
 * A few hours staring at the ATmega documentation and this will all make sense.
 * See my Secrets of Arduino PWM at http://arcfn.com/2009/07/secrets-of-arduino-pwm.html for details.
 */
void IRsend::enableIROut(uint8_t aFrequencyKHz) {
#if defined(SEND_PWM_BY_TIMER) || defined(ESP32)
#  if defined(SEND_PWM_BY_TIMER)
    TIMER_DISABLE_RECEIVE_INTR;
#  endif
    timerConfigForSend(aFrequencyKHz);

#elif defined(USE_NO_SEND_PWM)
    (void) aFrequencyKHz;

#else
    periodTimeMicros = (1000U + aFrequencyKHz / 2) / aFrequencyKHz; // rounded value -> 26 for 38 kHz
    periodOnTimeMicros = (((periodTimeMicros * IR_SEND_DUTY_CYCLE) + 50 - (PULSE_CORRECTION_NANOS / 10)) / 100U); // +50 for rounding
#endif

    pinMode(sendPin, OUTPUT);
    IRLedOff(); // When not sending, we want it low/inactive
}

unsigned int IRsend::getPulseCorrectionNanos() {
    return PULSE_CORRECTION_NANOS;
}

/** @}*/
