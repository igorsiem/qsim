/**
 * \file model-test.cpp
 * Test for the basic model concept and framework
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

// Test casting functionality for model state
TEST_CASE("casting model state", "[unit][model]")
{

    using namespace qsim;

    // Conversion of model state to human-readable strings
    REQUIRE(to<std::string>(model_state_t::none) == "none");
    REQUIRE(to<std::string>(model_state_t::uninitialised) ==
        "uninitialised");
    REQUIRE(to<std::string>(model_state_t::ready) == "ready");

    REQUIRE(to<std::wstring>(model_state_t::none) == L"none");
    REQUIRE(to<std::wstring>(model_state_t::uninitialised) ==
        L"uninitialised");
    REQUIRE(to<std::wstring>(model_state_t::ready) == L"ready");

    // Conversion of strings to model sequences
    REQUIRE(to_model_state("none") == model_state_t::none);
    REQUIRE(to_model_state("uninitialised") == model_state_t::uninitialised);
    REQUIRE(to_model_state("ready") == model_state_t::ready);
    REQUIRE_THROWS_AS(to_model_state("wrong state"), bad_model_state_cast);

    REQUIRE(to_model_state(L"none") == model_state_t::none);
    REQUIRE(to_model_state(L"uninitialised") ==
        model_state_t::uninitialised);
    REQUIRE(to_model_state(L"ready") == model_state_t::ready);
    REQUIRE_THROWS_AS(to_model_state(L"wrong state"), bad_model_state_cast);

    // Conversion between model state enumerator and integer
    REQUIRE(to<int>(model_state_t::none) == 0);
    REQUIRE(to<int>(model_state_t::uninitialised) == 1);
    REQUIRE(to<int>(model_state_t::ready) == 2);

    REQUIRE(to_model_state(0) == model_state_t::none);
    REQUIRE(to_model_state(1) == model_state_t::uninitialised);
    REQUIRE(to_model_state(2) == model_state_t::ready);
    REQUIRE_THROWS_AS(to_model_state(3), bad_model_state_cast);

    // Note that in the above tests, invalid strings or integers are expected
    // to throw exceptions

}   // end test for casting model state

// Test basic instantiation of a model and its wrapper
TEST_CASE("model and wrapper life-cycle", "[unit][model]")
{

    using monitor = test_models::monitor;
    using null_model = test_models::null_model;
    using null_init_df = test_models::null_init_df;

    auto exchange = std::make_shared<test_models::is_exchange_t>();
    auto mntr = std::make_shared<test_models::monitor>();

    // Instantiate a Model Wrapper, with its Model and Initialisation Data
    // Factory. Can access its data, but it is uninitialised.
    qsim::model_wrapper null_mw(
        std::make_unique<null_model>(exchange, mntr)
        , std::make_unique<null_init_df>(1, "hello"));

    REQUIRE(null_mw.model_type_id() == 1);
    REQUIRE(null_mw.model_state() == qsim::model_state_t::uninitialised);
    REQUIRE(mntr->initialised_entity_count() == 0);
    REQUIRE(mntr->entity_is_initialised(1) == false);

    // Initialise the model - now it is in the ready state
    null_mw.init();
    REQUIRE(null_mw.model_state() == qsim::model_state_t::ready);    
    REQUIRE(null_mw.model_instance_id() == 1);
    REQUIRE(mntr->initialised_entity_count() == 1);
    REQUIRE(mntr->entity_is_initialised(1) == true);

    // TODO destruction

}   // end null_model_instantiation
