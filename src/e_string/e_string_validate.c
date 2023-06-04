/* Copyright (c) 2023, diogoefl
 * SPDX-License-Identifier: BSD-3-Clause
 * See LICENSE file at this project root for more detailed information
 */

/* e_string_validate implementation
 *
 * this module implements validation of UTF-8 growable strings.
 * 
 * usage: add #include "e_string.h" to your file and link to e_string library
 */


#include "e_string.h"


/* private function e_string_validate_buffer
 *
 * checks if memory buffer and data length are compatible
 */
e_string_errno_t e_string_validate_buffer(const e_string_t* string)
{
    e_string_errno_t result = E_STRING_SUCCESS;
    if (string->buffer_capacity < string->data_length)
    {
        result = E_STRING_INVALID_BUFFER;
    }
    return result;
}

/* private function e_string_validate_utf8
 *
 * checks if data is of correct UTF-8 encoding
 * 
 * TODO
 */
e_string_errno_t e_string_validate_utf8(const e_string_t* string)
{
    e_string_errno_t result = E_STRING_SUCCESS;

    return result;
}

e_string_errno_t e_string_validate(const e_string_t* string)
{
    if (e_string_validate_buffer(string) == E_STRING_INVALID_BUFFER) {
        return E_STRING_INVALID_BUFFER;
    } else if (e_string_validate_utf8(string) == E_STRING_INVALID_UTF8) {
        return E_STRING_INVALID_UTF8;
    }
    return E_STRING_SUCCESS;
}