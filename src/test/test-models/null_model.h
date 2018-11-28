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

#include <qsim/qsim.h>
#include <qlib/qlib.h>

#ifndef _test_models_null_model_included_h
#define _test_models_null_model_included_h

namespace test_models {

class null_model
{

    public:

    null_model(qsim::model_instance_id_t iid);
    static qsim::model_type_id_t model_type_id(void) { return 1; }
    
    qsim::model_instance_id_t model_instance_id(void) const
        { return m_instance_id; }

    protected:

    qsim::model_instance_id_t m_instance_id;

};  // end null_model class

}   // end test_models namespace

#endif
