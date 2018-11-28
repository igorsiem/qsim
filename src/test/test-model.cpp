/**
 * \file test-model.cpp
 * Test for the the basic model concept and framework
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

// Test basic instantiation of a model and its wrapper
TEST_CASE("model and wrapper instantiation", "[unit][model]")
{

    using null_model = test_models::null_model;
    using null_model_wrapper =
        qsim::model_instance_wrapper<test_models::null_model>;

    // Null model wrapper with no model - attempt to access model information
    // fails
    null_model_wrapper no_model_mw;
    REQUIRE_THROWS_AS(no_model_mw.model_type_id(), std::bad_optional_access);
    REQUIRE_THROWS_AS(
        no_model_mw.model_instance_id(), std::bad_optional_access);

    // Instantiante a model wrapper with a proper model - can access its
    // info
    null_model_wrapper null_mw{ std::make_optional<null_model>(2) };
    REQUIRE(null_mw.model_type_id() == 1);
    REQUIRE(null_mw.model_instance_id() == 2);

}   // end null_model_instantiation
