#include "SLC/Utils.h"
#include "SLC/Log.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <alloca.h>
int ParseConcatinatedLabels(const char* concatinatedLabels);
int ExecuteSelected();

// Argument styles
// Style 1: Execute all test
// 01BaseUT.exe
// Style 2: Show help
// 01BaseUT.exe -h
// Style 3: Execute selected tests
// 01BaseUT.exe -st <concatinated_labels>
//  concatinated_labels: Array:DLink, Numbers, NumbersCopy:Array, etc.

static const char* HELP_MSG =
"[How to use 01BaseUT]\n"
"Style 1: All tests are executed.\n"
"  $ 01BaseUT.exe\n"
"Style 2: Show help message.\n"
"  $ 01BaseUT.exe -h\n"
"Style 3: Selected tests are executed.\n"
"  $ 01BaseUT.exe -st <concatinated_labels>"
"   <concatinated_labels> is Array:DLink, Numbers, NumbersCopy:Array:Log, etc.\n"
"   <concatinated_labels> is case-insensitive, label order has no influence.\n";

static const char* FUNC_LABELS[] = {
    "Array", "DLink", "Log", "Numbers", "NumbersCopy", "Utils"
};

static const int FUNC_LABEL_COUNT = sizeof(FUNC_LABELS)/sizeof(FUNC_LABELS[0]);
static bool SubCommandsHave[sizeof(FUNC_LABELS)/sizeof(FUNC_LABELS[0])];

int main(int argc, const char* argv[])
{
    int err = EXIT_SUCCESS;
    do {
        if (argc == 1) // no command line option
            SLCUtils_SetBools(true, FUNC_LABEL_COUNT, SubCommandsHave);
        else if ((argc == 2) && (0 == strcmp("-h", argv[1])))
            printf(HELP_MSG); // command line option is "-h"
        else if ((argc == 3) && (0 == strcmp("-st", argv[1])))
        { // command line option is "-st <concatinated_labels>"
            err = SLCUtils_ParseConcatinatedLabels(FUNC_LABEL_COUNT, FUNC_LABELS, ':', argv[2], SubCommandsHave);
            SLCUtils_IF_ERR_BREAK(err, "Command line error!!!\n");
        }
        else
        { // invalid command line
            SLCUtils_IF_ERR_BREAK((err = EXIT_FAILURE), "Command line error!!!\n");
        }
        SLCLog_Sink = stdout;
        SLCLog_Level = SLCLog_LevelALL;
        err = ExecuteSelected();
    } while (0);
    if (err)
    {
        fprintf(stderr, HELP_MSG);
    }
    return err;
}

// prototypes of sub unit tests
extern int ExecuteUtilsUT();
extern int ExecuteArrayUT();
extern int ExecuteDLinkUT();
extern int ExecuteLogUT();
extern int ExecuteNumbersUT();
extern int ExecuteNumbersCopyUT();

typedef int (*SUBUNITTEST_VOID)();
static const SUBUNITTEST_VOID subtests[] = {
    ExecuteUtilsUT, ExecuteArrayUT, ExecuteDLinkUT, ExecuteLogUT,
    ExecuteNumbersUT, ExecuteNumbersCopyUT
};

int ExecuteSelected()
{
    int err = EXIT_SUCCESS;
    for (int i = 0; i < FUNC_LABEL_COUNT; i++)
    {
        if (!SubCommandsHave[i]) continue;
        err = subtests[i]();
        if (err)
        {
            fprintf(stderr, "Fail in %s() @ %s,%d\n", FUNC_LABELS[i], __FILE__, __LINE__);
            break;
        }
    }
    return err;
}
