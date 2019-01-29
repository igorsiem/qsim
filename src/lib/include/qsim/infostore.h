/**
 * \file infostore.h
 * Definitions for storage of information exchanged between models
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <map>

#include <qlib/qlib.h>

#include "id.h"
#include "model_concepts.h"
#include "model_id.h"
#include "qsim_concepts.h"
#include "qsim_mutex.h"
#include "qsim_pointers.h"

#ifndef _qsim_infostore_h_included
#define _qsim_infostore_h_included

namespace qsim {

/**
 * \brief Store for information exchanged between models
 *
 * Infostore objects are collections of data that models exchange between
 * each other. They act as a decoupling, multiplexing and sharing mechanisms
 * for model information.
 *
 * Each Infostore holds two collections for a single type of information -
 * one for the current simulation time step, and one for the previous time
 * step. This 'double collection' is necessary to break circular
 * relationships in model dependency chains. Models add data to the current
 * collection, and query data from the current or previous collections.
 *
 * An Infostore object for a given type should be treated as a singleton.
 * Copy and move semantics are disabled.
 *
 * Operations on Infostore objects are thread-safe.
 *
 * \tparam InfoT The type of information managed by this Infostore; this
 * should be a type that can be used as a value in `std::vector`.
 */
template <typename InfoT>
class infostore
{

    public:

    DECLARE_NO_MOVE_AND_COPY_SEMANTICS(infostore)

    /**
     * \brief The information type handled by this Infostore
     */
    using info_t = InfoT;

    /**
     * \brief A vector of the information type
     */
    using info_vector = std::vector<info_t>;

    /**
     * \brief Trivial default constructor, initialising all attributes
     */
    infostore(void) :
        m_mtx()
        , m_current_data()
        , m_previous_data()
    {}

    /**
     * \brief Clear the previous data collection, then swap the current and
     * previous collections
     *
     * This method is typically called at the end of a time step. The effect
     * is that the previous collection contains what was the current data,
     * and the current collection is empty.
     */
    void swap_current_previous(void)
    {
        write_lock lck(m_mtx);
        m_previous_data.clear();
        std::swap(m_current_data, m_previous_data);
    }

    /**
     * \brief Add data from a given model
     *
     * This method appends data from a model to the infostore. If the
     * infostore alread has data from the model, it is appended.
     *
     * \param miid The ID of the model instance supplying the data
     *
     * \param data The vector of new data items from the model; note that
     * standard move semantics are used
     */
    void add(model_instance_id_t miid, info_vector data)
    {
        write_lock lck(m_mtx);

        // Note: this will instantiate a new info_vector if one does not
        // exist for the given model instance ID
        auto& model_data = m_current_data[miid];

        model_data.reserve(model_data.size() + data.size());
        std::move(data.begin(), data.end(), std::back_inserter(model_data));
    }   // end add method

    /**
     * \brief Retrieve data for the given model instance for the current
     * time step
     *
     * \param miid The model instance ID
     *
     * \return The vector of info objects produced by the model for the
     * current time step; this will be empty if the model has not produced
     * any data
     */
    info_vector current_data_from(model_instance_id_t miid)
    {
        read_lock lck(m_mtx);
        if (m_current_data.find(miid) == m_current_data.end())
            return info_vector();
        else return m_current_data[miid];
    }

    /**
     * \brief Retrieve data for the given model instance for the previous
     * time step
     *
     * \param miid The model instance ID
     *
     * \return The vector of info objects produced by the model for the
     * previous time step; this will be empty if the model has not produced
     * any data
     */
    info_vector previous_data_from(model_instance_id_t miid)
    {
        read_lock lck(m_mtx);
        if (m_previous_data.find(miid) == m_previous_data.end())
            return info_vector();
        else return m_previous_data[miid];
    }

    /**
     * \brief Clear all data from the infostore (both current and previous)
     */
    void clear(void)
    {
        write_lock lck(m_mtx);
        m_current_data.clear();
        m_previous_data.clear();
    }

    protected:

    /**
     * \brief A map of information vectors, indexed by the ID of the model
     * instance that generated the data
     */
    using model_info_map = std::map<model_instance_id_t, info_vector>;

    mutex m_mtx;    ///< Mutex for thread-safe access to internals

    /**
     * \brief Collection of model output from current time step
     */
    model_info_map m_current_data;

    /**
     * \brief Collection of model output from previous time step
     */
    model_info_map m_previous_data;

};  // end infostore class

}   // end qsim namespace

#endif  // _qsim_infostore_h_included defined
