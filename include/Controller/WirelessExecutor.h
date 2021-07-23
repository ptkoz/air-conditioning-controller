#ifndef AIR_CONDITIONING_CONTROLLER_WIRELESSEXECUTOR_H
#define AIR_CONDITIONING_CONTROLLER_WIRELESSEXECUTOR_H

#include "Arduino.h"

namespace ACC::Controller {
    /**
     * Interface for executing remote commands
     */
     class WirelessExecutor {
         public:
             virtual void remoteCommand(
                 unsigned short address,
                 unsigned short command,
                 const void * message = nullptr,
                 size_t length = 0
             ) = 0;
     };
}

#endif //AIR_CONDITIONING_CONTROLLER_WIRELESSEXECUTOR_H
