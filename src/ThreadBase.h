//
// Created by Gavin on 8/30/2017.
//

#ifndef MUDBASE_THREADBASE_H
#define MUDBASE_THREADBASE_H

#include <thread>
#include <string>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "barrier.h"

namespace mudbase {

    class ThreadManager;

    class ThreadBase;

    typedef boost::shared_ptr<ThreadBase> ThreadBase_ptr;

    typedef enum {
        THREAD_UNKNOWN,
        THREAD_PLAYER,
        THREAD_ADMIN,
        THREAD_LOGIN
    } ThreadType;

    class ThreadBase
            : public boost::enable_shared_from_this<ThreadBase>,
              private boost::noncopyable {
    public:
        ThreadBase(ThreadManager &manager, barrier *b, ThreadType t = THREAD_UNKNOWN);

        void start();

        void stop();

	std::thread::id id();

    protected:
        virtual void thread_func() = 0;

        std::thread thread_;
        bool abort_;
        ThreadManager &manager_;
        barrier *barrier_;
        ThreadType type_;
    };

} // namespace mudbase

#endif //MUDBASE_THREADBASE_H
