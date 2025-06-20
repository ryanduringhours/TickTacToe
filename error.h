#pragma once
//error messages
#include <assert.h>
#include <stdio.h> // for fprintf

#define ERR_NONE 0

//enum declaration of error codes
enum error_codes {
    ERR_FIRST = -128, // not an actual error but to set the first error number, subsequent entries increment by 1
    ERR_SOCKET, 				//-127
    ERR_INVALID_ARGUMENT,		//-126
    ERR_ADDRESS,				//-125
    ERR_NETWORK,				//-124
    //add error messages as required
    ERR_LAST
};

/**
 * @brief checks if the parameter is a NULL, prints error information and return error code
 */
#define M_REQUIRE_NON_NULL(arg)                                                \
    do {                                                                       \
        if (arg == NULL) {                                                     \
            printf("ERROR: parameter %s is NULL when calling  %s() "     \
                         "(defined in %s)\n",                                  \
                         #arg, __func__, __FILE__);                            \
            return ERR_INVALID_ARGUMENT;                                       \
        }                                                                      \
    } while (0)
//# is the stingification operator, turns arg into a string
//__funct__ is the name of the function in the program
//__FILE__ is the file name in the source file where the macro is used


/**
 * @brief Prints error message, related by the error code
 */
#define print_error(code)    fprintf(stderr, "ERROR: %s\n", ERR_MSG(code))

extern const char *const ERR_MESSAGES[];


/**
 * @brief converts error code to error message in string
 */
#define ERR_MSG(err)                                                           \
    (ERR_FIRST < (err) && (err) < ERR_LAST ? ERR_MESSAGES[(err) - ERR_FIRST]   \
                                           : "Invalid error code")
//checks range of error code and convert to error message




