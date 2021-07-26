#ifndef AIR_CONDITIONING_CONTROLLER_AIRCONDITIONER_H
#define AIR_CONDITIONING_CONTROLLER_AIRCONDITIONER_H

namespace ACC::Devices {
    /**
     * Interface for AirConditioners device
     */
    class AirConditioner {
        public:
            /** Whether AC Unit is available (online) */
            virtual bool isAvailable() = 0;
            /** Tries to turn on the AC */
            virtual bool turnOn() = 0;
            /** Tries to turn off the AC */
            virtual bool turnOff() = 0;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_AIRCONDITIONER_H
