# Copyright (c) 2023, diogoefl
# SPDX-License-Identifier: BSD-3-Clause
# See LICENSE file at this project root for more detailed information

# e_string Library testing

# e_string_validate function testing
add_executable(e_string_validate_test
               "e_string_validate_test.c")

set_property(TARGET e_string_validate_test PROPERTY C_STANDARD          23)
set_property(TARGET e_string_validate_test PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET e_string_validate_test PROPERTY C_EXTENSIONS        OFF)

target_include_directories(e_string_validate_test PRIVATE
                           $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>)

target_link_libraries(e_string_validate_test PRIVATE e_string)

# Tests expected to succeed
add_test("valid:[e_string_validate] ascii 1" e_string_validate_test "hello" 5)
add_test("valid:[e_string_validate] ascii 2" e_string_validate_test "abc" 3)
add_test("valid:[e_string_validate] latin" e_string_validate_test "á" 2)
add_test("valid:[e_string_validate] chinese" e_string_validate_test "你好" 6)

# Tests expected to fail
add_test("invalid:[e_string_validate] ascii" e_string_validate_test "abc" 2)
add_test("invalid:[e_string_validate] latin" e_string_validate_test "á" 1)
add_test("invalid:[e_string_validate] chinese" e_string_validate_test "你好" 4)

set_tests_properties("invalid:[e_string_validate] ascii"
                     "invalid:[e_string_validate] latin"
                     "invalid:[e_string_validate] chinese"
                     PROPERTIES WILL_FAIL TRUE)
