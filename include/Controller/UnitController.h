#ifndef AIR_CONDITIONING_CONTROLLER_UNITCONTROLLER_H
#define AIR_CONDITIONING_CONTROLLER_UNITCONTROLLER_H

#include <Sensors/HumiditySensor.h>
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
            Sensors::TemperatureSensor & temperatureSensor;
            Sensors::HumiditySensor & humiditySensor;
            Devices::AirConditioner & airConditioner;
            Displays::Display & display;
            const Time::Source & timeSource;

            /** Target temperature we want to achieve with Air Conditioning */
            TargetTemperature targetTemperature = TargetTemperature();

            /** Interval for updating temperature on screen and checking whether AC needs to be enabled / disabled */
            static constexpr unsigned short temperatureUpdateInterval = 10; // seconds

            /** Initialize with negative value so we get first temperature update without latency */
            Time::Timestamp lastTemperatureUpdate = Time::Timestamp(-temperatureUpdateInterval);

            /** Whether this controller should control the temperature or just update screen information */
            bool isAcManagementEnabled = true;

            /** Whether we think AC unit is currently enabled or not */
            bool isAcEnabled = false;

            /**
             * Interval for validating that temperature falls down when ac is enabled and does not fall down whenAC
             * is disabled.
             */
            static constexpr unsigned short statusEvaluationInterval = 180;

            /** Last time we performed ac status evaluation */
            Time::Timestamp lastEvaluationTimestamp = Time::Timestamp(0);

            /** Reference temperature for the ac evaluation */
            Measures::Temperature refTemperature = Measures::Temperature();

            /** Toggles air conditioning when required */
            void toggleAirConditioning(const Measures::Temperature & temperature);

            /** Updates temperature visible on the screen */
            void updateDisplayData(const Measures::Temperature & temperature, const Measures::Humidity & humidity);

            /**
             * Evaluates AC status and repeats last command if required, e.g. when AC should be on but we
             * think it isn't because temperature is still raising.
             */
            void evaluateAirConditioningStatus(const Measures::Temperature & temperature);

            /** Saves controller state to persistent memory */
            void persistState() const;

            /** Restores controller state from persistent memory */
            void restoreState();
        public:
            explicit UnitController(
                    Sensors::TemperatureSensor & temperatureSensor,
                    Sensors::HumiditySensor & humiditySensor,
                    Devices::AirConditioner & airConditioner,
                    Displays::Display & display,
                    const Time::Source & timeSource
            ):
                temperatureSensor(temperatureSensor),
                humiditySensor(humiditySensor),
                airConditioner(airConditioner),
                display(display),
                timeSource(timeSource) {}

            void initialize();
            void process();
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_UNITCONTROLLER_H
