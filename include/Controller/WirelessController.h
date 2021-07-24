#ifndef AIR_CONDITIONING_CONTROLLER_WIRELESSCONTROLLER_H
#define AIR_CONDITIONING_CONTROLLER_WIRELESSCONTROLLER_H

#include <Stream.h>
#include "WirelessExecutor.h"

namespace ACC::Controller {
    /**
     * Wireless controller reads remote commands and reacts to them. It can also sent commands to other devices.
     */
    class WirelessController : public WirelessExecutor {
        private:
            Stream & dataStream;
            unsigned char setPin;

        public:
            explicit WirelessController(Stream & dataStream, unsigned char setPin):
                dataStream(dataStream),
                setPin(setPin) {}

            void initialize();
            void remoteCommand(
                unsigned short address,
                unsigned short command,
                const void * message,
                size_t length
            ) override;
    };
}

#endif //AIR_CONDITIONING_CONTROLLER_WIRELESSCONTROLLER_H
