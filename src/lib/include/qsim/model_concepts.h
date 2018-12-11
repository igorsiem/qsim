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
concept bool HasModelTypeId()
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
concept bool HasModelInstanceId()
{
    return requires(T t)
    {
        { t.model_instance_id() } -> model_instance_id_t;
    };
}

/**
 * \brief Concept requiring a type to have a model state retrieval method
 *
 * \tparam T The constrained type
 */
template <typename T>
concept bool HasModelState()
{
    return requires(T t)
    {
        { t.model_state() } -> model_state_t;
    };
}

/**
 * \brief Concept requiring a type to declare a subtype for initialisation
 * data and an `init` method taking an instance of that sub-type
 *
 * \tparam The constrained type
 */
template <typename T>
concept bool IsInitialisable()
{
    return
        requires(T t) { typename T::init_data_t; }
        &&
        requires(T t, typename T::init_data_t d) { t.init(d); };
}

/**
 * \brief Constraints on a type so that it is usable as a Model class
 *
 * \tparam T The constrainted model type
 */
template <typename T>
concept bool IsModel()
{
    return
        std::is_destructible<T>::value
        && HasModelTypeId<T>()
        && HasModelInstanceId<T>()
        && HasModelState<T>()
        && IsInitialisable<T>()
        ;
}   // end IsModel concet

#endif  // QSIM_USE_CONCEPTS

}   // end qsim namespace

#endif // _qsim_model_concepts_h_included defined