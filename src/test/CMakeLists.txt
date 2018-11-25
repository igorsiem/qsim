# Cmake project file for building qSim tests
#
# Copyright Igor Siemienowicz 2018
# Distributed under the Boost Software License, Version 1.0. (See
# accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt)

file (GLOB TEST_SRC *.cpp)
add_executable(test-qsim ${TEST_SRC})
target_link_libraries(test-qsim PRIVATE fmt-header-only)
