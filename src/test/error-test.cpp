/**
 * \file error-test.cpp
 * Test for the qSim error class
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <catch/catch.hpp>
#include <qsim/qsim.h>

// Verify the operation of the error class declaration macros
DECLARE_ERROR_CLASS(test_error1, std::runtime_error)
DECLARE_MESSAGE_ERROR_CLASS(test_error2, std::exception, "second error")

// Basic verification of error signalling and handling
TEST_CASE("error", "[unit][error]")
{

    try
    {
        throw test_error1("first error");

        FAIL("exception was not thrown as expected");
    }
    catch (const test_error1& error)
    {
        REQUIRE(std::string(error.what()) == "first error");
    }
    catch (...)
    {
        FAIL("some exception other than test_error1 was throw");
    }

    try
    {
        RAISE_ERROR_WITH_DEBUG_MESSAGE(test_error2, "test debug message");

        FAIL("exception was not thrown as expected");
    }
    catch (const test_error2& error)
    {
        REQUIRE(std::string(error.what()) == "second error");
    }
    catch (...)
    {
        FAIL("some exception other than test_error2 was throw");
    }

}   // end error test
