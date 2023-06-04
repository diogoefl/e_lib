/* Copyright (c) 2023, diogoefl
 * SPDX-License-Identifier: BSD-3-Clause
 * See LICENSE file at this project root for more detailed information
 */

/* e_string_utf8 helper header 
 *
 * this is a helper module not exported.
 * final user is not supposed to use this header.
 */

#ifndef E_STRING_UTF8_H
#define E_STRING_UTF8_H

#include <stdbool.h>
#include <stdint.h>

/* e_string_utf8_is_ascii
 *
 * checks if data is compliant to US ASCII on UTF-8 encoding, 
 * based on definitions of 
 * https://www.w3.org/International/questions/qa-forms-utf-8
 * 
 * US ASCII is represented in e_string_t as 1 byte (8 bit) with the value
 * ranging from 0x00 upto 0x7F. 
 *
 * if sanity check is true, the following items from 0x00 to 0x1F are considered
 * invalid, as they can represent conflicts for usage and should not be
 * inside of a e_string_t which attempts to represent simple text strings.
 * if you need a string with this type of characters, please use char* instead.
 *   - 0x00 NUL
 *   - 0x01 SOH
 *   - 0x02 STX
 *   - 0x03 ETX
 *   - 0x04 EOT
 *   - 0x05 ENT
 *   - 0x06 ACK
 *   - 0x07 \a
 *   - 0x08 \b
 *   - 0x0B VT
 *   - 0x0C \f
 *   - 0x0E SO
 *   - 0x0F SI
 *   - 0x10 DLE
 *   - 0x11 DC1
 *   - 0x12 DC2
 *   - 0x13 DC3
 *   - 0x14 DC4
 *   - 0x15 NAK
 *   - 0x16 SYN
 *   - 0x17 ETB
 *   - 0x18 CAN
 *   - 0x19 EM
 *   - 0x1A SUB
 *   - 0x1B \e
 *   - 0x1C FS
 *   - 0x1D GS
 *   - 0x1E RS
 *   - 0x1F US
 *   - 0x7F DEL
 *
 * ranging from 0x00 to 0x1F, the following items are valid for e_string_t,
 * regardless of sanity check value.
 *   - 0x09 \t
 *   - 0x0A LF
 *   - 0x0D CR
 */
bool e_string_utf8_is_ascii(const uint8_t u8_byte, const bool sanity);

/* e_string_utf8_is_non_overlong
 *
 * checks if data is compliant to non-overlong 2 bytes on UTF-8 encoding, 
 * based on definitions of 
 * https://www.w3.org/International/questions/qa-forms-utf-8
 * 
 * non-overlong is represented in e_string_t as 2 bytes (16 bit) with the value
 * of the first byte ranging from 0xC2 upto 0xDF and the second byte ranging
 * from 0x80 upto 0xBF.
 *
 * if the codepoint is non-overlong you need both bytes for the correct output.
 */
bool e_string_utf8_is_non_overlong(const uint8_t u8_1st_byte,
                                   const uint8_t u8_2nd_byte);


/* e_string_utf8_is_excluding_overlong
 *
 * checks if data is compliant to excluding overlong 3 bytes on UTF-8 encoding, 
 * based on definitions of 
 * https://www.w3.org/International/questions/qa-forms-utf-8
 * 
 * excluding overlong is represented in e_string_t as 3 bytes (24 bit) with the
 * value of the first byte being 0xE0, the second byte ranging from 0xA0 upto
 * 0xBF and the third byte ranging from 0x80 upto 0xBF.
 *
 * if the codepoint is excluding overlong you need all bytes for the correct output.
 */
bool e_string_utf8_is_excluding_overlong(const uint8_t u8_1st_byte,
                                         const uint8_t u8_2nd_byte,
                                         const uint8_t u8_3rd_byte);


