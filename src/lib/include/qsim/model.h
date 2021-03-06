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

#include <map>
#include <optional>
#include <string>
#include <type_traits>

#include <qlib/qlib.h>

#include "data_factory.h"
#include "model_concepts.h"
#include "qsim_pointers.h"
#include "qsim_thread.h"

#ifndef _qsim_model_h_included
#define _qsim_model_h_included

namespace qsim {

/**
 * \brief A wrapper class for different types of model
 *
 * This class uses the type erasure pattern to provide a generic interface
 * to model operations. It also implements thread-safety, so that the model
 * itself need not do so.
 */
class model_wrapper
{

    /**
     * \brief Internal type-erasure base-class
     */
    struct mw_te_base
    {
        DECLARE_DEFAULT_DESTRUCTOR(mw_te_base)

        /**
         * \brief Initialise the underlying model
         *
         * \param data The initialisation data
         */
        virtual void init(void) = 0;

        /**
         * \brief The type ID of the underlying model
         *
         * \return The ID of the model type
         */
        virtual model_type_id_t model_type_id(void) const = 0;

        /**
         * \brief The instance ID of the underlying model
         *
         * \return The ID of the model instance
         */
        virtual model_instance_id_t model_instance_id(void) const = 0;

        /**
         * \brief Tick the underlying model
         *
         * \param tc The zero-based index of the tick (time step)
         */
        virtual void tick(tick_count_t tc) = 0;

    };  // end mw_te_base struct

    /**
     * \brief Internal type-erasure implementation
     *
     * \tparam ModelT The wrapper model class
     *
     * \tparam InitDataFactory The Data Factory type that generates
     * initialisation data for the model
     */
    template <
        QSIM_CONCEPT(is_model) ModelT
        , QSIM_CONCEPT(is_data_factory) InitDataFactoryT>
    struct mw_te_impl : public mw_te_base
    {

        public:

        /**
         * \brief The underlying model type
         */
        using model_t = ModelT;

        /**
         * \brief A unique pointer to the model type
         */
        using model_upr = std::unique_ptr<model_t>;

        /**
         * \brief The type with which the model is initialised
         */
        using init_data_t = typename model_t::init_data_t;

        /**
         * \brief The data factory type used for generating initialisation
         * data
         */
        using init_data_factory_t = InitDataFactoryT;

        /**
         * \brief A unique pointer to the data factory type
         */
        using init_data_factory_upr = std::unique_ptr<init_data_factory_t>;

        // Ensure that the initialisation data factory yields the same type
        // as that required to initialise the model.
        static_assert(
            std::is_same<
                init_data_t
                , typename init_data_factory_t::data_t>::value
            , "model initialisation type must be the same as the data type "
                "of its initialisation factory");

        /**
         * \brief Construct the internal implementation object
         *
         * \param model A unique pointer to the model object
         *
         * \param A unique pointer to the Data Factory used to initialise
         * the model
         */
        explicit mw_te_impl(
                model_upr&& model
                , init_data_factory_upr&& init_df) :
            mw_te_base()
            , m_model(std::move(model))
            , m_init_df(std::move(init_df))
        {}

        DECLARE_DEFAULT_VIRTUAL_DESTRUCTOR(mw_te_impl)
        DECLARE_NO_COPY_SEMANTICS(mw_te_impl)
        DECLARE_DEFAULT_MOVE_SEMANTICS(mw_te_impl)

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
            { return m_model->model_instance_id(); }

        /**
         * \brief The underlying model instance
         */
        model_upr m_model;

        /**
         * \brief The initialisation data factory for this model
         */
        init_data_factory_upr m_init_df;

        /**
         * \brief Initialise the underlying model from the data factory
         */
        virtual void init(void) override
            { m_model->init(std::move(m_init_df->get())); }

        /**
         * \brief Tick the underlying model
         *
         * \param tc The zero-based index of the tick (time step)
         */
        virtual void tick(tick_count_t tc) override
            { m_model->tick(tc); }
    
    };  // end mw_te_impl struct

    public:

