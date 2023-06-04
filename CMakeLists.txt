# Copyright (c) 2023, diogoefl
# SPDX-License-Identifier: BSD-3-Clause
# See LICENSE file at this project root for more detailed information

# CMake Project setup
cmake_minimum_required(VERSION 3.23)
project(e_lib
        VERSION      0.0.1
        DESCRIPTION  "e_xtended basic library for C23"
        HOMEPAGE_URL "https://github.com/diogoefl/e_lib"
        LANGUAGES    C )

# Main library
add_library(e_lib STATIC
            "src/e_lib.c")

set_property(TARGET e_lib PROPERTY C_STANDARD          23 )
set_property(TARGET e_lib PROPERTY C_STANDARD_REQUIRED ON )
set_property(TARGET e_lib PROPERTY C_EXTENSIONS        OFF)

target_include_directories(e_lib PRIVATE
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include/e_lib>)

set_target_properties(e_lib PROPERTIES
                      PUBLIC_HEADER "include/e_lib.h")

INSTALL(TARGETS e_lib
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/e_lib)

# Adding project lib testing
enable_testing()
add_subdirectory(test)
