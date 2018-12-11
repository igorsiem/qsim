/**
 * \file tick.h
 * Declarations related to simulation ticks
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include "qsim_time.h"

#ifndef _qsim_tick_h_included
#define _qsim_tick_h_included

namespace qsim {

/**
 * \brief Tick counter for a simulation
 *
 * The beginning of simulation time (0 sec) is tick 0 (everything
 * initialised); tick number 1 is the end of the first time slice.
 */
using tick_t = unsigned long int;

/**
 * \brief The length of simulation time for one tick
 */
using tick_increment_t = duration_sec_t;

}   // end qsim namespace

#endif
