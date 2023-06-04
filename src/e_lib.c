/* Copyright (c) 2023, diogoefl
 * SPDX-License-Identifier: BSD-3-Clause
 * See LICENSE file at this project root for more detailed information
 */

/* e_lib implementation 
 *
 * this library implements common usage requirements for c projects
 */

#include <stdint.h>
#include <stdio.h>

#include "e_lib.h"

/* Simple math function to use on CTest */
int64_t e_add9(const int64_t input)
{
    int64_t result = input + 9;
    return result;
}