# Cmake project file for building the qSim CLI
#
# Copyright Igor Siemienowicz 2018
# Distributed under the Boost Software License, Version 1.0. (See
# accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt)

file (GLOB CLI_SRC *.cpp)
add_executable(qsim-cli ${CLI_SRC})
