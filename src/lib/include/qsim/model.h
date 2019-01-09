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

    /**
     * \brief Constructor, initialising the model state
     *
     * \param ms The model state to set
     */
    explicit model_wrapper(model_state_t ms) : m_model_state(ms) {}

    DECLARE_DEFAULT_DESTRUCTOR(model_wrapper)

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
    virtual model_state_t model_state(void) const { return m_model_state; }

    protected:

    virtual void set_model_state(model_state_t ms) { m_model_state = ms; }

    model_state_t m_model_state;

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
     * \brief The initialisation data structure of the model type
     */
    using init_data_t = typename model_t::init_data_t;

    /**
     * \brief Initialise the model wrapper, setting the model state to
     * `uninitialised`
     */
    model_instance_wrapper(void) :
        model_wrapper(model_state_t::uninitialised)
        , m_model_instance()
    {}

    DECLARE_DEFAULT_VIRTUAL_DESTRUCTOR(model_instance_wrapper)

    /**
     * \brief Access to the wrapped model
     *
     * \return A reference to the wrapped model object
     */
    model_t& model(void) { return m_model_instance; }

    /**
     * \brief Const access to the wrapped model
     *
     * \return A const reference to the wrapped model object
     */
    const model_t& model(void) const { return m_model_instance; }

    /**
     * \brief The type ID of the underlying model
     *
     * \return The ID of the model type
     */
    virtual model_type_id_t model_type_id(void) const override
        { return model_t::model_type_id(); }

    /**
     * \brief The instance ID of the underlying model
     *
     * \return The ID of the model instance
     */
    virtual model_instance_id_t model_instance_id(void) const override
        { return m_model_instance.model_instance_id(); }

    /**
     * \brief Initialise the model
     *
     * Calls the underlying model's `init` method, and sets the model state
     * `ready`.
     *
     * \param data The initialisation data
     */
    void init(init_data_t data)
    {
        model().init(std::move(data));
        set_model_state(model_state_t::ready);
    }

    protected:

    /**
     * \brief The underlying model instance
     */
    model_t m_model_instance;

};  // end model_instance_wrapper class

}   // end qsim namespace

#endif
