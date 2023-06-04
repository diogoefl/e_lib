# Copyright (c) 2023, diogoefl
# SPDX-License-Identifier: BSD-3-Clause
# See LICENSE file at this project root for more detailed information

# CMake Library testing

# Add9 function testing
add_executable(e_lib_test_add9
               "e_lib_add9_test.c")

set_property(TARGET e_lib_test_add9 PROPERTY C_STANDARD          23)
set_property(TARGET e_lib_test_add9 PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET e_lib_test_add9 PROPERTY C_EXTENSIONS        OFF)

target_include_directories(e_lib_test_add9 PRIVATE
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
                           $<INSTALL_INTERFACE:include/e_lib>)

target_link_libraries(e_lib_test_add9 PRIVATE e_lib)

add_test("[e_lib] add9" e_lib_test_add9)