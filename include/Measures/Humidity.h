#ifndef AIR_CONDITIONING_CONTROLLER_HUMIDITY_H
#define AIR_CONDITIONING_CONTROLLER_HUMIDITY_H

#include <math.h>
#include "FloatValue.h"
#include "DecimalString.h"

namespace ACC::Measures {
    /**
     * Representation of the humidity
     */
    class Humidity : public FloatValue {
        public:
            /** Construct from humidity value */
            explicit Humidity(float humidity):
                    FloatValue(humidity) {}

            /** By default construct humidity with no actual value */
            explicit Humidity():
                Humidity(NAN) {}

            /** Assignment operator */
            Humidity & operator=(const Humidity & copyFrom) {
                rawValue = copyFrom.rawValue;
                return *this;
            }

            /** Returns formatted humidity string */
            DecimalString getFormattedHumidity() const;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_HUMIDITY_H
