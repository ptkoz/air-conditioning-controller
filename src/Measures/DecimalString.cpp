#include "Measures/DecimalString.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

using ACC::Measures::DecimalString;

DecimalString::DecimalString(
    float value,
    unsigned char bufferLength,
    char decimalWidth,
    unsigned char decimalPrecision
):
    length(bufferLength) {
    buffer = new char[length];

    if (isnan(value)) {
        unsigned char startIndex = 0;
        while (startIndex < decimalWidth - 3) {
            buffer[startIndex++] = ' ';
        }

        strncpy(&buffer[startIndex], "-.-", length - startIndex);
    } else {
        dtostrf(value, decimalWidth, decimalPrecision, buffer);
    }
}

DecimalString::~DecimalString() {
    delete[] buffer;
}

DecimalString::DecimalString(const DecimalString & copyFrom):
    length(copyFrom.length) {
    buffer = new char[length];
    strncpy(buffer, copyFrom.buffer, length);
}

DecimalString & ACC::Measures::DecimalString::operator+=(const char * toAttach) {
    strcat(buffer, toAttach);
    return *this;
}
