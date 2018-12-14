/**
 * \file is_exchange.h
 * Declare the `is_exchange` type
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include "infostore.h"

#ifndef _qsim_is_exchange_h_included
#define _qsim_is_exchange_h_included

namespace qsim {

/**
 * \brief A tuple of Infostores
 *
 * This type is generated based on a parameter pack of the information types
 * handled by the Infostores. An instance of the type is intended as the
 * central 'exchange' of data between models in a simulation.
 *
 * \tparam InfoTs A parameter pack of the information types handled by the
 * Infostores; these must be unique types
 */
template <typename... InfoTs>
using is_exchange = std::tuple<infostore<InfoTs>...>;

/**
 * \brief Retrieve a reference to the Infostore for a particular type of
 * object from an IS Exchange tuple
 *
 * Note that this method relies on the `InfoTs` collection of the IS
 * Exchnage having no duplicate types.
 *
 * \tparam InfoT The information type of the Infostore object to be
 * retrieved; must be a member of the collection of `InfoTs`
 * 
 * \tparam The collection of information types for the IS exchange tuple;
 * must include `InfoT`
 *
 * \param ise The Infostore Exchange object
 *
 * \return A reference to the InfoStore for the given type
 */
template <typename InfoT, typename... InfoTs>
infostore<InfoT>& get_infostore(is_exchange<InfoTs...>& ise)
{
    return std::get<infostore<InfoT> >(ise);
}

/**
 * \brief Retrieve a const reference to the Infostore for a particular type
 * of object from an IS Exchange tuple
 *
 * Note that this method relies on the `InfoTs` collection of the IS
 * Exchnage having no duplicate types.
 *
 * \tparam InfoT The information type of the Infostore object to be
 * retrieved; must be a member of the collection of `InfoTs`
 * 
 * \tparam The (const) collection of information types for the IS exchange
 * tuple; must include `InfoT`
 *
 * \param ise The Infostore Exchange object
 *
 * \return A const reference to the InfoStore for the given type
 */
template <typename InfoT, typename... InfoTs>
const infostore<InfoT>& get_infostore(const is_exchange<InfoTs...>& ise)
{
    return std::get<infostore<InfoT> >(ise);
}

}   // end qsim namespace

#endif
