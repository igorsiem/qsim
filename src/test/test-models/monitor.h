/**
 * \file monitor.h
 * A monitoring class for tracking various stats about test models, outside
 * of the standard qSim interface
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <set>
#include <qsim/qsim.h>

#ifndef _test_models_monitor_h_included
#define _test_models_monitor_h_included

namespace test_models {

// Class for monitoring stats about test models
class monitor final
{

    public:
    
    void signal_entity_initialised(qsim::model_instance_id_t eid)
    {
        qsim::write_lock lck(m_mtx);
        m_initialised_entity_ids.insert(eid);
    }    

    std::size_t initialised_entity_count(void) const
    {
        qsim::read_lock lck(m_mtx);
        return m_initialised_entity_ids.size();
    }

    bool entity_is_initialised(qsim::model_instance_id_t eid)
    {
        qsim::read_lock lck(m_mtx);
        return (m_initialised_entity_ids.find(eid) !=
            m_initialised_entity_ids.end());
    }

    void clear(void)
    {
        qsim::write_lock lck(m_mtx);
        m_initialised_entity_ids.clear();
    }

    private:

    mutable qsim::mutex m_mtx;

    std::set<qsim::model_instance_id_t> m_initialised_entity_ids;

};  // end monitor struct

}   // end test_models method

#endif
