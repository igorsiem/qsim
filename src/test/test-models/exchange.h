/**
 * \file test_info.h
 * Declares types for information exchange between test models
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <string>
#include <qsim/qsim.h>
#include "test_info.h"

#ifndef _test_models_exchange_h_included
#define _test_models_exchange_h_included

namespace test_models {

using test_info_is_t = qsim::infostore<test_info>;

using string_is_t = qsim::infostore<std::string>;

using int_is_t = qsim::infostore<int>;

using is_exchange_t = qsim::is_exchange<test_info, std::string, int>;

}   // end test_models namespace

#endif
