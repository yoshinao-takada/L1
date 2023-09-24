#if !defined(_01BASE_UTILS_H)
#define _01BASE_UTILS_H
#include <stdbool.h>

/*!
\brief find word in RefWords
\return -1: not found, >=0: index of RefWords
*/
int SLCUtils_FindWord(int szRefWords, const char* const *RefWords, const char* word);

/*!
\brief parse concatinatedWords which is a combined string of words with
    separator characters. The words must match one of RefWords.
    result is an array which size is szRefWords.
    result[*] is set true if concatinatedWords matches RefWords[*].
    Error messages are printed into stderr.
\return EXIT_SUCCESS: success, EXIT_FAILURE: error
*/
int SLCUtils_ParseConcatinatedLabels(int szRefWords, const char* const* RefWords,
    char separator, const char* concatinatedWords, bool *result);

/*!
\brief set bool array to the value.
*/
void SLCUtils_SetBools(bool value, int szBools, bool* bools);

#define SLCUtils_ArraySize(__a) (sizeof(__a)/sizeof(__a[0]))

#define SLCUtils_IF_ERR_PRINT(__err, ...) if (__err) { \
    fprintf(stderr, __VA_ARGS__); }

#define SLCUtils_IF_ERR_BREAK(__err, ...) if (__err) { \
    fprintf(stderr, __VA_ARGS__); break; }

#endif
