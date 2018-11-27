/**
 * \file model.h
 * Basic definitions for the model concept
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <optional>
#include <qlib/qlib.h>

#include "qsim_concepts.h"
#include "qsim_pointers.h"

#ifndef _qsim_model_h_included
#define _qsim_model_h_included

namespace qsim {

/**
 * \brief A wrapper for a Model Instances
 *
 * All Model Instances are 'wrapped' by an instance of a template type
 * derived from this base type. Instances of `model_wrapper` are held in
 * containers for loop / block operations.
 */
class model_wrapper
{

    public:

    DECLARE_DEFAULT_VIRTUAL_LIFE_CYCLE(model_wrapper)

    /**
     * \brief The type ID of the underlying model
     */
    virtual model_type_id_t model_type_id(void) const = 0;

    /**
     * \brief The instance ID of the underlying model
     */
    virtual model_instance_id_t model_instance_id(void) const = 0;

};  // end class model_wrapper

QSIM_DECLARE_POINTERS_FOR(model_wrapper)

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
 * \brief Constraints on a type so that it is usable as a Model class
 *
 * \tparam T The constrainted model type
 */
template <typename T>
concept bool IsModel()
{
    return HasModelTypeId<T>() && HasModelInstanceId<T>();
}

#endif  // QSIM_USE_CONCEPTS

/**
 * \brief A wrapper for specific model type
 *
 * This is a proxy for Model classes conforming to the `IsModel` concept. It
 * is derived from the `model_wrapper` base class, and provides runtime
 * polymorphism for Model types without requiring them to be derived from a
 * common base class.
 *
 * \tparam ModelT The Model type
 */
template <QSIM_CONCEPT(IsModel, ModelT)>
class model_instance_wrapper : public model_wrapper
{

    public:

    /**
     * \brief The type of the model
     */
    using model_t = ModelT;

    /**
     * \brief An optional instance of the model type
     */
    using opt_model_t = std::optional<model_t>;

    /**
     * \brief Initialises model wrapper with an optional instance of its
     * model
     *
     * \param model_instance The optional model instance
     */
    model_instance_wrapper(opt_model_t model_instance = std::nullopt) :
        model_wrapper()
        , m_model_instance(model_instance)
    {}

    DECLARE_DEFAULT_VIRTUAL_DESTRUCTOR(model_instance_wrapper)

    /**
     * \brief Determine whether the Wrapper has a Model object
     *
     * \return `true` if the Wrapper has a model
     */
    bool has_model(void) const { return m_model_instance.has_value(); }

    /**
     * \brief Access to the wrapped model
     *
     * \return A reference to the wrapped model object
     *
     * \throw std::bad_optional_access There is no wrapped model object
     */
    model_t& model(void) { return m_model_instance.value(); }

    /**
     * \brief Const access to the wrapped model
     *
     * \return A const reference to the wrapped model object
     *
     * \throw std::bad_optional_access There is no wrapped model object
     */
    const model_t& model(void) const { return m_model_instance.value(); }

    protected:

    /**
     * \brief The optional underlying model instance
     */
    opt_model_t m_model_instance;

};  // end model_instance_wrapper class

}   // end qsim namespace

#endif
