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
    auto thread_pool = std::make_shared<qlib::thread_pool>();

    // Model factory creates 10 models
    test_models::model_factory mf{10};

    // Scenario created and populated using model factory
    qsim::scenario scenario(thread_pool);
    REQUIRE_NOTHROW(scenario.populate_from(mf));

    // We have 10 models, uninitialised
    REQUIRE(scenario.models_size() == 10);
    REQUIRE(mf.mntr->initialised_entity_count() == 0);

    // Initialise the scenario - every entity is initialised
    REQUIRE_NOTHROW(scenario.init());
    REQUIRE(mf.mntr->initialised_entity_count() == 10);
    for (qsim::model_instance_id_t i = 1; i <= 10; i++)
        REQUIRE(mf.mntr->entity_is_initialised(i) == true);

    // TODO more functionality
}   // end scenario creation test
