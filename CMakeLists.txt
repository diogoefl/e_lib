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

# Adding submodules
add_subdirectory(src)

# Adding project lib testing
enable_testing()
add_subdirectory(test)
