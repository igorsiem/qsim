/**
 * \file id.h
 * Define basic identifier types
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#ifndef _qsim_id_h_included
#define _qsim_id_h_included

/**
 * \brief Declarations related to *qSim*
 */
namespace qsim {

/**
 * \brief Basic identifier type, used extensively throughout *qSim*
 *
 * Legitimate identifiers are generally greater than zero, with zero denoting
 * an unknown or undefined entity.
 */
using id_t = unsigned long int;

/**
 * \brief Alias for an undefined identifier
 */
constexpr id_t undefined_id = 0;

/**
 * \brief An identifier for a *Model Type*
 *
 * A Model Type is roughly analagous to a C++ type or class, while a Model
 * Instance corresponds to a C++ object.
 */
using model_type_id_t = id_t;

/**
 * \brief Alias for an undefined model type identifier
 */
constexpr id_t undefined_model_type_id = 0;

/**
 * \brief An identifier for a *Model Instance*
 *
 * A Model Type is roughly analagous to a C++ type or class, while a Model
 * Instance corresponds to a C++ object. A Model Instance is sometimes
 * referred to as an Entity in a Simulation.
 */
using model_instance_id_t = id_t;

/**
 * \brief Alias for an undefined model instance identifier
 */
constexpr id_t undefined_model_instance_id = 0;

}   // end qsim namespace

#endif
