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
#include <string>
#include <type_traits>

#include <qlib/qlib.h>

#include "model_concepts.h"
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
     *
     * \return The type ID
     */
    virtual model_type_id_t model_type_id(void) const = 0;

    /**
     * \brief The instance ID of the underlying model
     *
     * \return The instance ID
     */
    virtual model_instance_id_t model_instance_id(void) const = 0;

    /**
     * \brief Retrieve the state of the underlying model
     *
     * \return The model state enumerator
     */
    virtual model_state_t model_state(void) const = 0;

};  // end class model_wrapper

QSIM_DECLARE_POINTERS_FOR(model_wrapper)

/**
 * \brief A wrapper for specific model type
 *
 * This is a proxy for Model classes conforming to the `IsModel` concept. It
 * is derived from the `model_wrapper` base class, and provides runtime
 * polymorphism for Model types without requiring them to be derived from a
 * common base class.
 *
 * \tparam ModelT The Model type
 *
 * \todo Methods for setting and deleting model instances
 */
template <QSIM_CONCEPT(is_model) ModelT>
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
     * \brief The initialisation data structure of the model type
     */
    using init_data_t = typename model_t::init_data_t;

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

    /**
     * \brief The type ID of the underlying model
     *
     * \return The ID of the model type
     *
     * \throw std::bad_optional_access There is no wrapped model object
     */
    virtual model_type_id_t model_type_id(void) const override
        { return model().model_type_id(); }

    /**
     * \brief The instance ID of the underlying model
     *
     * \return The ID of the model instance
     *
     * \throw std::bad_optional_access There is no wrapped model object
     */
    virtual model_instance_id_t model_instance_id(void) const override
        { return model().model_instance_id(); }

    /**
     * \brief Retrieve the state of the underlying model
     *
     * \return The model state enumerator
     *
     * \throw std::bad_optional_access There is no wrapped model object
     */
    virtual model_state_t model_state(void) const override
        { return model().model_state(); }

    /**
     * \brief Initialise the model
     *
     * \param data The initialisation data
     *
     * \throw std::bad_optional_access There is no wrapped model object
     */
    void init(init_data_t data) { model().init(std::move(data)); }

    protected:

    /**
     * \brief The optional underlying model instance
     */
    opt_model_t m_model_instance;

};  // end model_instance_wrapper class

}   // end qsim namespace

#endif
