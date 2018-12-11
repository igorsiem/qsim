/**
 * \file infostore-test.cpp
 * Basic tests for the the infostore implementation
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

TEST_CASE("infostore", "[unit][infostore]")
{

    // Instantiate the infostore - initially, it has no data.
    using test_info_is = qsim::infostore<test_models::test_info>;
    test_info_is is;

    REQUIRE(is.current_data_from(1).empty());
    REQUIRE(is.previous_data_from(1).empty());
    REQUIRE(is.current_data_from(2).empty());
    REQUIRE(is.previous_data_from(2).empty());
    REQUIRE(is.current_data_from(3).empty());
    REQUIRE(is.previous_data_from(3).empty());

    // Add some data for model 1 - now we have some current data for model 1,
    // but no previous data, or data from models 2 and 3.
    is.add(
        1
        , test_info_is::info_vector{
            test_models::test_info{1, "one", 1.0 }
            , test_models::test_info{2, "two", 2.0}});

    REQUIRE(is.current_data_from(1).size() == 2);
    REQUIRE(is.previous_data_from(1).empty());
    REQUIRE(is.current_data_from(2).empty());
    REQUIRE(is.previous_data_from(2).empty());
    REQUIRE(is.current_data_from(3).empty());
    REQUIRE(is.previous_data_from(3).empty());

    // Add for model 2 - now we have current data for models 1 and 2, but
    // no previous data, and no data for model 3.
    is.add(
        2
        , test_info_is::info_vector{
            test_models::test_info{3, "three", 3.0 }});

    REQUIRE(is.current_data_from(1).size() == 2);
    REQUIRE(is.previous_data_from(1).empty());
    REQUIRE(is.current_data_from(2).size() == 1);
    REQUIRE(is.previous_data_from(2).empty());
    REQUIRE(is.current_data_from(3).empty());
    REQUIRE(is.previous_data_from(3).empty());

    // Swap current / previous (end of sim tick) - current data is now empty,
    // and previous holds what was current before
    is.swap_current_previous();

    REQUIRE(is.current_data_from(1).empty());
    REQUIRE(is.previous_data_from(1).size() == 2);
    REQUIRE(is.current_data_from(2).empty());
    REQUIRE(is.previous_data_from(2).size() == 1);
    REQUIRE(is.current_data_from(3).empty());
    REQUIRE(is.previous_data_from(3).empty());

    // Clear everything (end of sim run), and we're back to empty
    is.clear();

    REQUIRE(is.current_data_from(1).empty());
    REQUIRE(is.previous_data_from(1).empty());
    REQUIRE(is.current_data_from(2).empty());
    REQUIRE(is.previous_data_from(2).empty());
    REQUIRE(is.current_data_from(3).empty());
    REQUIRE(is.previous_data_from(3).empty());

}   // end basic infostore test
