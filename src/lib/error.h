/**
 * \file error.h
 * qSim error class definitions
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <qlib/qlib.h>

#ifndef _qsim_error_h_defined
#define _qsim_error_h_defined

/**
 * \brief Declare a class for signalling an error condition with a
 * constructor that takes an error message at runtime
 * 
 * \param cname The name of the error class
 * 
 * \param base_cname The base class for the error class; this should be
 * one of the `std::exception` classes that take a message argument in their
 * constructor
 */
#define DECLARE_ERROR_CLASS( cname, base_cname ) \
class cname : public base_cname \
{ \
    public: \
    explicit cname(const std::string& what_arg) : base_cname(what_arg) {} \
    explicit cname(const char* what_arg) : base_cname(what_arg) {} \
    DECLARE_DEFAULT_MOVE_AND_COPY_SEMANTICS(cname) \
};

/**
 * \brief Declare a class for signalling an error condition with a fixed
 * compiler-time error message
 * 
 * \param cname The name of the error class
 * 
 * \param base_cname The base class for the error class; this should be
 * one of the `std::exception` classes
 * 
 * \param msg The error message to use
 */
#define DECLARE_MESSAGE_ERROR_CLASS( cname, base_cname, msg ) \
class cname : public base_cname \
{ \
    public: DECLARE_ALL_VIRTUAL_DEFAULTS(cname) \
    virtual const char* what(void) const noexcept override \
        { return msg; } \
};

#endif
