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

#include <string>

#include <qsim/qsim.h>
#include <qlib/qlib.h>

#include "monitor.h"
#include "exchange.h"

#ifndef _test_models_null_model_included_h
#define _test_models_null_model_included_h

namespace test_models {

struct null_init_df
{

    struct data_t
    {
        qsim::model_instance_id_t id = 1;
        std::string internal_state;
    };

    data_t m_data;

    null_init_df(qsim::model_instance_id_t id, std::string is) :
        m_data{id, is} {}

    data_t get(void) const { return m_data; }
};

// Example of model class that does absolutely nothing
class null_model
{

    public:

    explicit null_model(std::shared_ptr<monitor> mtr) :
        m_instance_id(0)
        , m_internal_state()
        , m_monitor(mtr)
    {}

    static qsim::model_type_id_t model_type_id(void) { return 1; }
    
    qsim::model_instance_id_t model_instance_id(void) const
        { return m_instance_id; }

    using internal_state_t = std::string;

    using init_data_t = null_init_df::data_t;

    void init(init_data_t i);

    void tick(void);

    internal_state_t internal_state(void) const { return m_internal_state; }

    protected:

    qsim::model_instance_id_t m_instance_id;

    internal_state_t m_internal_state;

    std::shared_ptr<monitor> m_monitor;

};  // end null_model class

}   // end test_models namespace

#endif
