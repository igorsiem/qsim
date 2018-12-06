/**
 * \file null_model.h
 * Declares the `null_model` class - a 'do nothing' model for testing
 * architectures
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include "null_model.h"

namespace test_models {

null_model::null_model(qsim::model_instance_id_t iid) :
    m_instance_id(iid)
    , m_model_state(qsim::model_state_t::none)
    , m_internal_state()
{}

}   // end test_models namespace
