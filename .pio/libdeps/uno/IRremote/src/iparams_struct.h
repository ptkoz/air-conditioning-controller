#ifndef AIR_CONDITIONING_CONTROLLER_IPARAMS_STRUCT_H
#define AIR_CONDITIONING_CONTROLLER_IPARAMS_STRUCT_H

#include "raw_buffer.h"

/**
 * This struct contains the data and control used for receiver static functions and the ISR (interrupt service routine)
 * Only StateForISR needs to be volatile. All the other fields are not written by ISR after data available and before start/resume.
 */
struct irparams_struct {
    // The fields are ordered to reduce memory over caused by struct-padding
    volatile uint8_t StateForISR;   ///< State Machine state
    uint8_t IRReceivePin;           ///< Pin connected to IR data from detector
#if defined(__AVR__)
    volatile uint8_t *IRReceivePinPortInputRegister;
    uint8_t IRReceivePinMask;
#endif
    uint16_t TickCounterForISR;     ///< Counts 50uS ticks. The value is copied into the rawbuf array on every transition.

    bool OverflowFlag;              ///< Raw buffer OverflowFlag occurred
    uint8_t rawlen;                 ///< counter of entries in rawbuf
    uint16_t rawbuf[RAW_BUFFER_LENGTH]; ///< raw data / tick counts per mark/space, first entry is the length of the gap between previous and current command
};

#endif //AIR_CONDITIONING_CONTROLLER_IPARAMS_STRUCT_H
