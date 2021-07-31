#ifndef AIR_CONDITIONING_CONTROLLER_DECIMALSTRING_H
#define AIR_CONDITIONING_CONTROLLER_DECIMALSTRING_H

namespace ACC::Measures {
    /**
     * Holds a double value as decimal string.
     */
    class DecimalString {
        protected:
            const unsigned char length;
            char * buffer;
        public:
            /** Allocate the memory */
            explicit DecimalString(
                double value,
                unsigned char bufferLength,
                char decimalWidth,
                unsigned char decimalPrecision
            );

            /** Copy constructor that copies all the contents */
            DecimalString(const DecimalString & copyFrom);

            /** Free the memory */
            ~DecimalString();

            /** Allow concatenating something (e.g. unit). It's up to the caller to reserve the right amount of memory */
            DecimalString & operator+=(const char * toAttach);

            /** Allows using this just as char array */
            operator const char *() const {
                return buffer;
            }
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_DECIMALSTRING_H
