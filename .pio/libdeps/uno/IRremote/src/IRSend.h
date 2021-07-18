#ifndef AIR_CONDITIONING_CONTROLLER_IRSEND_H
#define AIR_CONDITIONING_CONTROLLER_IRSEND_H

#include "Arduino.h"
#include "IRData.h"

/**
 * Main class for sending IR signals
 */
class IRsend {
    public:
        IRsend(uint8_t aSendPin);
        void setSendPin(uint8_t aSendPinNumber);
        void begin(uint8_t aSendPin, bool aEnableLEDFeedback = true, uint8_t aFeedbackLEDPin = 0);

        IRsend();
        void begin(bool aEnableLEDFeedback, uint8_t aFeedbackLEDPin = 0)
        __attribute__ ((deprecated ("Please use begin(<sendPin>, <EnableLEDFeedback>, <LEDFeedbackPin>)")));

        size_t write(IRData *aIRSendData, uint_fast8_t aNumberOfRepeats = 0);

        void enableIROut(uint8_t aFrequencyKHz);

        void sendPulseDistanceWidthData(unsigned int aOneMarkMicros, unsigned int aOneSpaceMicros, unsigned int aZeroMarkMicros,
                                        unsigned int aZeroSpaceMicros, uint32_t aData, uint8_t aNumberOfBits, bool aMSBfirst, bool aSendStopBit = false);
        void sendBiphaseData(unsigned int aBiphaseTimeUnit, uint32_t aData, uint_fast8_t aNumberOfBits);

        void mark(unsigned int aMarkMicros);
        void space(unsigned int aSpaceMicros);
        void IRLedOff();

// 8 Bit array
        void sendRaw(const uint8_t aBufferWithTicks[], uint_fast8_t aLengthOfBuffer, uint_fast8_t aIRFrequencyKilohertz);
        void sendRaw_P(const uint8_t aBufferWithTicks[], uint_fast8_t aLengthOfBuffer, uint_fast8_t aIRFrequencyKilohertz);

// 16 Bit array
        void sendRaw(const uint16_t aBufferWithMicroseconds[], uint_fast8_t aLengthOfBuffer, uint_fast8_t aIRFrequencyKilohertz);
        void sendRaw_P(const uint16_t aBufferWithMicroseconds[], uint_fast8_t aLengthOfBuffer, uint_fast8_t aIRFrequencyKilohertz);

        /*
         * New send functions
         */
        void sendBoseWave(uint8_t aCommand, uint_fast8_t aNumberOfRepeats = 0);
        void sendDenon(uint8_t aAddress, uint8_t aCommand, uint_fast8_t aNumberOfRepeats, bool aSendSharp = false);
        void sendDenonRaw(uint16_t aRawData, uint_fast8_t aNumberOfRepeats = 0)
        __attribute__ ((deprecated ("Please use sendDenon(aAddress, aCommand, aNumberOfRepeats).")));
        void sendJVC(uint8_t aAddress, uint8_t aCommand, uint_fast8_t aNumberOfRepeats);

        void sendLGRepeat(bool aUseLG2Protocol = false);
        void sendLG(uint8_t aAddress, uint16_t aCommand, uint_fast8_t aNumberOfRepeats, bool aIsRepeat = false, bool aUseLG2Protocol =
        false);
        void sendLGRaw(uint32_t aRawData, uint_fast8_t aNumberOfRepeats = 0, bool aIsRepeat = false, bool aUseLG2Protocol = false);

        void sendNECRepeat();
        void sendNEC(uint16_t aAddress, uint8_t aCommand, uint_fast8_t aNumberOfRepeats, bool aIsRepeat = false);
        void sendNECRaw(uint32_t aRawData, uint_fast8_t aNumberOfRepeats = 0, bool aIsRepeat = false);
        // NEC variants
        void sendOnkyo(uint16_t aAddress, uint16_t aCommand, uint_fast8_t aNumberOfRepeats, bool aIsRepeat = false);
        void sendApple(uint8_t aAddress, uint8_t aCommand, uint_fast8_t aNumberOfRepeats, bool aIsRepeat = false);

        void sendPanasonic(uint16_t aAddress, uint8_t aData, uint_fast8_t aNumberOfRepeats); // LSB first
        void sendKaseikyo(uint16_t aAddress, uint8_t aData, uint_fast8_t aNumberOfRepeats, uint16_t aVendorCode); // LSB first

