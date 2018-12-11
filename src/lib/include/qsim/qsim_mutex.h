/**
 * \file qsim_mutex.h
 * Mutex / lock guard definitions for qsim
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <shared_mutex>

#ifndef _qsim_qsim_mutex_h_included
#define _qsim_qsim_mutex_h_included

namespace qsim {

/**
 * \brief Type of mutex used throughout qSim
 */
using mutex = std::shared_mutex;

/**
 * \brief Non-exclusive lock to read protected data
 */
using read_lock = std::shared_lock<mutex>;

/**
 * \brief Exclusive lock to write protected data
 */
using write_lock = std::unique_lock<mutex>;

}   // end qsim namespace

#endif
