#include <string.h>
#include "Measures/Humidity.h"

using namespace ACC::Measures;

Humidity::Humidity(const Humidity & copyFrom):
        DoubleValue(copyFrom.rawValue),
        formattedValue{} {
    strncpy(formattedValue, copyFrom.formattedValue, formattedBufferSize);
}

Humidity::Humidity(double humidity):
        DoubleValue(humidity),
        formattedValue{} {

    if (isnan(rawValue)) {
        strncpy(formattedValue, "  -.-%", formattedBufferSize);
    } else {
        dtostrf(humidity, 5, 1, formattedValue);
        strcat(formattedValue, "%");
    }
}

Humidity & Humidity::operator=(const Humidity & copyFrom) {
    if (&copyFrom != this) {
        rawValue = copyFrom.rawValue;
        strncpy(formattedValue, copyFrom.formattedValue, formattedBufferSize);
    }

    return *this;
}

bool Humidity::operator==(const Humidity & other) const {
    return strcmp(formattedValue, other.formattedValue) == 0;
}

bool Humidity::operator!=(const Humidity & other) const {
    return strcmp(formattedValue, other.formattedValue) != 0;
}
