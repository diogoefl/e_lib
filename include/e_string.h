/* Copyright (c) 2023, diogoefl
 * SPDX-License-Identifier: BSD-3-Clause
 * See LICENSE file at this project root for more detailed information
 */

/* e_string header 
 *
 * this module implements UTF-8 growable strings array with size tracking.
 * api inspiration is based on Rust std::String and data structure is also 
 * inspired by Luca Sas string handling library exposed at ACCU 2021 conference
 * talk available at: https://www.youtube.com/watch?v=QpAhX-gsHMs&t=3009s
 * 
 * usage: add #include "e_string.h" to your file
 */

#ifndef E_STRING_H
#define E_STRING_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* e_string struct
 *
 * this is the basic data structure to keep track on string size and capacity.
 * data will be stored always UTF-8 encoding, and functionality for conversion
 * can be used to retrieve cstr (NUL terminated strings).
 * 
 * PODs definition
 *   - data_length: defines the current length for the stored string
 *   - buffer_capacity: defines the amount of stored memory in the buffer
 *   - data: defines pointer to the start of the UTF-8 string data
 * 
 * length and capacity are stored as size_t to allow the maximum amount the
 * system can store - which is defined in SIZE_MAX .
 *
 * this is a growable string, therefore the buffer_capacity can be longer than
 * the data_length, but if for some reason the data_length is longer than the
 * buffer_capacity - an undefined behaviour can occur during the usage.
 *
 * the data is stored as UTF-8 strings, user must convert there string to UTF-8
 * compatible data prior to creating e_string_t.
 * functions for conversion are available at this library as well.
 */
typedef struct e_string
{
    size_t data_length;
    size_t buffer_capacity;
    uint8_t * data;
} e_string_t;

/* e_string errno macros
 *
 * this is a simple data that defines typical error that this library can exit.
 * all the errno used for e_string use the composition of the following numbers:
 *  - -5: defines e_lib prefix for errno to prevent conflict with c_errno
 *  -  1: defines e_string library
 *  -  0: defines specific errno
 * 
 * as an example -511 means an invalid buffer size (E_STRING_INVALID_BUFFER)
 * 
 * e_string_errno are negative in case of error to allow for easier comparison
 * on if statements.
 */
typedef int e_string_errno_t;
#define E_STRING_INVALID_BUFFER -511
#define E_STRING_INVALID_UTF8   -512
#define E_STRING_ERROR           false   /* 0 */
#define E_STRING_SUCCESS         true    /* 1 */


/* public functions: data access and validation
 * use this group of functions to validate e_string_t data and safe access.
 */

/* e_string_validate
 *
 * this function allows the user to validate if the string is valid, either by
 * checking if the data is UTF-8 compatible, or if the buffer and data is of
 * compatible size.
 *
 * it does not change the given data, nor it fix invalid structures.
 *
 * TODO: incomplete UTF8 checking
 */
e_string_errno_t e_string_validate(const e_string_t* string);


#endif /* E_STRING_H */