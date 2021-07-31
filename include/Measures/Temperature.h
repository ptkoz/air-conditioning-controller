#ifndef AIR_CONDITIONING_CONTROLLER_TEMPERATURE_H
#define AIR_CONDITIONING_CONTROLLER_TEMPERATURE_H

#include <math.h>
#include "DoubleValue.h"
#include "DecimalString.h"

namespace ACC::Measures {
    /**
     * Representation of the temperature
     */
    class Temperature : public DoubleValue {
        public:
            /** Construct from temperature value */
            explicit Temperature(double temperature):
                DoubleValue(temperature) {}

            /** By default construct temperature with no actual value */
            explicit Temperature():
                Temperature(NAN) {}

            /** Assignment operator */
            Temperature & operator=(const Temperature & copyFrom) {
                rawValue = copyFrom.rawValue;
                return *this;
            }

            /** Return temperature value */
            double getTemperature() const {
                return rawValue;
            }

            /** Returns formatted temperature string */
            DecimalString getFormattedTemperature() const;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_TEMPERATURE_H
