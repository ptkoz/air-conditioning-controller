#ifndef AIR_CONDITIONING_CONTROLLER_AIRCONDITIONER_H
#define AIR_CONDITIONING_CONTROLLER_AIRCONDITIONER_H

namespace ACC::Devices {
    /**
     * Interface for AirConditioners device
     */
    class AirConditioner {
        public:
            virtual void turnOn() = 0;
            virtual void turnOff() = 0;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_AIRCONDITIONER_H
