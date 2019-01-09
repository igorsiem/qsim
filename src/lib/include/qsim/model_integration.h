/**
 * \file model_integration.h
 * Structures for integrating related model types
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <type_traits>

#include "data_factory.h"
#include "model.h"

#ifndef _qsim_model_integration_h_included
#define _qsim_model_integration_h_included

namespace qsim {

// TODO a type where a model concept is paired with a data factory for
// initialisation, and we want to make sure that they have the same data
// type

template <
    QSIM_CONCEPT(is_model) ModelT
    , QSIM_CONCEPT(is_data_factory) InitDataFactoryT>
struct model_type_integration
{

    using model_t = ModelT;

    using init_data_factory_t = InitDataFactoryT;

    static_assert(
        std::is_same<
            typename model_t::init_data_t
            , typename init_data_factory_t::data_t>::value
        , "model initialisation type must be the same as the data type of "
            "its initialisation factory");

    using model_instance_wrapper_t = model_instance_wrapper<model_t>;

    /// template <typename... ArgTs>
    /// static model_instance_wrapper_t generate_instance_wrapper(ArgTs... args)
    /// {
    ///     return std::move(
    ///         model_instance_wrapper_t(
    ///             std::make_optional<model_t>(std::forward(args...))));
    /// }   // end generate_instance_wrapper method

};  // end model_type_integration struct

}   // end qsim namespace

#endif
