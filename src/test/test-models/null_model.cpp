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

void null_model::init(null_model::init_data_t i)
{
    m_instance_id = i.id;
    m_internal_state = i.internal_state;
    m_monitor->signal_entity_initialised(m_instance_id);
}

void null_model::tick(qsim::tick_count_t)
{
    m_monitor->signal_entity_ticked(m_instance_id);

    // TODO do something with the info from the ISE
}   // end tick method

}   // end test_models namespace