        void sendRC5(uint8_t aAddress, uint8_t aCommand, uint_fast8_t aNumberOfRepeats, bool aEnableAutomaticToggle = true);
        void sendRC6(uint8_t aAddress, uint8_t aCommand, uint_fast8_t aNumberOfRepeats, bool aEnableAutomaticToggle = true);
        void sendSamsungRepeat();
        void sendSamsung(uint16_t aAddress, uint16_t aCommand, uint_fast8_t aNumberOfRepeats, bool aIsRepeat = false);
        void sendSharp(uint8_t aAddress, uint8_t aCommand, uint_fast8_t aNumberOfRepeats); // redirected to sendDenon
        void sendSony(uint16_t aAddress, uint8_t aCommand, uint_fast8_t aNumberOfRepeats, uint8_t numberOfBits = 12);

        void sendLegoPowerFunctions(uint8_t aChannel, uint8_t tCommand, uint8_t aMode, bool aDoSend5Times = true);
        void sendLegoPowerFunctions(uint16_t aRawData, bool aDoSend5Times = true);
        void sendLegoPowerFunctions(uint16_t aRawData, uint8_t aChannel, bool aDoSend5Times = true);

        void sendMagiQuest(uint32_t wand_id, uint16_t magnitude);

        void sendPronto(const __FlashStringHelper *str, uint_fast8_t aNumberOfRepeats = 0);
        void sendPronto(const char *prontoHexString, uint_fast8_t aNumberOfRepeats = 0);
        void sendPronto(const uint16_t *data, unsigned int length, uint_fast8_t aNumberOfRepeats = 0);
#if defined(__AVR__)
        void sendPronto_PF(uint_farptr_t str, uint_fast8_t aNumberOfRepeats = 0);
        void sendPronto_P(const char *str, uint_fast8_t aNumberOfRepeats);
#endif

// Template protocol :-)
        void sendShuzu(uint16_t aAddress, uint8_t aCommand, uint_fast8_t aNumberOfRepeats);

        /*
         * OLD send functions
         */
        void sendDenon(unsigned long data, int nbits);
        void sendDISH(unsigned long data, int nbits);
        void sendJVC(unsigned long data, int nbits,
                     bool repeat)
        __attribute__ ((deprecated ("This old function sends MSB first! Please use sendJVC(aAddress, aCommand, aNumberOfRepeats)."))) {
            sendJVCMSB(data, nbits, repeat);
        }
        void sendJVCMSB(unsigned long data, int nbits, bool repeat = false);

        void sendLG(unsigned long data, int nbits);

        void sendNEC(uint32_t aRawData,
                     uint8_t nbits)
        __attribute__ ((deprecated ("This old function sends MSB first! Please use sendNEC(aAddress, aCommand, aNumberOfRepeats)."))) {
            sendNECMSB(aRawData, nbits);
        }
        void sendNECMSB(uint32_t data, uint8_t nbits, bool repeat = false);
        void sendPanasonic(uint16_t aAddress,
                           uint32_t aData)
        __attribute__ ((deprecated ("This old function sends MSB first! Please use sendPanasonic(aAddress, aCommand, aNumberOfRepeats).")));
        void sendRC5(uint32_t data, uint8_t nbits);
        void sendRC5ext(uint8_t addr, uint8_t cmd, bool toggle);
        void sendRC6(uint32_t data, uint8_t nbits);
        void sendRC6(uint64_t data, uint8_t nbits);
        void sendSharpRaw(unsigned long data, int nbits);
        void sendSharp(unsigned int address, unsigned int command);
        void sendSAMSUNG(unsigned long data, int nbits);
        __attribute__ ((deprecated ("This old function sends MSB first! Please use sendSamsung().")));
        void sendSony(unsigned long data,
                      int nbits)
        __attribute__ ((deprecated ("This old function sends MSB first! Please use sendSony(aAddress, aCommand, aNumberOfRepeats).")));
        ;
        void sendWhynter(unsigned long data, int nbits);

        uint8_t sendPin;

        unsigned int periodTimeMicros;
        unsigned int periodOnTimeMicros; // compensated with PULSE_CORRECTION_NANOS for duration of digitalWrite.
        unsigned int getPulseCorrectionNanos();

        void customDelayMicroseconds(unsigned long aMicroseconds);
};

#endif //AIR_CONDITIONING_CONTROLLER_IRSEND_H
