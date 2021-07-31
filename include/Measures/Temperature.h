#ifndef AIR_CONDITIONING_CONTROLLER_TEMPERATURE_H
#define AIR_CONDITIONING_CONTROLLER_TEMPERATURE_H

#include <math.h>
#include "DoubleValue.h"

namespace ACC::Measures {
    /**
     * Representation of the temperature
     */
    class Temperature : public DoubleValue {
        protected:
            static constexpr unsigned char formattedBufferSize = 8;
            char formattedValue[formattedBufferSize];
        public:
            /** Construct from temperature value */
            explicit Temperature(double temperature);

            /** Copy constructor */
            Temperature(const Temperature & copyFrom);

            /** By default construct temperature with no actual value */
            explicit Temperature():
                    Temperature(NAN) {}

            /** Return temperature value */
            double getTemperature() const {
                return rawValue;
            }

            /** Returns formatted temperature string */
            const char * getFormattedTemperature() const {
                return formattedValue;
            }

            /** Assignment operator */
            Temperature & operator=(const Temperature & copyFrom);

            /** Overloaded strict comparison that compares by string representation */
            bool operator==(const Temperature & other) const;
            bool operator!=(const Temperature & other) const;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_TEMPERATURE_H
