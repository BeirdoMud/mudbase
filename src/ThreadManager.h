//
// Created by Gavin on 8/30/2017.
//

#ifndef MUDBASE_THREADMANAGER_H
#define MUDBASE_THREADMANAGER_H

#include <cstddef>
#include <chrono>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <set>
#include <boost/assert.hpp>
#include <boost/fiber/all.hpp>
#include "barrier.h"
#include "ThreadBase.h"

namespace mudbase {

    typedef std::unique_lock<std::mutex> lock_t;

    class ThreadManager {
    public:
        void register_thread(ThreadBase_ptr fiber);

        void deregister_thread(ThreadBase_ptr fiber);

        void shutdown();

        void wait();

        void init_thread(barrier *b);

        std::size_t count();

    private:
        std::size_t thread_count_;
        std::mutex mtx_count_;
        boost::fibers::condition_variable_any cnd_count_;

        std::set<ThreadBase_ptr> threads_;
    };

} // namespace mudbase

#endif //MUDBASE_THREADMANAGER_H