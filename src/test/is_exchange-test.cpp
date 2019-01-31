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

// Simple tests for an InfoStore exchange
TEST_CASE("is_exchange", "[unit][is_exchange]")
{
    // Create an IS exchange from the test models library
    using is_exchange_t = test_models::is_exchange_t;
    is_exchange_t ise;

    // Get references to our InfoStore objects from the Exchange. Each of
    // them starts off empty.
    auto& test_info_is = qsim::get_infostore<test_models::test_info>(ise);
    auto& string_is = qsim::get_infostore<std::string>(ise);
    auto& int_is = qsim::get_infostore<int>(ise);

    REQUIRE(test_info_is.current_data_from(1).size() == 0);
    REQUIRE(string_is.current_data_from(1).size() == 0);
    REQUIRE(int_is.current_data_from(1).size() == 0);
    
    // Add a data time to each of the IS collections.
    using test_info_is_t = test_models::test_info_is_t;
    using string_is_t = test_models::string_is_t;
    using int_is_t = test_models::int_is_t;

    test_info_is.add(
        1
        , test_info_is_t::info_vector{
            test_models::test_info{1, "one", 1.0 }});

    string_is.add(
        1
        , string_is_t::info_vector{ std::string("abc") });

    int_is.add(
        1
        , int_is_t::info_vector{ 1 });

    // Now, the IS objects have some current data
    REQUIRE(test_info_is.current_data_from(1).size() == 1);
    REQUIRE(string_is.current_data_from(1).size() == 1);
    REQUIRE(int_is.current_data_from(1).size() == 1);    

    SECTION("clear exchange sequentially")
    {
        // Call clear on each IS in the exchange - IS objects are now empty.
        clear(ise);

        REQUIRE(test_info_is.current_data_from(1).size() == 0);
        REQUIRE(string_is.current_data_from(1).size() == 0);
        REQUIRE(int_is.current_data_from(1).size() == 0);
    }

    SECTION("clear exchange with parallelisation")
    {
        qsim::thread_pool tp;
        clear(ise, tp);

        REQUIRE(test_info_is.current_data_from(1).size() == 0);
        REQUIRE(string_is.current_data_from(1).size() == 0);
        REQUIRE(int_is.current_data_from(1).size() == 0);
    }

}   // end is_exchange test
