# Copyright (c) 2023, diogoefl
# SPDX-License-Identifier: BSD-3-Clause
# See LICENSE file at this project root for more detailed information

# Main library
add_library(e_lib STATIC
            "e_lib.c")

set_property(TARGET e_lib PROPERTY C_STANDARD          23 )
set_property(TARGET e_lib PROPERTY C_STANDARD_REQUIRED ON )
set_property(TARGET e_lib PROPERTY C_EXTENSIONS        OFF)

target_include_directories(e_lib PRIVATE
                           $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include/e_lib>)

set_target_properties(e_lib PROPERTIES
                      PUBLIC_HEADER "include/e_lib.h")

INSTALL(TARGETS e_lib
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/e_lib)

# e_lib submodules
add_subdirectory(e_string)