#ifndef AIR_CONDITIONING_CONTROLLER_ADDRESSES_H
#define AIR_CONDITIONING_CONTROLLER_ADDRESSES_H

namespace ACC::Persistence::Address {
    static constexpr unsigned short acStatus = 0x01;
    static constexpr unsigned short targetTemperature = 0x02;
}

#endif //AIR_CONDITIONING_CONTROLLER_ADDRESSES_H
