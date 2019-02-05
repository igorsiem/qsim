/**
 * \file model_concepts.h
 * Concept definitions for model classes
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include "is_exchange.h"
#include "model_id.h"
#include "model_state.h"
#include "qsim_concepts.h"

#ifndef _qsim_model_concepts_h_included
#define _qsim_model_concepts_h_included

namespace qsim {

#ifdef QSIM_USE_CONCEPTS

/**
 * \brief Concept requiring a type to have a `model_type_id` static method
 *
 * \tparam T The constrained type
 */
template <typename T>
concept bool has_model_type_id()
{
    return requires(T t)
    {
        { T::model_type_id() } -> model_type_id_t;
    };
};

/**
 * \brief Concept requiring a type to have a `model_instance_id` method
 *
 * \tparam T The constrained type
 */
template <typename T>
concept bool has_model_instance_id()
{
    return requires(T t)
    {
        { t.model_instance_id() } -> model_instance_id_t;
    };
}

/**
 * \brief Concept requiring a type to declare a subtype for initialisation
 * data and an `init` method taking an instance of that sub-type
 *
 * \tparam The constrained type
 */
template <typename T>
concept bool is_initialisable()
{
    return
        requires(T) { typename T::init_data_t; }
        &&
        requires(T t, typename T::init_data_t d) { t.init(d); };
}

/**
 * \brief Concept requiring a type to have a `tick` method
 *
 * \tparam T The constrained type
 */
template <typename T>
concept bool is_tickable()
{
    return requires(T t) { t.tick(); };
}

/**
 * \brief Constraints on a type so that it is usable as a Model class
 *
 * Constraints for the model concept are:
 *
 * * Destructible
 *
 * * Has a static method for retrieving the model type ID
 *
 * * Has a method for retrieving the model instance (entity) ID
 *
 * * Is initialisable - has a sub-type called `init_data_t`, and an `init`
 *   method that initialises the model object (entity) with an instance of
 *   that sub-type
 *
 * * Is tickable - has a `tick` method for updating state
 *
 * Note that the constructor of a model type should take a shared pointer to
 * the tuple of InfoStore types used in the simulation, to perform its input
 * and output, but this process is mediated by the \ref model_factory type.
 *
 * \tparam ModelT The constrainted model type
 */
template <typename ModelT>
concept bool is_model()
{
    return
        std::is_destructible<ModelT>::value
        && has_model_type_id<ModelT>()
        && has_model_instance_id<ModelT>()
        && is_initialisable<ModelT>()
        && is_tickable<ModelT>()
        ;
}   // end is_model concept

#endif  // QSIM_USE_CONCEPTS

}   // end qsim namespace

#endif // _qsim_model_concepts_h_included defined

/**
 * \page model_object_life_cycle Model Object (Entity) Life-cycle
 *
 * qSim models have a distinct and carefully managed life-cycle that is
 * intended to optimise resource and computing efficiency while placing as
 * few constraints as possible on model implementations. Model objects may be
 * of any class conforming to the concepts defined in the `model_concepts.h`
 * file, and are intended to encapsulate entities in the simulation.
 *
 * Specifically, model objects have the following life-cycle:
 *
 * 1. *Construction* -- Model object construction is very simple because a
 *    separate initialisation phase also takes place before a simulation
 *    commences. Models must be default-constructible, and are generally
 *    constructed for a Scenario using a Model Factory (see the page entitled
 *    \ref model_factory).
 *
 * 2. *Initialisation* -- Model objects are initialised with an arbitary
 *    data structure prior to the beginning of a simulation. The constraints
 *    on initialisation are as follows:
 *
 *    a. Model objects must be capable of being initialised repeatedly, with
 *       consistent results.
 *
 *    b. Initialisation must include setting the instance ID to a unique
 *       identifier; repeated initialisations must set the instance ID to the
 *       same value every time (this implies that initialisation data
 *       includes the instance ID, and be supplied to the initialisation
 *       method with the same ID every time).
 *
 *    c. The model must be ready to be 'ticked' after a successful
 *       initialisation.
 *
 *    d. Models may signal initialisation failure with an exception.
 *
 * 3. *Ticking* -- Models are repeatedly 'ticked' as the simulation
 *    progresses. In each tick, the model:
 *
 *    a. Take its input from infostore objects
 *
 *    b. Update its internal state
 *
 *    c. Send its output to infostore objects
 *
 * 4. *Re-initialisation* -- This is the same as initialisation, and makes
 *    the model ready to repeat the simulation
 *
 * 5. *Destruction* -- All resources released
 */
