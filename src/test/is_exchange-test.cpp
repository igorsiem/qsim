/**
 * \file infostore-test.cpp
 * Tests for the Infostore Exchange mechanism
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

TEST_CASE("is_exchange", "[unit][is_exchange]")
{
    // Create an IS exchange for our test models
    using is_exchange_t = qsim::is_exchange<test_models::test_info>;
    is_exchange_t ise;

    // Get the test_info ISE out as a ref - verify that it has no data,
    // demonstrating that we can access it OK.
    auto& test_info_is = qsim::get_infostore<test_models::test_info>(ise);
    REQUIRE(test_info_is.current_data_from(1).size() == 0);
}   // end is_exchange test
