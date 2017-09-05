//
// Created by Gavin on 9/4/2017.
//

#include <unistd.h>
#include <string>
#include <boost/fiber/all.hpp>
#include "FiberPlaying.h"
#include "main.h"

namespace mudbase {

    FiberPlaying::FiberPlaying(FiberManager &manager, PlayerConnection_ptr conn)
            : FiberBase(manager), connection_(conn) {
    }

    bool FiberPlaying::fiber_func() {
        // This fiber allows for playing the mud

        // There will be a parser module (that depends on the context of where the player is, and what kind of player)
        // For now, let's just grab input and echo it back, and disconnect on an empty line

        if (!connection_->hasInput()) {
            return true;
        }

        std::string &line = connection_->readLine();

        if (line.empty()) {
            connection_->close();
            return false;
        }

        connection_->writeLine(line);

        // Yield
        return true;
    }

} // namespace mudbase
