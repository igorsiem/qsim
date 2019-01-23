/**
 * \file model_factory.h
 * Declares a simple factory for test models to populate a collection of
 * model objects.
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
#include "null_model.h"

#ifndef _test_models_model_factory_included_h
#define _test_models_model_factory_included_h

using namespace fmt::literals;

namespace test_models {

// Model factory - generates a scenario with some null models
class model_factory
{
    
    public:

    explicit model_factory(int nm) : m_number_of_models(nm) {}

    void populate(qsim::model_vector& mc)
    {

        // Create models with simple initialisation data
        for (int i = 1; i <= m_number_of_models; i++)
            mc.push_back(
                std::move(std::make_unique<qsim::model_wrapper>(
                    std::make_unique<null_model>()
                    , std::make_unique<null_init_df>(
                        i
                        , "null model {}"_format(i)))));

    }   // end populate method

    int m_number_of_models;

};  // end model factory class

}   // end test_models namespace

#endif
