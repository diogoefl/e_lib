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
#include <stddef.h>


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

    size_t data_iterator = 0;
    while (data_iterator < string->data_length) {
        /* checking US-ASCII 1-byte
         * can be represented as [\x00-\x7F]
         */
        if ( string->data[data_iterator] == 0x09 ||
             string->data[data_iterator] == 0x0A ||
             string->data[data_iterator] == 0x0D ||
            (string->data[data_iterator] <= 0x20 &&
             string->data[data_iterator] <= 0x7E) ) {       
            /* this item is US-ASCII move 1 size for next */
            data_iterator += 1;
            continue;
        }

        /* sanity checking if data still has 2 uint8_t
         * if there is less than 2 uint8_t left than we have invalid utf8
         * all of the next checks require at least 2-byte
         */
        if (string->data_length - data_iterator < 2) {
            result = E_STRING_INVALID_UTF8;
            break;
        }

        /* checking non-overlong 2-byte
         * can be represented as [\xC2-\xDF][\x80-\xBF]
         */
        if ((0xC2 <= string->data[data_iterator] && string->data[data_iterator] <= 0xDF) &&
            (0x80 <= string->data[data_iterator + 1] && string->data[data_iterator + 1] <= 0xBF)) {
            /* this item is non-overlong 2-byte, move 2 size for next */
            data_iterator += 2;
            continue;
        }

        /* sanity checking if data still has 3 uint8_t
         * if there is less than 3 uint8_t left than we have invalid utf8
         * all of the next checks require at least 3-byte
         */
        if (string->data_length - data_iterator < 3) {
            result = E_STRING_INVALID_UTF8;
            break;
        }

        /* checking straight 3-byte
         * can be represented as [\xE1-\xEC\xEE\xEF][\x80-\xBF]{2}
         * excluding overlongs \xE0[\xA0-\xBF][\x80-\xBF]
         * excluding surrogates \xED[\x80-\x9F][\x80-\xBF]
         */
        if (( /* excluding overlongs */
            
                /* 1st byte is 0xE0 */
                string->data[data_iterator] == 0xE0 &&
                /* 2nd byte is among 0xA0 and 0xBF */
                (0xA0 <= string->data[data_iterator + 1] && string->data[data_iterator + 1] <= 0xBF) &&
                /* 3rd byte is among 0x80 and 0xBF */
                (0x80 <= string->data[data_iterator + 2] && string->data[data_iterator + 2] <= 0xBF)

            ) /* end excluding overlongs */
        
            ||
            
            ( /* check straight 3-byte */
            
                /* 1st byte is either among 0xE1 and 0xEC or it is 0xEE or it is 0xEF */
                (string->data[data_iterator] == 0xEE ||
                 string->data[data_iterator] == 0xEF ||
                (0xE1 <= string->data[data_iterator] && string->data[data_iterator] <= 0xEC)) &&
                /* 2nd byte is among 0x80 and 0xBF */
                (0x80 <= string->data[data_iterator + 1] && string->data[data_iterator + 1] <= 0xBF) &&
                /* 3rd byte is among 0x80 and 0xBF */
                (0x80 <= string->data[data_iterator + 2] && string->data[data_iterator + 2] <= 0xBF)
            
            ) /* end check straight 3-byte */

            ||

            ( /* excluding surrogates */

                /* 1st byte is 0xED */
                string->data[data_iterator] == 0xED &&
                /* 2nd byte is among 0x80 and 0x9F */
                (0x80 <= string->data[data_iterator + 1] && string->data[data_iterator + 1] <= 0x9F) &&
                /* 3rd byte is among 0x80 and 0xBF */
                (0x80 <= string->data[data_iterator + 2] && string->data[data_iterator + 2] <= 0xBF)

            ) /* end excluding surrogates */
        ) {
            /* this item is straight 3-byte, move 3 size for next */
            data_iterator += 3;
            continue;
        }

        /* sanity checking if data still has 4 uint8_t
         * if there is less than 4 uint8_t left than we have invalid utf8
         * all of the next checks require at least 4-byte
         */
        if (string->data_length - data_iterator < 4) {
            result = E_STRING_INVALID_UTF8;
            break;
        }

        /* checking plane 4-byte
         * planes 1-3 can be represented as \xF0[\x90-\xBF][\x80-\xBF]{2}
         * planes 4-15 can be represented as [\xF1-\xF3][\x80-\xBF]{3}
         * plane 16 can be represented as \xF4[\x80-\x8F][\x80-\xBF]{2}
         */
        if (( /* planes 1-3 */

                /* 1st byte is 0xF0 */
                string->data[data_iterator] == 0xF0 &&
                /* 2nd byte is among 0x90 and 0xBF */
                (0x90 <= string->data[data_iterator + 1] && string->data[data_iterator + 1] <= 0xBF) &&
                /* 3rd byte is among 0x80 and 0xBF */
                (0x80 <= string->data[data_iterator + 2] && string->data[data_iterator + 2] <= 0xBF) &&
                /* 4th byte is among 0x80 and 0xBF */
                (0x80 <= string->data[data_iterator + 3] && string->data[data_iterator + 3] <= 0xBF)

            ) /* end planes 1-3 */

            ||

            ( /* planes 4-15 */

                /* 1st byte is among 0xF1 and 0xF3 */
                (0xF1 <= string->data[data_iterator] && string->data[data_iterator] <= 0xF3) &&
                /* 2nd byte is among 0x80 and 0xBF */
                (0x80 <= string->data[data_iterator + 1] && string->data[data_iterator + 1] <= 0xBF) &&
                /* 3rd byte is among 0x80 and 0xBF */
                (0x80 <= string->data[data_iterator + 2] && string->data[data_iterator + 2] <= 0xBF) &&
                /* 4th byte is among 0x80 and 0xBF */
                (0x80 <= string->data[data_iterator + 3] && string->data[data_iterator + 3] <= 0xBF)

            ) /* end planes 4-15*/

            ||

            ( /* plane 16 */

                /* 1st byte is 0xF4 */
                string->data[data_iterator] == 0xF4 &&
                /* 2nd byte is among 0x80 and 0x8F */
                (0x80 <= string->data[data_iterator + 1] && string->data[data_iterator + 1] <= 0x8F) &&
                /* 3rd byte is among 0x80 and 0xBF */
                (0x80 <= string->data[data_iterator + 2] && string->data[data_iterator + 2] <= 0xBF) &&
                /* 4th byte is among 0x80 and 0xBF */
                (0x80 <= string->data[data_iterator + 3] && string->data[data_iterator + 3] <= 0xBF)

            ) /* end plane 16 */

        ) {
            /* this item is plane 4-byte, move 4 size for next */
            data_iterator += 4;
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