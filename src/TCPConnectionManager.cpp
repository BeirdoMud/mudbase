//
// Created by Gavin on 8/29/2017.
//

#include "TCPConnection.h"
#include "TCPConnectionManager.h"
#include <algorithm>
#include <boost/bind.hpp>

namespace mudbase {
    void TCPConnectionManager::start(TCPConnection_ptr c) {
        connections_.insert(c);
        c->start();
    }

    void TCPConnectionManager::stop(TCPConnection_ptr c) {
        connections_.erase(c);
        c->stop();
    }

    void TCPConnectionManager::stop_all() {
        std::for_each(connections_.begin(), connections_.end(),
                      boost::bind(&TCPConnection::stop, _1));
        connections_.clear();
    }
} // namespace mudbase