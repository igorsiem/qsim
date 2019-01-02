/**
 * \file null_model.h
 * Declares the `null_model` class - a 'do nothing' model for testing
 * architectures
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <string>

#ifndef _test_models_string_factor_included_h
#define _test_models_string_factor_included_h

namespace test_models {

struct string_factory
{

    using data_t = std::string;

    data_t s;

    explicit string_factory(data_t _s) : s(std::move(_s)) {}

    data_t get(void) const { return s; }

};  // end string_factory struct

}   // end test_models

#endif