/* e_string_utf8_is_straight_3byte
 *
 * checks if data is compliant to straight 3-byte on UTF-8 encoding, 
 * based on definitions of 
 * https://www.w3.org/International/questions/qa-forms-utf-8
 * 
 * straight 3-byte is represented in e_string_t as 3 bytes (24 bit) with the
 * value of the first byte ranging from 0xE1 upto 0xEC or from 0xEE upto 0xEF,
 * the second byte ranging from 0x80 upto 0xBF and the third byte ranging from
 * 0x80 upto 0xBF.
 *
 * if the codepoint is straight 3-byte you need all bytes for the correct output.
 */
bool e_string_utf8_is_straight_3byte(const uint8_t u8_1st_byte,
                                     const uint8_t u8_2nd_byte,
                                     const uint8_t u8_3rd_byte);


/* e_string_utf8_is_excluding_surrogates
 *
 * checks if data is compliant to excluding surrogates on UTF-8 encoding, 
 * based on definitions of 
 * https://www.w3.org/International/questions/qa-forms-utf-8
 * 
 * excluding surrogates is represented in e_string_t as 3 bytes (24 bit) with 
 * the value of the first byte is 0xED, the second byte ranging from 0x80 upto
 * 0x9F and the third byte ranging from 0x80 upto 0xBF.
 *
 * if the codepoint is excluding surrogates you need all bytes for the correct output.
 */
bool e_string_utf8_is_excluding_surrogates(const uint8_t u8_1st_byte,
                                           const uint8_t u8_2nd_byte,
                                           const uint8_t u8_3rd_byte);


/* e_string_utf8_is_plane_1to3
 *
 * checks if data is compliant to planes 1-3 on UTF-8 encoding, 
 * based on definitions of 
 * https://www.w3.org/International/questions/qa-forms-utf-8
 * 
 * planes 1-3 is represented in e_string_t as 4 bytes (32 bit) with 
 * the value of the first byte is 0xF0, the second byte ranging from 0x90 upto
 * 0xBF, the third byte ranging from 0x80 upto 0xBF and the fourth byte ranging
 * from 0x80 upto 0xBF.
 *
 * if the codepoint is planes 1-3 you need all bytes for the correct output.
 */
bool e_string_utf8_is_plane_1to3(const uint8_t u8_1st_byte,
                                 const uint8_t u8_2nd_byte,
                                 const uint8_t u8_3rd_byte,
                                 const uint8_t u8_4th_byte);


/* e_string_utf8_is_plane_4to15
 *
 * checks if data is compliant to planes 4-15 on UTF-8 encoding, 
 * based on definitions of 
 * https://www.w3.org/International/questions/qa-forms-utf-8
 * 
 * planes 4-15 is represented in e_string_t as 4 bytes (32 bit) with 
 * the value of the first byte ranging from 0xF1 upto 0xF3, the second byte
 * ranging from 0x80 upto 0xBF, the third byte ranging from 0x80 upto 0xBF and
 * the fourth byte ranging from 0x80 upto 0xBF.
 *
 * if the codepoint is planes 4-15 you need all bytes for the correct output.
 */
bool e_string_utf8_is_plane_4to15(const uint8_t u8_1st_byte,
                                  const uint8_t u8_2nd_byte,
                                  const uint8_t u8_3rd_byte,
                                  const uint8_t u8_4th_byte);


/* e_string_utf8_is_plane_16
 *
 * checks if data is compliant to plane 16 on UTF-8 encoding, 
 * based on definitions of 
 * https://www.w3.org/International/questions/qa-forms-utf-8
 * 
 * plane 16 is represented in e_string_t as 4 bytes (32 bit) with 
 * the value of the first byte is 0xF4, the second byte ranging from 0x80 upto
 * 0x8F, the third byte ranging from 0x80 upto 0xBF and the fourth byte ranging
 * from 0x80 upto 0xBF.
 *
 * if the codepoint is plane 16 you need all bytes for the correct output.
 */
bool e_string_utf8_is_plane_16(const uint8_t u8_1st_byte,
                               const uint8_t u8_2nd_byte,
                               const uint8_t u8_3rd_byte,
                               const uint8_t u8_4th_byte);

#endif /* E_STRING_UTF8_H */