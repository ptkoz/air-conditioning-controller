#ifndef AIR_CONDITIONING_CONTROLLER_FLOATVALUE_H
#define AIR_CONDITIONING_CONTROLLER_FLOATVALUE_H

namespace ACC::Measures {
    /**
     * Encapsulated double value
     */
    class FloatValue {
        protected:
            float rawValue;

        public:
            explicit FloatValue(float value):
                rawValue(value) {};

            /** Comparison operators checks equality to first decimal point */
            virtual bool operator==(const FloatValue & other) const {
                return round(rawValue * 10) == round(other.rawValue * 10);
            }

            virtual bool operator!=(const FloatValue & other) const {
                return round(rawValue * 10) != round(other.rawValue * 10);
            }

            /** Greater than / smaller than operators check 0.1 significance */
            bool operator>(const FloatValue & other) const {
                return rawValue > other.rawValue + 0.1f;
            }

            bool operator>=(const FloatValue & other) const {
                return rawValue >= other.rawValue;
            }

            bool operator<(const FloatValue & other) const {
                return rawValue < other.rawValue - 0.1f;
            }

            bool operator<=(const FloatValue & other) const {
                return rawValue <= other.rawValue;
            }
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_FLOATVALUE_H
