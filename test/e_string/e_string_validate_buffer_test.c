/* Copyright (c) 2023, diogoefl
 * SPDX-License-Identifier: BSD-3-Clause
 * See LICENSE file at this project root for more detailed information
 */

/* e_string_validate namespace testing*/

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

#include "e_string.h"

/* private function priv_process_args
 *
 * retrieve arguments given and process data to create e_string_t
 */
e_string_t priv_process_args(const int argc, char*const argv[])
{
    if (argc < 3) {
        fprintf(stdout, "%s\n%s\n",
                u8"[e_string_validate] error: missing argument for testing",
                u8"[e_string_validate] usage: e_string_validate_test string length_number");
        exit(EXIT_FAILURE);
    } else if (argc > 3) {
        fprintf(stdout, "%s\n%s\n",
                u8"[e_string_validate] error: too many arguments for testing",
                u8"[e_string_validate] usage: e_string_validate_test string length_number");
        exit(EXIT_FAILURE);
    }

    const char* input = argv[1];
    int expected_size = atoi(argv[2]);

    if (expected_size <= 0) {
        fprintf(stdout, "%s\n%s\n",
                u8"[e_string_validate] error: expected positive number greater than 0 as second argument",
                u8"[e_string_validate] usage: e_string_validate_test string length_number");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "%s: %d\n",
            u8"[e_string_validate] input for expected size", expected_size);

    const size_t input_length = strlen(input);
    const size_t memory_buffer = expected_size * sizeof(uint8_t);

    fprintf(stdout, "%s: %s\n",
            u8"[e_string_validate] input given", input);
    fprintf(stdout, "%s: %zu\n",
            u8"[e_string_validate] input length", input_length);
    fprintf(stdout, "%s: %zu\n",
            u8"[e_string_validate] input memory required", memory_buffer);
    
    e_string_t result = {
        .data_length = input_length,
        .buffer_capacity = memory_buffer,
        .data = malloc(memory_buffer)
    };

    for (size_t i = 0; i < expected_size; i++) {
        result.data[i] = input[i];
    }
    
    return result;
}

/* private function priv_validate_buffer
 *
 * check if buffer_capacity and data_length are compatible
 */
bool priv_validate_buffer(e_string_t string)
{
    if (string.buffer_capacity < string.data_length) {
        fprintf(stdout, "%s %d\n%s\n",
                u8"[e_string_validate] error: corrupted e_string may return e_string_errno_t of",
                E_STRING_INVALID_BUFFER,
                u8"[e_string_validate] error: memory buffer is incompatible with data length");
    } else if (string.buffer_capacity == string.data_length) {
        fprintf(stdout, "%s\n",
                u8"[e_string_validate] valid: memory buffer is equal data length");
    } else {
        fprintf(stdout, "%s\n",
                u8"[e_string_validate] valid: memory buffer is bigger than data length");
    }
     fprintf(stdout, "%s %zu\n%s %zu\n",
             u8"[e_string_validate] buffer detected:", string.buffer_capacity,
             u8"[e_string_validate] length required:", string.data_length);

     return (e_string_validate(&string) == E_STRING_INVALID_BUFFER) ? false : true;
}


/* e_string_validate_buffer_test_valid
 *
 * create string based on input and test if string are valid.
 */
int main(int argc, char* argv[])
{
    /* process input */
    setlocale(LC_ALL, "en_US.utf8");
    e_string_t string = priv_process_args(argc, argv);
    
    /* execute validations */
    if (priv_validate_buffer(string) == false) {
        exit(EXIT_FAILURE);
    }

    /* no errors found - print string data */
    fprintf(stdout, "%s: %.*s\n",
            u8"[e_string_validate] e_string data", (int)string.data_length, string.data);
    fprintf(stdout, "%s: %zu\n",
            u8"[e_string_validate] e_string length", string.data_length);
    fprintf(stdout, "%s: %zu\n",
            u8"[e_string_validate] e_string buffer size", string.buffer_capacity);
    

    return EXIT_SUCCESS;
}