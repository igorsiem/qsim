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
#include "qsim_thread.h"

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

/// \cond Execute `clear` operation over tuple of InfoStores
template <typename ISExchangeT, std::size_t... Indices>
std::array<int, std::tuple_size<ISExchangeT>::value> clear(
        ISExchangeT& is_exchange
        , std::index_sequence<Indices...>)
{
    return std::array<int, std::tuple_size<ISExchangeT>::value>
    {
        (std::get<Indices>(is_exchange).clear(), 0)...
    };
}   // end clear method
/// \endcond

/**
 * \brief Clear all the InfoStores in an Exchange
 *
 * \tparam ISExchangeT An `is_exchange` type (tuple of InfoStores)
 *
 * \param is_exchange The IS exchange object
 *
 * \todo Implement paralellised version of this method
 */
template <typename ISExchangeT>
void clear(ISExchangeT& is_exchange)
{
    clear(
        is_exchange
        , std::make_index_sequence<std::tuple_size<ISExchangeT>::value>());
}   // end clear method

// \cond Execute `clear` operation over tuple of InfoStores, using a thread
// pool, and the indices trick
template <typename InfoStoreT>
future<void> clear_is(InfoStoreT& is, thread_pool& tp)
{
    return tp.enqueue([&is](void) { is.clear(); });
}

template <typename ISExchangeT, std::size_t... Indices>
std::array<future<void>, std::tuple_size<ISExchangeT>::value>
clear(
        ISExchangeT& is_exchange
        , thread_pool& tp
        , std::index_sequence<Indices...>)
{
    return std::array<future<void>, std::tuple_size<ISExchangeT>::value>
        { clear_is(std::get<Indices>(is_exchange), tp)... };

}   // end clear method
// \endcond

/**
 * \brief Execute the 'clear' operation over an ISExchange (tuple of
 * InfoStores)
 *
 * \tparam ISExchangeT The IS Exchange - a tuple of InfoStores
 *
 * \param is_exchange The IS Exchange object
 *
 * \param tp The thread pool to use
 */
template <typename ISExchangeT>
void clear(ISExchangeT& is_exchange, thread_pool& tp)
{

    // Execute the clear operation over the tuple, using the thread pool, and
    // receiving an array of futures for the individual clear operations in
    // return.
    auto futures = std::move(clear(
        is_exchange
        , tp
        , std::make_index_sequence<std::tuple_size<ISExchangeT>::value>()));

    // Wait for all the tasks to complete, and then do a 'get' on each future
    // to re-throw any exceptions.
    boost::wait_for_all(futures.begin(), futures.end());
    for (auto& f : futures) f.get();
}   // end clear method

// \cond Execute `swap_current_previous` operation over tuple of InfoStores,
// using a thread pool, and the indices trick
template <typename InfoStoreT>
future<void> swap_current_previous_is(InfoStoreT& is, thread_pool& tp)
{
    return tp.enqueue([&is](void) { is.swap_current_previous(); });
}

template <typename ISExchangeT, std::size_t... Indices>
std::array<future<void>, std::tuple_size<ISExchangeT>::value>
swap_current_previous(
        ISExchangeT& is_exchange
        , thread_pool& tp
        , std::index_sequence<Indices...>)
{
    return std::array<future<void>, std::tuple_size<ISExchangeT>::value>
        { swap_current_previous_is(std::get<Indices>(is_exchange), tp)... };

}   // end swap_current_previous method
// \endcond

/**
 * \brief Execute the `swap_current_previous` operation over an ISExchange
 * (tuple of InfoStores)
 *
 * This method uses the given thread pool to execute the operation in
 * parallel, and blocks until they are all complete.
 *
 * \tparam ISExchangeT The IS Exchange - a tuple of InfoStores
 *
 * \param is_exchange The IS Exchange object
 *
 * \param tp The thread pool to use
 */
template <typename ISExchangeT>
void swap_current_previous(ISExchangeT& is_exchange, thread_pool& tp)
{
    // Execute the swap_current_previous operation over the tuple, using the
    // thread pool, and receiving an array of futures for the individual
    // operations in return.
    auto futures =
        std::move(
            swap_current_previous(
                is_exchange
                , tp
                , std::make_index_sequence<
                    std::tuple_size<ISExchangeT>::value>()));

    // Wait for all the tasks to complete, and then do a 'get' on each future
    // to re-throw any exceptions.
    boost::wait_for_all(futures.begin(), futures.end());
    for (auto& f : futures) f.get();
}   // end clear method

}   // end qsim namespace

#endif
