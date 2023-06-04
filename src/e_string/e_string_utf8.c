/* Copyright (c) 2023, diogoefl
 * SPDX-License-Identifier: BSD-3-Clause
 * See LICENSE file at this project root for more detailed information
 */

/* e_string_utf8 implementation.
 *
 * this module implements UTF-8 helper functions.
 * final user is not supposed to use this module.
 */

#include "e_string_utf8.h"


bool e_string_utf8_is_ascii(const uint8_t u8_byte, const bool sanity)
{
    if (  u8_byte == 0x09                         /* TAB      */
       || u8_byte == 0x0A                         /* LF       */
       || u8_byte == 0x0D                         /* CR       */
       || (0x20 <= u8_byte && u8_byte <= 0x7E)) { /* SPC -> ~ */
        return true;
    }

    /* if sanity is disabled */
    if (u8_byte <= 0x7F && sanity == false) {
        return true;
    }

    /* otherwise the codepoint is not ASCII compliant */
    return false;
}


bool e_string_utf8_is_non_overlong(const uint8_t u8_1st_byte,
                                   const uint8_t u8_2nd_byte)
{
    if (  (0xC2 <= u8_1st_byte && u8_1st_byte <= 0xDF)
       && (0x80 <= u8_2nd_byte && u8_2nd_byte <= 0xBF)) {
        return true;
    }

    /* otherwise the codepoint is not non-overlong compliant */
    return false;
}


bool e_string_utf8_is_excluding_overlong(const uint8_t u8_1st_byte,
                                         const uint8_t u8_2nd_byte,
                                         const uint8_t u8_3rd_byte)
{
    if (  u8_1st_byte == 0xE0
       && (0xA0 <= u8_2nd_byte && u8_2nd_byte <= 0xBF)
       && (0x80 <= u8_3rd_byte && u8_3rd_byte <= 0xBF)) {
        return true;
    }

    /* otherwise the codepoint is not excluding overlongs compliant */
    return false;
}


bool e_string_utf8_is_straight_3byte(const uint8_t u8_1st_byte,
                                     const uint8_t u8_2nd_byte,
                                     const uint8_t u8_3rd_byte)
{
    if (  (  u8_1st_byte == 0xEE
          || u8_1st_byte == 0xEF
          || (0xE1 <= u8_1st_byte && u8_1st_byte <= 0xEC))
       && (0x80 <= u8_2nd_byte && u8_2nd_byte <= 0xBF)
       && (0x80 <= u8_3rd_byte && u8_3rd_byte <= 0xBF)) {
        return true;
    }

    /* otherwise the codepoint is not straight 3-byte compliant */
    return false;
}


bool e_string_utf8_is_excluding_surrogates(const uint8_t u8_1st_byte,
                                           const uint8_t u8_2nd_byte,
                                           const uint8_t u8_3rd_byte)
{
    if (  u8_1st_byte == 0xED
       && (0x80 <= u8_2nd_byte && u8_2nd_byte <= 0x9F)
       && (0x80 <= u8_3rd_byte && u8_3rd_byte <= 0xBF)) {
        return true;
    }

    /* otherwise the codepoint is not straight 3-byte compliant */
    return false;
}


bool e_string_utf8_is_plane_1to3(const uint8_t u8_1st_byte,
                                 const uint8_t u8_2nd_byte,
                                 const uint8_t u8_3rd_byte,
                                 const uint8_t u8_4th_byte)
{
    if (  u8_1st_byte == 0xF0
       && (0x90 <= u8_2nd_byte && u8_2nd_byte <= 0xBF)
       && (0x80 <= u8_3rd_byte && u8_3rd_byte <= 0xBF)
       && (0x80 <= u8_4th_byte && u8_4th_byte <= 0xBF)) {
        return true;
    }

    /* otherwise the codepoint is not plane 1-3 compliant */
    return false;
}


bool e_string_utf8_is_plane_4to15(const uint8_t u8_1st_byte,
                                  const uint8_t u8_2nd_byte,
                                  const uint8_t u8_3rd_byte,
                                  const uint8_t u8_4th_byte)
{
    if (  (0xF1 <= u8_1st_byte && u8_1st_byte <= 0xF3)
       && (0x80 <= u8_2nd_byte && u8_2nd_byte <= 0xBF)
       && (0x80 <= u8_3rd_byte && u8_3rd_byte <= 0xBF)
       && (0x80 <= u8_4th_byte && u8_4th_byte <= 0xBF)) {
        return true;
    }

    /* otherwise the codepoint is not plane 4-15 compliant */
    return false;
}


bool e_string_utf8_is_plane_16(const uint8_t u8_1st_byte,
                               const uint8_t u8_2nd_byte,
                               const uint8_t u8_3rd_byte,
                               const uint8_t u8_4th_byte)
{
    if (  u8_1st_byte == 0xF4
       && (0x80 <= u8_2nd_byte && u8_2nd_byte <= 0x8F)
       && (0x80 <= u8_3rd_byte && u8_3rd_byte <= 0xBF)
       && (0x80 <= u8_4th_byte && u8_4th_byte <= 0xBF)) {
        return true;
    }

    /* otherwise the codepoint is not plane 16 compliant */
    return false;
}