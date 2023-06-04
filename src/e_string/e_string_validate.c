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


#include <stddef.h>
#include <stdint.h>

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
 * checks if data is of correct UTF-8 encoding, based on definitions of W3
 * https://www.w3.org/International/questions/qa-forms-utf-8
 * 
 * TODO: segment byte-checking on more pure and simple functions
 */
e_string_errno_t e_string_validate_utf8(const e_string_t* string)
{
    e_string_errno_t result = E_STRING_SUCCESS;

    size_t index = 0;
    while (index < string->data_length) {
        const uint8_t u8_1st = string->data[index];
        bool ascii = e_string_utf8_is_ascii(u8_1st, true);
        if (ascii == true) {
            index += 1;
            continue;
        }

        /* sanity checking if data still has 2 uint8_t */
        if (string->data_length - index < 2) {
            result = E_STRING_INVALID_UTF8;
            break;
        }

        const uint8_t u8_2nd = string->data[index + 1];
        bool non_overlong = e_string_utf8_is_non_overlong(u8_1st, u8_2nd);
        if (non_overlong == true) {
            index += 2;
            continue;
        }
        
        /* sanity checking if data still has 3 uint8_t */
        if (string->data_length - index < 3) {
            result = E_STRING_INVALID_UTF8;
            break;
        }

        const uint8_t u8_3rd = string->data[index + 2];
        bool exc_overl = e_string_utf8_is_excluding_overlong(u8_1st,
                                                             u8_2nd,
                                                             u8_3rd);
        bool straight_3b = e_string_utf8_is_straight_3byte(u8_1st,
                                                           u8_2nd,
                                                           u8_3rd);
        bool exc_surrog = e_string_utf8_is_excluding_surrogates(u8_1st,
                                                                u8_2nd, 
                                                                u8_3rd);
        if (exc_overl == true || straight_3b == true || exc_surrog == true)
        {
            index += 3;
            continue;
        }

        /* sanity checking if data still has 4 uint8_t */
        if (string->data_length - index < 4) {
            result = E_STRING_INVALID_UTF8;
            break;
        }

        const uint8_t u8_4th = string->data[index + 3];
        bool plane_1to3 = e_string_utf8_is_plane_1to3(u8_1st,
                                                      u8_2nd, 
                                                      u8_3rd,
                                                      u8_4th);
        bool plane_4to15 = e_string_utf8_is_plane_4to15(u8_1st,
                                                        u8_2nd,
                                                        u8_3rd,
                                                        u8_4th);
        bool plane_16 = e_string_utf8_is_plane_16(u8_1st,
                                                  u8_2nd,
                                                  u8_3rd,
                                                  u8_4th);
        if (plane_1to3 == true || plane_4to15 == true || plane_16 == true) {
            index += 4;
            continue;
        }

        /* if no condition was evaluated than we have an invalid utf8 byte */
        result = E_STRING_INVALID_UTF8;
        break;
    }

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