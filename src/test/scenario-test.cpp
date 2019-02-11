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
    test_models::null_model_factory mf{10};

    // Scenario created and populated using model factory
    qsim::scenario scenario(thread_pool);
    REQUIRE_NOTHROW(scenario.populate_from(mf));

    // We have 10 models, uninitialised
    REQUIRE(scenario.entities_size() == 10);
    REQUIRE(mf.mntr->initialised_entity_count() == 0);

    // Initialise the scenario - every entity is initialised
    REQUIRE_NOTHROW(scenario.init());
    REQUIRE(mf.mntr->initialised_entity_count() == 10);
    for (qsim::model_instance_id_t i = 1; i <= 10; i++)
        REQUIRE(mf.mntr->entity_is_initialised(i) == true);

    // Tick the scenario - all 10 models have been ticked.
    scenario.tick();
    REQUIRE(mf.mntr->ticked_entity_count() == 10);

}   // end scenario creation test

TEST_CASE("running scenario with multiple models", "[integration][scenario")
{
    auto thread_pool = std::make_shared<qlib::thread_pool>();
    qsim::scenario scenario(thread_pool);

    // Model factory adds a time model and a null model.
    test_models::one_of_each_model_factory mf;
    scenario.populate_from(mf);

    // We have two models, uninitialised.
    REQUIRE(scenario.entities_size() == 2);
    REQUIRE(mf.mntr->initialised_entity_count() == 0);

    // Initialise - all models initialised - no models ticked
    scenario.init();
    REQUIRE(mf.mntr->initialised_entity_count() == 2);
    REQUIRE(mf.mntr->ticked_entity_count() == 0);
    REQUIRE(mf.mntr->entity_tick_count(1) == 0);
    REQUIRE(mf.mntr->entity_tick_count(1) == 0);
    REQUIRE(scenario.next_tick_index() == 0);

    // Tick index zero - all entities ticked once, time set to zero, next
    // tick is tick index one.
    scenario.tick();
    REQUIRE(mf.mntr->ticked_entity_count() == 2);
    REQUIRE(mf.mntr->entity_tick_count(1) == 1);
    REQUIRE(mf.mntr->entity_tick_count(2) == 1);
    REQUIRE(mf.mntr->latest_time_sec() == 0.0);
    REQUIRE(scenario.next_tick_index() == 1);

    // Tick index one - all entities ticked twice, time set to 1.0, next
    // tick is tick index two.
    scenario.tick();
    REQUIRE(mf.mntr->ticked_entity_count() == 2);
    REQUIRE(mf.mntr->entity_tick_count(1) == 2);
    REQUIRE(mf.mntr->entity_tick_count(2) == 2);
    REQUIRE(mf.mntr->latest_time_sec() == 1.0);
    REQUIRE(scenario.next_tick_index() == 2);

}   // end running scenario method
