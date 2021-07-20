#ifndef AIR_CONDITIONING_CONTROLLER_SOURCE_H
#define AIR_CONDITIONING_CONTROLLER_SOURCE_H

#include "Timestamp.h"

namespace ACC::Time {
    class Source {
        public:
            inline Timestamp currentTimestamp() const {
                return Timestamp();
            }
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_SOURCE_H
