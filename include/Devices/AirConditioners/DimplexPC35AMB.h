#ifndef AIR_CONDITIONING_CONTROLLER_DIMPLEXPC35AMB_H
#define AIR_CONDITIONING_CONTROLLER_DIMPLEXPC35AMB_H

#include "devices/AirConditioner.h"
#include <IRSend.h>

namespace ACC::Devices::AirConditioners {
    /**
     * Air conditioner implementation for Dimplex device
     */
    class DimplexPC35AMB : public AirConditioner {
        private:
            const unsigned short irFrequency;
            IRsend & irEmitter;

        public:
            explicit DimplexPC35AMB(unsigned char irPin);
            explicit DimplexPC35AMB(IRsend & irEmitter);
            ~DimplexPC35AMB();
            void turnOn() override;
            void turnOff() override;
            void setLowSpeed();
            void setHighSpeed();
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_DIMPLEXPC35AMB_H
