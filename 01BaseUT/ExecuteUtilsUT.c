#include "SLC/Utils.h"
#include "SLC/Log.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static const char* const RefWords[] = {
    "Word1", "Word1A", "Word1AB", "Hello", "World"
};
static bool ParseResults[SLCUtils_ArraySize(RefWords)];

static const char Concatinated0[] = "Hello:word1:word1aB";
static const char Concatinated1[] = "Word1A:Word1AB:Hell0";
static const char Concatinated2[] = "Word1A:Word1AB:Hello:Hello";
static const bool ParseResultsRef0[] = { true, false, true, true, false };

int ExecuteUtilsUT()
{
    int err = EXIT_SUCCESS;
    do {
        // FindWord
        int szRefWords = SLCUtils_ArraySize(RefWords);
        int found = SLCUtils_FindWord(szRefWords, RefWords, "word1");
        assert(found == 0);
        found = SLCUtils_FindWord(szRefWords, RefWords, "WORD1A");
        assert(found == 1);
        found = SLCUtils_FindWord(szRefWords, RefWords, "wORLD");
        assert(found == 4);
        found = SLCUtils_FindWord(szRefWords, RefWords, "Word1B");
        assert(found == -1);

        // ParseConcatinatedLabels
        SLCUtils_SetBools(false, szRefWords, ParseResults);
        err = SLCUtils_ParseConcatinatedLabels(szRefWords, RefWords, ':', Concatinated0, ParseResults);
        assert(err == EXIT_SUCCESS);
        for (int i = 0; i < SLCUtils_ArraySize(ParseResults); i++)
        {
            assert(ParseResults[i] == ParseResultsRef0[i]);
        }
        err = SLCUtils_ParseConcatinatedLabels(szRefWords, RefWords, ':', Concatinated1, ParseResults);
        assert(err != EXIT_SUCCESS);
        err = SLCUtils_ParseConcatinatedLabels(szRefWords, RefWords, ':', Concatinated2, ParseResults);
        assert(err != EXIT_SUCCESS);
        err = EXIT_SUCCESS;
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}