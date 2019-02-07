/**
 * \file time_model.h
 * Declares the time model
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <qsim/qsim.h>
#include <qlib/qlib.h>

#include "monitor.h"
#include "exchange.h"

#ifndef _test_models_time_model_included_h
#define _test_models_time_model_included_h

namespace test_models {

// Data factory for initialising the time model - in this case, starting
// time is always initialised to zero (so the model can do that for itself,
// so all we need for initialisation data is the model instance (entity) ID.
struct time_init_df
{

    struct data_t
    {
        qsim::model_instance_id_t instance_id;
    };

    // Constructor - initialise the entity ID
    explicit time_init_df(qsim::model_instance_id_t eid) :
        init_data({ eid }) {}

    data_t get(void) const { return init_data; }

    data_t init_data;

};  // end time_init_df

class time_model
{

    public:

    time_model(is_exchange_spr exchange, monitor_spr monitor) :
        m_instance_id(0)
        , m_exchange(exchange)
        , m_monitor(monitor)
    {}

    static qsim::model_type_id_t model_type_id(void) { return 2; }

    qsim::model_instance_id_t model_instance_id(void) const
        { return m_instance_id; }

    using init_data_t = time_init_df::data_t;

    // Initialise entity ID and reset time
    void init(init_data_t i)
    {
        m_instance_id = i.instance_id;
        m_monitor->signal_entity_initialised(m_instance_id);
    }

    // Tick - increment time and output
    void tick(qsim::tick_count_t tc)
    {
        // Get out the time infostore, and add our output to it
        auto& time_is = qsim::get_infostore<tick_time>(*m_exchange);
        time_is.add(
            m_instance_id
            , std::vector<tick_time>{ tick_time{ tc, tc * 1.0 } });
            // TODO support increment other than 1 second
    }   // end tick methid

    protected:

    qsim::model_instance_id_t m_instance_id;

    is_exchange_spr m_exchange;

    monitor_spr m_monitor;

};  // end time_model class

}   // end test_models namespace

#endif
