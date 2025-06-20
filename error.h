#pragma once
//error messages
#include <assert.h>
#include <stdio.h> // for fprintf

#define ERR_NONE 0

enum error_codes {
    ERR_FIRST = -128, // not an actual error but to set the first error number, subsequent entries increment by 1
    ERR_SOCKET,
    ERR_INVALID_ARGUMENT,
    ERR_ADDRESS,
    ERR_NETWORK,
    //add error messages as required
    ERR_LAST
};

#define M_REQUIRE_NON_NULL(arg)                                                \
    do {                                                                       \
        if (arg == NULL) {                                                     \
            printf("ERROR: parameter %s is NULL when calling  %s() "     \
                         "(defined in %s)\n",                                  \
                         #arg, __func__, __FILE__);                            \
            return ERR_INVALID_ARGUMENT;                                       \
        }                                                                      \
    } while (0)

#define print_error(code)    fprintf(stderr, "ERROR: %s\n", ERR_MSG(code))

extern const char *const ERR_MESSAGES[];


#define ERR_MSG(err)                                                           \
    (ERR_FIRST < (err) && (err) < ERR_LAST ? ERR_MESSAGES[(err) - ERR_FIRST]   \
                                           : "Invalid error code")





