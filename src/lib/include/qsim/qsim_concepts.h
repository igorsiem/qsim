/**
 * \file qsim_concepts.h
 * Macro definitions so that qSim can use C++ concepts
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#ifndef _qsim_qsim_concepts_h_included
#define _qsim_qsim_concepts_h_included

#ifdef QSIM_USE_CONCEPTS

    /**
     * \brief Declare a template argument with concept-based constraints
     *
     * This macro only uses the concept name if `QSIM_USE_CONCEPTS` is
     * defined, otherwise it uses the `template` keyword to declare a
     * generic unconstrained type
     *
     * \param ConceptName The concept to use
     *
     * \param TypeArg The name of the type placeholder
     */
    #define QSIM_CONCEPT(ConceptName, TypeArg) ConceptName TypeArg

#else
    /**
     * \brief Declare a template argument with concept-based constraints
     *
     * This macro only uses the concept name if `QSIM_USE_CONCEPTS` is
     * defined, otherwise it uses the `template` keyword to declare a
     * generic unconstrained type
     *
     * \param ConceptName The concept to use
     *
     * \param TypeArg The name of the type placeholder
     */
    #define QSIM_CONCEPT(ConceptName, TypeArg) typename TypeArg
    
#endif

#endif
