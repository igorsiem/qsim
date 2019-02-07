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
 * \brief Time step counter for a simulation
 *
 * The beginning of simulation time (0 time) is tick 0 (everything
 * initialised); tick number 1 begins at the end of the first time slice.
 */
using tick_count_t = signed long int;

/**
 * \brief The type used to denote the duration of a single time step in
 * seconds
 */
using tick_duration_sec_t = time_duration_sec_t;

}   // end qsim namespace

#endif
