#include "Measures/Humidity.h"

using namespace ACC::Measures;

DecimalString Humidity::getFormattedHumidity() const {
    DecimalString formattedValue(rawValue, 7, 5, 1);
    formattedValue += "%";
    return formattedValue;
}
