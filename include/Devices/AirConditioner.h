#ifndef AIR_CONDITIONING_CONTROLLER_AIRCONDITIONER_H
#define AIR_CONDITIONING_CONTROLLER_AIRCONDITIONER_H

namespace ACC::Devices {
    enum AirConditionerStatus {
        UNAVAILABLE, // The device in unavailable (offline)
        TURNED_OFF, // Device is online, air conditioning is turned off
        TURNED_ON, // Device is online, air conditioning is turned on
    };

    /**
     * Interface for AirConditioners device
     */
    class AirConditioner {
        public:
            /** Returns current air conditioning status */
            virtual AirConditionerStatus getStatus() const = 0;
            /** Turns on the device (if possible) */
            virtual void turnOn(bool forceRepeat = false) = 0;
            /** Turns off the device (if possible) */
            virtual void turnOff(bool forceRepeat = false) = 0;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_AIRCONDITIONER_H
