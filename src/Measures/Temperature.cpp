#include <string.h>
#include <stdlib.h>
#include "Measures/Temperature.h"

using namespace ACC::Measures;

Temperature::Temperature(const Temperature & copyFrom):
        DoubleValue(copyFrom.rawValue),
        formattedValue{} {
    strncpy(formattedValue, copyFrom.formattedValue, formattedBufferSize);
}

Temperature::Temperature(double temperature):
        DoubleValue(temperature),
        formattedValue{} {

    // the * looks pretty close to a degree sign and the fonts are updated to actually display degree sign on the screen
    if (isnan(rawValue)) {
        strncpy(formattedValue, "  -.-*C", formattedBufferSize);
    } else {
        dtostrf(temperature, 5, 1, formattedValue);
        strcat(formattedValue, "*C");
    }
}

Temperature & Temperature::operator=(const Temperature & copyFrom) {
    if (&copyFrom != this) {
        rawValue = copyFrom.rawValue;
        strncpy(formattedValue, copyFrom.formattedValue, formattedBufferSize);
    }

    return *this;
}

bool Temperature::operator==(const Temperature & other) const {
    return strcmp(formattedValue, other.formattedValue) == 0;
}

bool Temperature::operator!=(const Temperature & other) const {
    return strcmp(formattedValue, other.formattedValue) != 0;
}
