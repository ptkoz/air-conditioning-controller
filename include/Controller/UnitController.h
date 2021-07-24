#ifndef AIR_CONDITIONING_CONTROLLER_UNITCONTROLLER_H
#define AIR_CONDITIONING_CONTROLLER_UNITCONTROLLER_H

#include "TargetTemperature.h"
#include "Devices/AirConditioner.h"
#include "Sensors/TemperatureSensor.h"
#include "Displays/Display.h"
#include "Time/Source.h"

namespace ACC::Controller {
    /**
     * Orchestrates the module - measures temperature & humidity, enables / disables AC, puts information on screen.
     */
    class UnitController {
        private:
            TargetTemperature targetPrimaryTemperature = TargetTemperature();
            bool isAirConditionerEnabled = false;

            Sensors::TemperatureSensor & primaryTemperatureSensor;
            Devices::AirConditioner & airConditioner;
            Displays::Display & display;

            /** Saves controller state to persistent memory */
            void saveState() const;

            /** Restores controller state from persistent memory */
            void restoreState();

        public:
            explicit UnitController(
                    Sensors::TemperatureSensor & primaryTemperatureSensor,
                    Devices::AirConditioner & airConditioner,
                    Displays::Display & display
            ):
                primaryTemperatureSensor(primaryTemperatureSensor),
                airConditioner(airConditioner),
                display(display) {}

            void initialize();
            void process();
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_UNITCONTROLLER_H
