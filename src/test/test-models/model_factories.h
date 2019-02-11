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

#include "exchange.h"
#include "null_model.h"
#include "time_model.h"

#ifndef _test_models_model_factory_h_included
#define _test_models_model_factory_h_included

using namespace fmt::literals;

namespace test_models {

// Model factory - generates a scenario with some null models
struct null_model_factory
{
    
    explicit null_model_factory(int nm) :
        m_number_of_models(nm)
        , mntr(std::make_shared<monitor>()) {}

    qsim::is_exchange_wrapper_spr populate(
            qsim::models_by_tick_group_index_map& mm)
    {

        // Create the InfoStore Exchange
        auto ise = std::make_shared<is_exchange_t>();

        // Create models with simple initialisation data, putting them all
        // in the same tick group.
        qsim::tick_group group;
        for (int i = 1; i <= m_number_of_models; i++)
            group.push_back(
                std::move(std::make_unique<qsim::model_wrapper>(
                    std::make_unique<null_model>(ise, mntr)
                    , std::make_unique<null_init_df>(
                        i
                        , "null model {}"_format(i)))));

        mm.emplace(0, std::move(group));

        // Put the Exchange in a Wrapper, and return the shared pointer of
        // the Wrapper
        return std::make_shared<qsim::is_exchange_wrapper>(ise);

    }   // end populate method

    int m_number_of_models;

    std::shared_ptr<monitor> mntr;

};  // end null_model_factory class

// Populates a sceneario with one of each type of model
struct one_of_each_model_factory
{
    
    one_of_each_model_factory(void) : mntr(std::make_shared<monitor>()) {}

    qsim::is_exchange_wrapper_spr populate(
            qsim::models_by_tick_group_index_map& mm)
    {

        // Create the InfoStore Exchange
        auto ise = std::make_shared<is_exchange_t>();

        // Time Model goes in Tick Group 0, with ID 1; Null Model into Tick
        // Group 1 with ID 2.
        mm[0].push_back(
            std::move(
                std::make_unique<qsim::model_wrapper>(
                    std::make_unique<time_model>(ise, mntr)
                    , std::make_unique<time_init_df>(1))));

        mm[1].push_back(
            std::move(
                std::make_unique<qsim::model_wrapper>(
                    std::make_unique<null_model>(ise, mntr)
                    , std::make_unique<null_init_df>(
                        2
                        , "null model 2"))));

        // Put the Exchange in a Wrapper, and return the shared pointer of
        // the Wrapper
        return std::make_shared<qsim::is_exchange_wrapper>(ise);

    }   // end populate method

    std::shared_ptr<monitor> mntr;

};  // end one_of_each_model_factory

}   // end test_models namespace

#endif
