/**
 * \file scenario-test.cpp
 * Tests for the model factory concept and scenario class
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

// Test creation of a scenario using a model factory
TEST_CASE("scenario creation", "[unit][scenario]")
{
    // Model factory creates 10 models
    test_models::model_factory mf{10};

    // Scenario created and populated using model factory
    qsim::scenario scenario;
    REQUIRE_NOTHROW(scenario.populate_from(mf));

    // We have 10 models
    REQUIRE(scenario.models_size() == 10);

    // TODO more functionality
}   // end scenario creation test
