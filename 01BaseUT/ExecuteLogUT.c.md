# Control
```
{
    "out": "ExecuteLogUT.c",
    "vtypes": ["r32", "r64", "c64", "c128"],
    "rtypes": ["r32", "r64", "r32", "r64"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
```
#include "SLC/Numbers.h"
#include "SLC/NumbersCopy.h"
#include "SLC/Log.h"
#include <stdio.h>
#include <stdlib.h>
```
# Generic
```
#pragma region <VTYPE>_functions
#pragma endregion <VTYPE>_functions
```
# Foot
```
void LogAll()
{
    static const int numbers[] = { 100, 10, 1 };
    SLCLog_ERR(EXIT_FAILURE, "Error code is %s. Numbers are [%d, %d, %d]\n", "EXIT_FAILURE",
        numbers[0], numbers[1], numbers[2]);
    SLCLog_INF("Numbers are [%d, %d, %d]\n", numbers[0], numbers[1], numbers[2]);
    SLCLog_DBG("Numbers are [%d, %d, %d]\n", numbers[0], numbers[1], numbers[2]);
    SLCLog_PERF("Numbers are [%d, %d, %d]\n", numbers[0], numbers[1], numbers[2]);
    SLCLog_TEST("Numbers are [%d, %d, %d]\n", numbers[0], numbers[1], numbers[2]);
}

int ExecuteLogUT()
{
    SLCLog_Level_t backup = SLCLog_Level; // backup loglevel
    int err = EXIT_SUCCESS;
    do {
        // LevelNONE
        SLCLog_Level = SLCLog_LevelNONE;
        printf("LogLevel is NONE.\n");
        LogAll();

        // LevelERR
        SLCLog_Level = SLCLog_LevelERR;
        printf("LogLevel is ERR.\n");
        LogAll();

        // LevelINF
        SLCLog_Level = SLCLog_LevelINF;
        printf("LogLevel is INF.\n");
        LogAll();

        // LevelDBG
        SLCLog_Level = SLCLog_LevelDBG;
        printf("LogLevel is DBG.\n");
        LogAll();

        // LevelPERF
        SLCLog_Level = SLCLog_LevelPERF;
        printf("LogLevel is PERF.\n");
        LogAll();

        // LevelTEST
        SLCLog_Level = SLCLog_LevelTEST;
        printf("LogLevel is TEST.\n");
        LogAll();

        // LevelAll
        SLCLog_Level = backup;
        printf("LogLevel is ALL.\n");
        LogAll();
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
