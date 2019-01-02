/**
 * \file data_factory-test.cpp
 * Basic tests for the `data_factory` concept
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <catch/catch.hpp>
#include <qsim/qsim.h>
#include "test-models/test-models.h"

// Function for retrieving data from a data factory
template <QSIM_CONCEPT(qsim::is_data_factory) T>
typename T::data_t get_data_from(T& t)
{
    return t.get();
}

// Basic check of the data factory concept
TEST_CASE("data_factory", "[unit][data_factory]")
{
    // Instantiate a string factory from the test model set
    test_models::string_factory sf("abc");
    REQUIRE(get_data_from(sf) == "abc");
}   // end data_factory basic test
