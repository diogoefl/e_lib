# Copyright (c) 2023, diogoefl
# SPDX-License-Identifier: BSD-3-Clause
# See LICENSE file at this project root for more detailed information

# e_string library
add_library(e_string STATIC
            "e_string_from.c"
            "e_string_utf8.c"
            "e_string_validate.c")

set_property(TARGET e_string PROPERTY C_STANDARD          17 )
set_property(TARGET e_string PROPERTY C_STANDARD_REQUIRED ON )
set_property(TARGET e_string PROPERTY C_EXTENSIONS        OFF)

target_include_directories(e_string PRIVATE
                           $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include/e_lib>)

set_target_properties(e_string PROPERTIES
                      PUBLIC_HEADER ["include/e_string.h"])

INSTALL(TARGETS e_string
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/e_lib)