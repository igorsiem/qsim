/**
 * \file tick_time.h
 * An data type and InfoStore for tracking time in test simulations
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <string>
#include <qsim/qsim.h>

#ifndef _test_models_tick_time_h_included
#define _test_models_tick_time_h_included

namespace test_models {

struct tick_time
{

    qsim::tick_count_t tick_count;      // The time step number

    qsim::time_duration_sec_t time_sec; // Time since start of sim

};  //  end tick_time struct

using tick_time_is_t = qsim::infostore<tick_time>;

}   // end test_models namespace

#endif
