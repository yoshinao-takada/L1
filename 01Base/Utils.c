#include "SLC/Utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <alloca.h>

int SLCUtils_FindWord(int szRefWords, const char* const *RefWords, const char* word)
{
    int result = -1;
    for (int index = 0; index < szRefWords; index++)
    {
        if (0 == strcasecmp(word, RefWords[index]))
        {
            result = index;
            break;
        }
    }
    return result;
}


int SLCUtils_ParseConcatinatedLabels(int szRefWords, const char* const* RefWords,
    char separator, const char* concatinatedWords, bool *result
) {
    int err = EXIT_SUCCESS;
    char* buffer = NULL;
    int szConcatinatedWords = strlen(concatinatedWords);
    int szBuffer = 0;
    do {
        // check length of concatinatedWords
        int maxLength = szRefWords - 1;
        for (int i = 0; i < szRefWords; i++)
        {
            maxLength += (int)strlen(RefWords[i]);
        }
        SLCUtils_IF_ERR_BREAK(
            (err = (szConcatinatedWords > maxLength) ? EXIT_FAILURE : EXIT_SUCCESS),
            "concatinatedWords(=\"%s\") is too long @ %s,%d.\n", concatinatedWords,
            __FILE__, __LINE__);
        
        // split concatinatedWords
        szBuffer = szConcatinatedWords + 2;
        SLCUtils_IF_ERR_BREAK(
            err = (NULL == (buffer = (char*)alloca(szBuffer))) ? EXIT_FAILURE : EXIT_SUCCESS,
            "Fail in alloca(%d) @ %s,%d.\n", szBuffer, __FILE__, __LINE__);
        strcpy(buffer, concatinatedWords);
        for (int i = 0; i < szBuffer; i++)
        {
            if (buffer[i] == separator) buffer[i] = '\0';
        }
        buffer[szBuffer - 1] = '\0';

        // parse splitted words
        SLCUtils_SetBools(false, szRefWords, result); // clear result[*]
        bool notEnd = true;
        const char* scanner = buffer;
        do {
            int found = SLCUtils_FindWord(szRefWords, RefWords, scanner);
            if (found >= 0)
            {
                if (result[found])
                {
                    SLCUtils_IF_ERR_BREAK(err = EXIT_FAILURE,
                        "Duplicated \"%s\" @ %s,%d.\n", scanner, __FILE__, __LINE__);
                }
                result[found] = true;
            }
            else
            { // no match in RefWords
                fprintf(stderr, "Valie labels are \n");
                for (int i = 0; i < szRefWords; i++)
                {
                    const char* separator2 = i ? " | " : "[";
                    fprintf(stderr, "%s%s", separator2, RefWords[i]);
                }
                fprintf(stderr, "]\n");
                SLCUtils_IF_ERR_BREAK(err = EXIT_FAILURE,
                    "Invalid label \"%s\" @ %s,%d.\n", scanner, __FILE__, __LINE__);
            }
            scanner += strlen(scanner) + 1;
            notEnd = (*scanner != '\0');
        } while (notEnd);
    } while (0);
    return err;
}

/*!
\brief set bool array to the value.
*/
void SLCUtils_SetBools(bool value, int szBools, bool* bools)
{
    for (int i = 0; i < szBools; i++) bools[i] = value;
}
