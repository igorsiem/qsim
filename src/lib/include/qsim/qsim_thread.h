/**
 * \file qsim_thread.h
 * Mutex / lock guard definitions for qsim
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <shared_mutex>
#include <qlib/qlib.h>

#ifndef _qsim_qsim_thread_h_included
#define _qsim_qsim_thread_h_included

namespace qsim {

/**
 * \brief Type of mutex used throughout qSim
 */
using shared_mutex = qlib::shared_mutex;

/**
 * \brief Non-exclusive lock to read protected data
 */
using read_lock = std::shared_lock<shared_mutex>;

/**
 * \brief Exclusive lock to write protected data
 */
using write_lock = std::unique_lock<shared_mutex>;

/**
 * \brief The thread pool type used for parallelisation
 */
using thread_pool = qlib::thread_pool;

/**
 * \brief The future object type used in qSim (taken from qLib)
 */
template <typename R> using future = qlib::future<R>;

/**
 * \page Multithreading
 *
 * *qSim* is a multi-threaded application that uses parallel execution to
 * speed up simulation times. The core element of most parallelised
 * algorithms is the `thread_pool` class (from the `qlib` library), which is
 * simple implementation of a Worker Thread Pool.
 *
 * Most *qSim* executables will instantiate a single `thread_pool` instance
 * that is passed around the various elements as a shared pointer, and can
 * schedule tasks whenever they need to. One of example of this is the
 * `init` method of the `scenario` class, which initialises the models in
 * parallel.
 *
 * \todo Expand Multithreading page to discuss parallelism and lock-step
 * simulation
 */

}   // end qsim namespace

#endif
