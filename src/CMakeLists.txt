# Top-level Cmake project file for building qSim
#
# Copyright Igor Siemienowicz 2018
# Distributed under the Boost Software License, Version 1.0. (See
# accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.10)
project(qSim LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# --- Config Items ---

# Comment this out to disable use of the C++ Concepts TS
SET(QSIM_USE_CONCEPTS 1)

# ---

# Optionally enable C++ concepts
if (QSIM_USE_CONCEPTS)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts")
    add_definitions(-DQSIM_USE_CONCEPTS)
endif(QSIM_USE_CONCEPTS)

# Threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

FIND_PACKAGE(Boost COMPONENTS program_options thread system REQUIRED)

include_directories(
    .
    external
    external/qlib/third-party/fmt/include
    lib/include
    third-party
)

add_subdirectory(cli)
add_subdirectory(test)
add_subdirectory(external/qlib/third-party/fmt EXCLUDE_FROM_ALL)
