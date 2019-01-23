/**
 * \file scenario.h
 * Scenario type, as a tickable collection of models
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <functional>
#include "model.h"
#include "qsim_concepts.h"
#include "qsim_mutex.h"

#ifndef _qsim_scenario_h_included
#define _qsim_scenario_h_included

namespace qsim {

#ifdef QSIM_USE_CONCEPTS

/**
 * \brief Concept for a type that can populate models into a model vector
 *
 * \tparam T The constrained type
 */
template <typename T>
concept bool can_populate_models()
{
    return requires(T t, model_vector& mv)
    {
        { t.populate(mv) };
    };

}

/**
 * \brief Concept for a type that implements a Model Factory interface
 *
 * \tparam T The constrained type
 */
template <typename T>
concept bool is_model_factory()
{
    return can_populate_models<T>();
}

#endif

/**
 * \brief A single scenario 'world' in a simulation
 *
 * A Scenario is a collection of models and other structures necessary for
 * running a simulation.
 *
 * Scenarios maintain their own mutex, and their operations are thread-safe.
 */
class scenario
{

    public:

    /**
     * \brief Trivial constructor
     *
     * Scenario objects must be populated with models before they can be
     * initialised and run.
     */
    scenario(void) : m_mutex(), m_models() {}

    DECLARE_DEFAULT_DESTRUCTOR(scenario)
    DECLARE_NO_COPY_SEMANTICS(scenario)
    DECLARE_DEFAULT_MOVE_SEMANTICS(scenario)

    /**
     * \brief Populate a scenario object from a Model Factory
     *
     * Note that the internal collection of models is cleared by this method
     * before calling the `populate` method of the Model Factory.
     *
     * \tparam ModelFactory The Model Factory type; must conform to the
     * `is_model_factory` concept
     *
     * \param model_factory The Model Factory object
     */
    template <QSIM_CONCEPT(is_model_factory) ModelFactoryT>
    void populate_from(ModelFactoryT& model_factory)
    {

        write_lock lck(m_mutex);

        m_models.clear();
        model_factory.populate(m_models);

    }   // end populate_from method

    /**
     * \brief Retrieve the size of the Models collection
     */
    std::size_t models_size(void) const
    {
        read_lock lck(m_mutex);
        return m_models.size();
    }   // end models_size method

    protected:

    /**
     * \brief Mutex for the models collection
     *
     * Note that each model (wrapper) has its own mutex protected the
     * model instance - this mutex is for the collection object.
     */
    mutable mutex m_mutex;

    /**
     * \brief The main models collection
     */
    model_vector m_models;

};  // end scenario class

}   // end qsim namespace

#endif
