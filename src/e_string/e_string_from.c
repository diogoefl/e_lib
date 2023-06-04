/* Copyright (c) 2023, diogoefl
 * SPDX-License-Identifier: BSD-3-Clause
 * See LICENSE file at this project root for more detailed information
 */

/* e_string_from implementation
 *
 * this module implements constructors of e_string_t.
 * 
 * usage: add #include "e_string.h" to your file and link to e_string library
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "e_string.h"


e_string_t e_string_from_cstr(const char* cstr)
{

    const size_t input_length = strlen(cstr);
    const size_t memory_buffer = input_length * sizeof(uint8_t);
    
    e_string_t result = {
        .data_length = input_length,
        .buffer_capacity = memory_buffer,
        .data = malloc(memory_buffer)
    };

    for (size_t i = 0; i < input_length; i++) {
        result.data[i] = cstr[i];
    }
    
    return result;
}


e_string_t e_string_from_uint64(const uint64_t number)
{
    /* define how many digits there are in number */
    const int digits = (int)(log10(number) + 1);
    char* cstr = calloc(digits, sizeof(uint8_t));
    snprintf(cstr, digits, "%ju", number);

    e_string_t result = e_string_from_cstr(cstr);

    free(cstr);

    return result;
}

e_string_t e_string_from_uint32(const uint32_t number)
{
    /* define how many digits there are in number */
    const int digits = (int)(log10(number) + 1);
    char* cstr = calloc(digits, sizeof(uint8_t));
    snprintf(cstr, digits, "%u", number);

    e_string_t result = e_string_from_cstr(cstr);

    free(cstr);

    return result;
}

e_string_t e_string_from_uint16(const uint16_t number)
{
    /* define how many digits there are in number */
    const int digits = (int)(log10(number) + 1);
    char* cstr = calloc(digits, sizeof(uint8_t));
    snprintf(cstr, digits, "%hu", number);

    e_string_t result = e_string_from_cstr(cstr);

    free(cstr);

    return result;
}

e_string_t e_string_from_uint8(const uint8_t number)
{
    /* define how many digits there are in number */
    const int digits = (int)(log10(number) + 1);
    char* cstr = calloc(digits, sizeof(uint8_t));
    snprintf(cstr, digits, "%hu", number);

    e_string_t result = e_string_from_cstr(cstr);

    free(cstr);

    return result;
}

e_string_t e_string_from_int64(const int64_t number)
{
    /* define how many digits there are in number */
    const int digits = (number < 0) ? (int)(log10(number) + 2)
                                    : (int)(log10(number) + 1);
    char* cstr = calloc(digits, sizeof(uint8_t));
    snprintf(cstr, digits, "%jd", number);

    e_string_t result = e_string_from_cstr(cstr);

    free(cstr);

    return result;
}

e_string_t e_string_from_int32(const int32_t number)
{
    /* define how many digits there are in number */
    const int digits = (number < 0) ? (int)(log10(number) + 2)
                                    : (int)(log10(number) + 1);
    char* cstr = calloc(digits, sizeof(uint8_t));
    snprintf(cstr, digits, "%d", number);

    e_string_t result = e_string_from_cstr(cstr);

    free(cstr);

    return result;
}

e_string_t e_string_from_int16(const int16_t number)
{
    /* define how many digits there are in number */
    const int digits = (number < 0) ? (int)(log10(number) + 2)
                                    : (int)(log10(number) + 1);
    char* cstr = calloc(digits, sizeof(uint8_t));
    snprintf(cstr, digits, "%hd", number);

    e_string_t result = e_string_from_cstr(cstr);

    free(cstr);

    return result;
}

e_string_t e_string_from_int8(const int8_t number)
{
    /* define how many digits there are in number */
    const int digits = (number < 0) ? (int)(log10(number) + 2)
                                    : (int)(log10(number) + 1);
    char* cstr = calloc(digits, sizeof(uint8_t));
    snprintf(cstr, digits, "%hd", number);

    e_string_t result = e_string_from_cstr(cstr);

    free(cstr);

    return result;
}

e_string_t e_string_from_int(const int number)
{
    /* define how many digits there are in number */
    const int digits = (number < 0) ? (int)(log10(number) + 2)
                                    : (int)(log10(number) + 1);
    char* cstr = calloc(digits, sizeof(uint8_t));
    snprintf(cstr, digits, "%d", number);

    e_string_t result = e_string_from_cstr(cstr);

    free(cstr);

    return result;
}

e_string_t e_string_from_uint(const unsigned int number)
{
    /* define how many digits there are in number */
    const int digits = (int)(log10(number) + 1);
    char* cstr = calloc(digits, sizeof(uint8_t));
    snprintf(cstr, digits, "%u", number);

    e_string_t result = e_string_from_cstr(cstr);

    free(cstr);

    return result;
}