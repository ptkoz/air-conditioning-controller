#ifndef AIR_CONDITIONING_CONTROLLER_IRDATA_H
#define AIR_CONDITIONING_CONTROLLER_IRDATA_H

#include "IRProtocol.h"
#include "iparams_struct.h"

/**
 * Data structure for the user application, available as decodedIRData.
 * Filled by decoders and read by print functions or user application.
 */
struct IRData {
    decode_type_t protocol;     ///< UNKNOWN, NEC, SONY, RC5, ...
    uint16_t address;           ///< Decoded address
    uint16_t command;           ///< Decoded command
    uint16_t extra;             ///< Used by MagiQuest and for Kaseikyo unknown vendor ID.  Ticks used for decoding Distance protocol.
    uint8_t numberOfBits; ///< Number of bits received for data (address + command + parity) - to determine protocol length if different length are possible.
    uint8_t flags;              ///< See IRDATA_FLAGS_* definitions above
    uint32_t decodedRawData;    ///< Up to 32 bit decoded raw data, used for sendRaw functions.
    irparams_struct *rawDataPtr; ///< Pointer of the raw timing data to be decoded. Mainly the data buffer filled by receiving ISR.
};

#endif //AIR_CONDITIONING_CONTROLLER_IRDATA_H
