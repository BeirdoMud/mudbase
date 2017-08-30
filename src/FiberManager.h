//
// Created by Gavin on 8/30/2017.
//

#ifndef MUDBASE_FIBERMANAGER_H
#define MUDBASE_FIBERMANAGER_H

#include <cstddef>
#include <chrono>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <set>
#include <boost/assert.hpp>
#include <boost/fiber/all.hpp>
#include "barrier.h"
#include "FiberBase.h"

namespace mudbase {

    typedef std::unique_lock<std::mutex> lock_t;

    class FiberManager {
    public:
        void register_fiber(FiberBase_ptr fiber);
        void deregister_fiber(FiberBase_ptr fiber);
        void shutdown();
        void wait();
        void init_thread(barrier *b);
        std::size_t count();

    private:
        std::size_t fiber_count_;
        std::mutex mtx_count_;
        boost::fibers::condition_variable_any cnd_count_;

        std::set<FiberBase_ptr> fibers_;
    };

    typedef struct {
        barrier *b;
        FiberManager& manager;
    } ThreadArgs;

} // namespace mudbase

#endif //MUDBASE_FIBERMANAGER_H
