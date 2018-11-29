/**
 * \file model_state.h
 * Enumerate and characterise the runtime state of a Model
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include  <typeinfo>
#include <qlib/qlib.h>
#include "error.h"

#ifndef _qsim_model_state_h_included
#define _qsim_model_state_h_included

namespace  qsim {

/**
 * \brief Enumerate the different states in which a model may be during
 * simulation run-time
 */
enum class model_state_t
{
    none = 0            ///< Unspecified state
    , uninitialised = 1 ///< Un-initialised - cannot be ticked yet
    , ready = 2         ///< Initialised - ready to be ticked
};  // end model_state enum

DECLARE_MESSAGE_ERROR_CLASS(
    bad_model_state_cast
    , std::bad_cast
    , "invalid cast of qSim model state enumerator")

template <typename TargetT>
TargetT to(model_state_t) = delete;

/**
 * \brief Convert a model state enumerator to a human-readable string
 *
 * \param ms The model state enumerator
 *
 * \return A human-readable string representation
 */
template <>
inline std::string to(model_state_t ms)
{
    switch (ms)
    {
        case model_state_t::none: return "none";
        case model_state_t::uninitialised: return "uninitialised";
        case model_state_t::ready:  return "ready";
        default: throw bad_model_state_cast();
    }
}   // end to function

/**
 * \brief Convert a model state enumerator to a human-readable wide-string
 *
 * \param ms The model state enumerator
 *
 * \return A human-readable wide-string representation
 */
template <>
inline std::wstring to(model_state_t ms)
    { return boost::lexical_cast<std::wstring>(to<std::string>(ms)); }

/**
 * \brief Convert a string to a model state enumerator
 *
 * \param str A string representation of the model state; see the
 * documentation for qsim::to<std::string>
 *
 * \return The model state string representation
 *
 * \throw bad_model_state_cast The string was not recognised as a model
 * state
 */
inline model_state_t to_model_state(const std::string& str)
{
    if (str == "none") return model_state_t::none;
    else if (str == "uninitialised") return model_state_t::uninitialised;
    else if (str == "ready") return model_state_t::ready;
    else throw bad_model_state_cast();
}

/**
 * \brief Convert a wide-string to a model state enumerator
 *
 * \param wstr A wide-string representation of the model state; see the
 * documentation for qsim::to<std::string>
 *
 * \return The model state string representation
 *
 * \throw bad_model_state_cast The string was not recognised as a model
 * state
 */
inline model_state_t to_model_state(const std::wstring& wstr)
{
    return to_model_state(boost::lexical_cast<std::string>(wstr));
}

/**
 * \brief Convert a model state enumerator to an integer value
 *
 * \param ms The model state enumerator
 *
 * \return The integer equivalent of `ms`
 */
template<>
inline int to(model_state_t ms)
{
    return static_cast<int>(ms);
}

/**
 * \brief Convert an integer to a model state enumerator (if the value is
 * in range)
 *
 * \param i The integer to convert
 *
 * \return The model state enumerator equivalent to `i`
 *
 * \throw bad_model_state_cast The value of `i` was not within the enumerator
 * range; see docs for qsim::model_state_t
 */
inline model_state_t to_model_state(int i)
{
    switch (i)
    {
        case 0: return model_state_t::none;
        case 1: return model_state_t::uninitialised;
        case 2: return model_state_t::ready;
        default: throw bad_model_state_cast();
    }
}   // end to_model_state

}   // end qsim namespace

#endif
