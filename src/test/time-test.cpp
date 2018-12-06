/**
 * \file time-test.cpp
 * Tests for qSim basic time definitions
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <thread>
#include <catch/catch.hpp>
#include <qsim/qsim.h>

TEST_CASE("time definitions", "[unit][time]")
{

    using namespace std::chrono_literals;

    qsim::time_point_t start = qsim::clock_t::now();
    std::this_thread::sleep_for(1s);
    qsim::time_point_t finish = qsim::clock_t::now();

    qsim::duration_sec_t dur = finish-start;

    REQUIRE(dur.count() == Approx(1).epsilon(0.01));

}   // end test of time definitions
