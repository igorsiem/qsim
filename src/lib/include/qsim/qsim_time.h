/**
 * \file qsim_time.h
 * Basic declarations around the qSim definition of time
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <chrono>

#ifndef _qsim_qsim_time_h_included
#define _qsim_qsim_time_h_included

namespace qsim {

/**
 * \brief The clock type used throughout qSim
 */
using clock_t = std::chrono::system_clock;

/**
 * \brief The duration type used throughout qSim - reckoned in
 * double-precision seconds
 */
using duration_sec_t = std::chrono::duration<double, std::ratio<1, 1> >;

/**
 * \brief The time point type used throughout qSim
 */
using time_point_t = std::chrono::time_point<clock_t>;

}   // end qsim namespace

#endif
