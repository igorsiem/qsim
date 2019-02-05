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
#include <qlib/qlib.h>

#include "is_exchange.h"
#include "model.h"
#include "qsim_concepts.h"
#include "qsim_thread.h"

#ifndef _qsim_scenario_h_included
#define _qsim_scenario_h_included

namespace qsim {

#ifdef QSIM_USE_CONCEPTS

/**
 * \brief Concept for a type that can populate models into a model vector,
 * and return a (shared pointer to) a newly-created InfoStore Exchange
 * object.
 *
 * \tparam T The constrained type
 */
template <typename T>
concept bool can_populate_models()
{
    return requires(T t, model_vector& mv)
    {
        { t.populate(mv) } -> is_exchange_wrapper_spr;
    };
}

/**
 * \brief Concept for a type that implements a Model Factory interface
 *
 * Model Factories must implement a model-population method that returns
 * a corresponding InfoStore Exhchange Wrapper.
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
 * \page model_factory Model Factory
 *
 * The `is_model_factory` concept defines an object that is capable of
 * populating a collection of models, creating `model_wrapper` objects in
 * some implementation-defined way (e.g. loading entity definitions from a
 * file).
 *
 * Model Factories are passed to the `populate_from` method of the `scenario`
 * class to fill the Scenario with models. These can then be initialised
 * and run.
 *
 * Another task that the Model Factory must perform is to set up access for
 * models to the InfoStore Exchange. The Exchange object itself is
 * instantiated as a shared pointer to a tuple of InfoStores, and this is
 * made available to model objects as they are created.
 *
 * The shared pointer to the InfoStore Exchange object is passed to the
 * constructor of an `is_exchange_wrapper` object. This is a type erasure
 * class that allows the `scenario` class to address InfoStore Exchanges
 * with generic operations (like `clear`) without having to know the
 * specifics of the InfoStore types.
 */

/**
 * \brief A single scenario 'world' in a simulation
 *
 * A Scenario is a collection of models and other structures necessary for
 * running a simulation.
 *
 * Scenarios maintain their own mutex, and their operations are thread-safe.
 *
 * \todo Add a tick method for the scenario
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
    explicit scenario(std::shared_ptr<thread_pool> thread_pool) :
        m_mutex()
        , m_models()
        , m_is_exchange_wrp(nullptr)
        , m_thread_pool(thread_pool)
    {}

    DECLARE_DEFAULT_DESTRUCTOR(scenario)
    DECLARE_NO_COPY_SEMANTICS(scenario)
    DECLARE_DEFAULT_MOVE_SEMANTICS(scenario)

    /**
     * \brief Populate a scenario object from a Model Factory, and set up the
     * InfoStore Exchnage
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
        m_is_exchange_wrp = model_factory.populate(m_models);

    }   // end populate_from method

    /**
     * \brief Retrieve the size of the Models collection
     */
    std::size_t models_size(void) const
    {
        read_lock lck(m_mutex);
        return m_models.size();
    }   // end models_size method

    /**
     * \brief Initialise the scenario
     *
     * This method initialises all the models in the scenario, and clears
     * the InfoStore exchange.
     */
    void init(void)
    {
        std::vector<future<void> > results;

        write_lock lck(m_mutex);
        
        for (auto& model : m_models)
        {
            results.emplace_back(
                m_thread_pool->enqueue([&model](void)
                {
                    model->init();
                }));
        }

        // Wait for all the tasks to finish, and re-throw any exceptions in
        // the calling thread.
        boost::wait_for_all(results.begin(), results.end());
        for (auto& r : results) r.get();

        // Clear the InfoStore as well.
        m_is_exchange_wrp->clear(*m_thread_pool);
    }   // end init method

    protected:

    /**
     * \brief Mutex for the models collection
     *
     * Note that each model (wrapper) has its own mutex protected the
     * model instance - this mutex is for the collection object.
     */
    mutable shared_mutex m_mutex;

    /**
     * \brief The main models collection
     *
     * This is filled during the `populate` method.
     */
    model_vector m_models;

    /**
     * \brief The (wrapped) model exchange object
     *
     * This is set during the `populate` method. Note that the individual
     * InfoStores have their own mutexes, so the `m_mutex` of the `scenario`
     * object need not be locked for InfoStore operations.
     */
    is_exchange_wrapper_spr m_is_exchange_wrp;

    /**
     * \brief The thread-pool to use for parallel execution
     */
    std::shared_ptr<thread_pool> m_thread_pool;

};  // end scenario class

}   // end qsim namespace

#endif