    /**
     * \brief Create a model wrapper object
     *
     * \tparam ModelT The wrapper model type
     *
     * \tparam InitDataFactoryT The Data Factory type that generates
     * initialisation data for the model
     *
     * \param model A unique pointer to the uninitialised Model
     *
     * \param init_df A unique pointer to the Data Factory that generates
     * initialisation data for the Model 
     */
    template <
        QSIM_CONCEPT(is_model) ModelT
        , QSIM_CONCEPT(is_data_factory) InitDataFactoryT>
    model_wrapper(
            std::unique_ptr<ModelT>&& model
            , std::unique_ptr<InitDataFactoryT>&& init_df) :
        m_mutex()
        , m_wrapped_model(
            std::make_unique<
                mw_te_impl<
                    ModelT
                    , InitDataFactoryT> >(
                        std::move(model)
                        , std::move(init_df)))
        , m_model_state(model_state_t::uninitialised)
    {}

    DECLARE_DEFAULT_DESTRUCTOR(model_wrapper)
    DECLARE_NO_COPY_SEMANTICS(model_wrapper)
    DECLARE_DEFAULT_MOVE_SEMANTICS(model_wrapper)

    /**
     * \brief The type ID of the underlying Model
     *
     * \return The type ID
     */
    model_type_id_t model_type_id(void) const
        { return m_wrapped_model->model_type_id(); }

    /**
     * \brief The instance ID of the underlying Model
     *
     * \return The instance ID
     */
    model_instance_id_t model_instance_id(void) const
    {
        read_lock lck(m_mutex);
        return m_wrapped_model->model_instance_id();
    }

    /**
     * \brief Retrieve the state of the Model
     *
     * \return The model state enumerator
     */
    model_state_t model_state(void) const
    {
        read_lock lck(m_mutex);
        return m_model_state;
    }

    /**
     * \brief Initialise the model, ready for simulation
     *
     * After successful initialisation, the Model State is set to `ready`.
     */
    virtual void init(void)
    {
        write_lock lck(m_mutex);

        m_wrapped_model->init();
        m_model_state = model_state_t::ready;
    }   // end init method

    /**
     * \brief Tick the underlying model
     *
     * \param tc The zero-based index of the tick (time step)
     */
    void tick(tick_count_t tc)
    {
        write_lock lck(m_mutex);
        m_wrapped_model->tick(tc);        
    }   // end tick method

    protected:

    /**
     * \brief A mutex object protecting access to the wrapper model and the
     * state enumerator
     */
    mutable shared_mutex m_mutex;

    /**
     * \brief The instance of the concept implementation class
     */
    std::unique_ptr<mw_te_base> m_wrapped_model;

    /**
     * \brief The current state of the Model
     */
    model_state_t m_model_state;

};  // end class model_wrapper

QSIM_DECLARE_UNIQUE_POINTERS_FOR(model_wrapper)

/**
 * \page tick_group Tick Group
 *
 * Model Instances (Entities) in a Scenario are segmented into Tick Groups.
 * A single tick group contains model instances that may be ticked in
 * parallel (i.e. have no direct dependence on each other's data).
 *
 * The Tick Group index is a simple signed integer. Tick Groups are ticked
 * in strict order, so that ticking for all the Entities in Group *n* is
 * complete before ticking for Entities in Group *n+1* commences.
 *
 * The \ref model_factory for a Scenario is responsible for assigning Models
 * to Tick Groups. If Model 'B' relies on the output of model 'A', then 'B'
 * should be assigned a higher Tick Group index. Then 'A' will have placed
 * its output in the InfoStore Exchange that may then be accessed by 'B'.
 *
 * Tick Groups may be assigned to individual Model Instances, but they are
 * most often assigned to Model Types. For example, a radar sensor model
 * would generally need to know the positions of all platform models, so
 * the entire class of sensor models would generally be assigned to a Tick
 * Group with a higher index than that containing the platform models.
 *
 * Circular depencies may be broken by having one Entity or one class of
 * Entities in the circular dependency access the output they require from
 * the *previous* time step, rather than the current time step. This is the
 * reason that InfoStore objects retain this data.
 *
 * See the \ref infostore page for more information.
 */

/**
 * \brief An index for the \ref tick_group of a model
 */
using tick_group_index_t = int;

/**
 * \brief A collection of models that may be ticked in parallel
 */
using tick_group = std::vector<model_wrapper_upr>;

/**
 * \brief A map of tick groups (vectors of models), indexed by tick group
 * index
 */
using models_by_tick_group_index_map =
    std::map<tick_group_index_t, tick_group>;

}   // end qsim namespace

#endif
