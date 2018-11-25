# Top-level Cmake project file for building qSim
#
# Copyright Igor Siemienowicz 2018
# Distributed under the Boost Software License, Version 1.0. (See
# accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.10)
project(qSim LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include_directories(
    .
    external
    external/qlib/third-party/fmt/include
    third-party
)

add_subdirectory(cli)
add_subdirectory(test)
add_subdirectory(external/qlib/third-party/fmt EXCLUDE_FROM_ALL)
