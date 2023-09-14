#ifndef AIR_CONDITIONING_CONTROLLER_ADDRESSES_H
#define AIR_CONDITIONING_CONTROLLER_ADDRESSES_H

namespace ACC::Persistence::Address {
    static constexpr unsigned short acStatus = 0x01; // boolean, 1 byte
    static constexpr unsigned short targetTemperature = 0x02; // float, 4 bytes
    static constexpr unsigned short acManagementEnabled = 0x06; // boolean, 1 byte
}

#endif //AIR_CONDITIONING_CONTROLLER_ADDRESSES_H
