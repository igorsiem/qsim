/**
 * \file data_factory.h
 * Concept definitions for Data Factory classes
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <optional>
#include "qsim_concepts.h"

#ifndef _qsim_data_factory_h_included
#define _qsim_data_factory_h_included

namespace qsim {

#ifdef QSIM_USE_CONCEPTS

/**
 * \brief Concept requiring a type to declare a `data_t` subtype, and a
 * method for retrieving optional instances of that type
 *
 * \tparam T The constrained type
 */
template <typename T>
concept bool can_get_data()
{
    return
        requires(T) { typename T::data_t; }
        && requires(T t)
        {
            { t.get() } -> std::optional<typename T::data_t>;
        };
}

/**
 * \brief A data factory is a very simply source of a sequence of optional
 * instances of a piece of data
 *
 * In some ways, this concept is similar to an Input Iterator, in that a
 * sequence of values is generated, but there is no comparison or
 * dereferencing - just a generated sequence.
 *
 * \tparam T The constrained type
 */
template <typename T>
concept bool is_data_factory() { return can_get_data<T>(); }

#endif  // QSIM_USE_CONCEPTS

}   // end qsim namespace

#endif
