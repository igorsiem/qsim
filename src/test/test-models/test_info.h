/**
 * \file test_info.h
 * Declares the `test_info` class
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <string>

#ifndef _test_models_test_info_included_h
#define _test_models_test_info_included_h

namespace test_models {

struct test_info
{
    int i;
    std::string str;
    double d;

    test_info(int _i, std::string _str, double _d) :
        i(_i), str(std::move(_str)), d(_d) {}

};  // end test_info struct

}   // end test_models method

#endif
