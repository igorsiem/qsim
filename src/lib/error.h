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

/**
 * \brief Throw an instance of a named exception class, writing a message
 * to the debug log at the same time
 * 
 * Note that the debug message is not the `what` message of the error type
 * itself. This would normally be logged separately at the catch point,
 * unless it can be resolved.
 * 
 * The underlying usage pattern here is that the error type is propagated
 * to the point where it can be either resolved or signalled to the user,
 * while the debug message contains programmer information (debug logging
 * may or may not be turned on).
 * 
 * \param error_type The type of error object to throw as an exception; this
 * should be default-constructible
 * 
 * \param debug_msg The message to write to the log; this should be a
 * standard string
 */
#define RAISE_ERROR_WITH_DEBUG_MESSAGE(error_type, debug_msg) \
    do { \
        ::qlib::logger::instance().log( \
            ::qlib::logger::level_t::debug \
            , std::string(debug_msg)); \
        throw error_type(); \
    } while (false)

/**
 * \brief Throw an instance of a named exception class, writing a (wide
 * string) message to the debug log at the same time
 * 
 * Note that the debug message is not the `what` message of the error type
 * itself. This would normally be logged separately at the catch point,
 * unless it can be resolved.
 * 
 * The underlying usage pattern here is that the error type is propagated
 * to the point where it can be either resolved or signalled to the user,
 * while the debug message contains programmer information (debug logging
 * may or may not be turned on).
 * 
 * \param error_type The type of error object to throw as an exception; this
 * should be default-constructible
 * 
 * \param debug_wmsg The message to write to the log; this should be a
 * wide string
 */
#define RAISE_ERROR_WITH_DEBUG_WMESSAGE(error_type, debug_wmsg) \
    do { \
        ::qlib::logger::instance().log( \
            ::qlib::logger::level_t::debug \
            , std::wstring(debug_wmsg)); \
        throw error_type(); \
    } while (false)

#endif
