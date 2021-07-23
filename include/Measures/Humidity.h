#ifndef AIR_CONDITIONING_CONTROLLER_HUMIDITY_H
#define AIR_CONDITIONING_CONTROLLER_HUMIDITY_H

#include <stdlib.h>
#include <math.h>
#include "DoubleValue.h"

namespace ACC::Measures {
    /**
     * Representation of the humidity
     */
    class Humidity : public DoubleValue {
        protected:
            static constexpr unsigned char formattedBufferSize = 7;
            char formattedValue[formattedBufferSize];
        public:
            /** Construct from humidity value */
            explicit Humidity(double humidity);

            /** Copy constructor */
            Humidity(const Humidity & copyFrom);

            /** By default construct humidity with no actual value */
            explicit Humidity():
                Humidity(NAN) {}

            /** Construct from humidity string */
            explicit Humidity(const char * humidity):
                Humidity(strtod(humidity, nullptr)) {}

            /** Return humidity value */
            double getHumidity() const {
                return rawValue;
            }

            /** Returns formatted humidity string */
            const char * getFormattedHumidity() const {
                return formattedValue;
            }

            /** Assignment operator */
            Humidity & operator=(const Humidity & copyFrom);

            /** Overloaded strict comparison that compares by string representation */
            bool operator==(const Humidity & other) const;
            bool operator!=(const Humidity & other) const;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_HUMIDITY_H
