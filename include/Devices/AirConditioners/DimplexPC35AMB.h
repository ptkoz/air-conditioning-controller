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
            unsigned long lastStatusChangeTimestamp;
            const unsigned short irFrequency;
            IRsend & irEmitter;

            static unsigned long getMillisSinceEvent(unsigned long eventTimestamp);
            bool canChangeStatus() const;
        public:
            explicit DimplexPC35AMB(IRsend & irEmitter);
            ~DimplexPC35AMB();
            bool turnOn() override;
            bool turnOff() override;
            void setLowSpeed();
            void setHighSpeed();
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_DIMPLEXPC35AMB_H
