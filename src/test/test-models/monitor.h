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

    void signal_entity_ticked(qsim::model_instance_id_t eid)
    {
        qsim::write_lock lck(m_mtx);
        auto itr = m_entity_tick_count.find(eid);
        if (itr == m_entity_tick_count.end()) m_entity_tick_count[eid] = 1;
        else itr->second++;
    }

    std::size_t ticked_entity_count(void) const
    {
        qsim::read_lock lck(m_mtx);
        return m_entity_tick_count.size();
    }

    int entity_tick_count(qsim::model_instance_id_t eid)
    {
        qsim::read_lock lck(m_mtx);
        auto itr = m_entity_tick_count.find(eid);
        if (itr == m_entity_tick_count.end()) return 0;
        else return itr->second;
    }

    double latest_time_sec(void) const { return m_latest_time_sec.load(); }

    void set_latest_time_sec(double t) { m_latest_time_sec = t; }

    void clear(void)
    {
        qsim::write_lock lck(m_mtx);
        m_initialised_entity_ids.clear();
        m_entity_tick_count.clear();
        
        lck.unlock();

        m_latest_time_sec = -1.0;
    }

    private:

    mutable qsim::shared_mutex m_mtx;

    std::set<qsim::model_instance_id_t> m_initialised_entity_ids;

    std::map<qsim::model_instance_id_t, int>  m_entity_tick_count;

    std::atomic<double> m_latest_time_sec = -1.0;

};  // end monitor struct

using monitor_spr = std::shared_ptr<monitor>;

}   // end test_models method

#endif
