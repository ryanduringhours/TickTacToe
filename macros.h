#pragma once

#include <assert.h>   // see TO_BE_IMPLEMENTED
#include <stddef.h>   // for size_t
#include <stdint.h>   // for uint16_t, uint32_t
#include <string.h>   // for memset()

/**
 * @brief find max and min
 */
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * @brief initialise to zero
 */
#define zero_var(X) memset(&X, 0, sizeof(X))
#define zero_ptr(X) memset(X, 0, sizeof(*X))

/**
 * @brief for incomplete programs
 */

#define TO_BE_IMPLEMENTED() \
    do { fprintf(stderr, "NOTE: to be implemented\n"); assert(0); } while (0)
