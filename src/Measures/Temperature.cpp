#include "Measures/Temperature.h"

using namespace ACC::Measures;

DecimalString Temperature::getFormattedTemperature() const {
    DecimalString formattedValue(rawValue, 8, 5, 1);
    formattedValue += "*C";
    return formattedValue;
}
