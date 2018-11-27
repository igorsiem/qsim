/**
 * \file qsim_pointers.h
 * Some convenience macros for pointer types
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <memory>

#ifndef _qsim_qsim_pointers_h_included
#define _qsim_qsim_pointers_h_included

/**
 * \brief Declare smart pointer types for a give type
 *
 * This method declaes shared and unique pointers to instances and const
 * instances of a given type name.
 *
 * \param name The type name for which corresponding pointer types are to be
 * declared
 */
#define QSIM_DECLARE_POINTERS_FOR( name ) \
    using name##_spr = std::shared_ptr<name>; \
    using const_##name##_spr = std::shared_ptr<const name>; \
    using name##_upr = std::unique_ptr<name>; \
    using const_##name##_upr = std::unique_ptr<const name>;

#endif
