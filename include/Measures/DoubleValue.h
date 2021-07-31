#ifndef AIR_CONDITIONING_CONTROLLER_DOUBLEVALUE_H
#define AIR_CONDITIONING_CONTROLLER_DOUBLEVALUE_H

namespace ACC::Measures {
    /**
     * Encapsulated double value
     */
    class DoubleValue {
        protected:
            double rawValue;

        public:
            explicit DoubleValue(double value):
                rawValue(value) {};

            /** Comparison operators checks equality to first decimal point */
            virtual bool operator==(const DoubleValue & other) const {
                return round(rawValue * 10) == round(other.rawValue * 10);
            }

            virtual bool operator!=(const DoubleValue & other) const {
                return round(rawValue * 10) != round(other.rawValue * 10);
            }

            /** Greater than / smaller than operators check 0.1 significance */
            bool operator>(const DoubleValue & other) const {
                return rawValue > other.rawValue + 0.1f;
            }

            bool operator>=(const DoubleValue & other) const {
                return rawValue >= other.rawValue;
            }

            bool operator<(const DoubleValue & other) const {
                return rawValue < other.rawValue - 0.1f;
            }

            bool operator<=(const DoubleValue & other) const {
                return rawValue <= other.rawValue;
            }
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_DOUBLEVALUE_H
