# Control
```
{
    "out": "../include/SLC/Log.h",
    "vtypes": ["r32", "r64", "c64", "c128"]
}
```
# Head
```
#if !defined(SLCLog__H_)
#define SLCLog__H_
#include "SLC/Numbers.h"
#include "SLC/errno.h"
#include "SLC/ExIO.h"
#include <stdio.h>
#include <pthread.h>
#pragma region Loggging_related_definitions
typedef enum {
    SLCLog_LevelNONE = 0, // disable output
    SLCLog_LevelERR = 1, // output only ERR
    SLCLog_LevelINF = 2, // output ERR and INF
    SLCLog_LevelDBG = 4, // output ERR, INF, and DBG
    SLCLog_LevelPERF = 8, // output performance test message
    SLCLog_LevelTEST = 16, // output test message
    SLCLog_LevelALL = 31, // enable all log levels.
} SLCLog_Level_t;

// Log-sink file.
// NULL disables logging. Default value is stdout.
#if !defined(_01BASE_LOG_C)
extern FILE* SLCLog_Sink;
extern SLCLog_Level_t SLCLog_Level;
extern pthread_spinlock_t SLCLog_Lock;
#endif

// initialize/deinitialize global variables

// write timestamp and log-level
void SLCLog_WriteHeader(SLCLog_Level_t loglevel);

void SLCLog_WriteErrHeader(SLCerrno_t err);

// Error log output
#define SLCLog_ERR(err, ...) if ((SLCLog_Sink) && (SLCLog_Level & SLCLog_LevelERR)) { \
    SLCLog_WriteErrHeader(err); \
    fprintf(SLCLog_Sink, __VA_ARGS__); \
}

// __var : evaluation target variable
// __err : error number variable is set by this macro.
// __file : file path; usually filled with __FILE__ macro.
// __func : function name; usually filled with __func__ macro.
// __line : line number where the error occurs. usually filled with __LINE__ macro.
#define SLC_IfNullERR(__var, __err, __file, __func, __line) if (NULL == (__var)) { \
    __err = ENOMEM; \
    SLCLog_ERR(err, "@ %s, %s, %d\n", __file, __func, __line); break; }

// Info log output
#define SLCLog_INF(...) if ((SLCLog_Sink) && (SLCLog_Level & SLCLog_LevelINF)) { \
    SLCLog_WriteHeader(SLCLog_LevelINF); fprintf(SLCLog_Sink, __VA_ARGS__); }

// Debug log output
#define SLCLog_DBG(...) if ((SLCLog_Sink) && (SLCLog_Level & SLCLog_LevelDBG)) { \
    SLCLog_WriteHeader(SLCLog_LevelDBG); fprintf(SLCLog_Sink, __VA_ARGS__); }

// Performance test log output
#define SLCLog_PERF(...) if ((SLCLog_Sink) && (SLCLog_Level & SLCLog_LevelPERF)) { \
    SLCLog_WriteHeader(SLCLog_LevelPERF); fprintf(SLCLog_Sink, __VA_ARGS__); }

// Test log output
#define SLCLog_TEST(...) if ((SLCLog_Sink) && (SLCLog_Level & SLCLog_LevelTEST)) { \
    SLCLog_WriteHeader(SLCLog_LevelTEST); fprintf(SLCLog_Sink, __VA_ARGS__); }
#pragma endregion
#pragma region test_utility_macros
// standard test method signatures
typedef struct {
    SLCi32_t settings;
    const void* data;
} SLC_TestArgs_t, *SLC_PTestArgs_t;
typedef const SLC_TestArgs_t *SLC_PCTestArgs_t;
typedef SLCerrno_t (*SLC_TESTMETHOD)(SLCi32_t settings);
typedef SLCerrno_t (*SLC_TESTMETHOD2)(SLC_PCTestArgs_t args);

// test method calling macro
#define SLC_TEST_ABORT_ON_FAIL  1
#define SLC_test(__errno, __method_to_test, __setting, __func, __line) \
    __errno = __method_to_test(__setting); \
    if (__errno) { \
        SLCLog_ERR(__errno, "setting=%d(0x%x), func=%s, line=%d\n", __setting, __setting, __func, __line); \
        if (SLC_TEST_ABORT_ON_FAIL) break; }
#define SLC_test2(__errno, __method_to_test, __pvsetting, __func, __line) \
    __errno = __method_to_test(__pvsetting); \
    if (__errno) { \
        SLCLog_ERR(__errno, "func=%s, line=%d\n", __func, __line); \
        if (SLC_TEST_ABORT_ON_FAIL) break; }
#define SLC_testend(__errno, __func, __line) \
    SLCLog_TEST("errno=0x%x(%d) @ %s,%d\n", __errno, __errno, __func, __line)
#pragma endregion
#pragma regioon stopwatch_functions
// initialize stopwatch.
void SLC_Stopwatch_Init(SLCsize_t channels, SLCsize_t caption_length);

// Release the resources initialized by SLC_Stopwatch_Init.
void SLC_Stopwatch_Destroy();

// Start time measurement using a selected channel.
SLCi32_t SLC_Stopwatch_Start(const char* caption);

// Measure and record time.
void SLC_Stopwatch_Measure(SLCi32_t channel);

// Release the channel.
void SLC_Stopwatch_Release(SLCi32_t channel);

// Difference between two timespec instances
void SLC_Timespec_A_minus_B(struct timespec* a_minus_b, struct timespec* a, struct timespec* b);

/*!
\brief error log for SLCr32_t number array test
\param err [in] error code like EXIT_FAILURE, SLC_ESINGULAR, etc.
\param refname [in] variable name of reference number array
\param testname [in] variable name of number array under test
\param index [in] index of the arrays where an error occured
\param refarray [in] reference number array
\param testarray [in] number array under test
*/
void SLCLogr32_ERR(SLCerrno_t err,
    const char* refname, const char* testname,
    SLCi32_t index, const SLCr32_t* refarray, const SLCr32_t* testarray
);

void SLCLogr64_ERR(SLCerrno_t err,
    const char* refname, const char* testname,
    SLCi32_t index, const SLCr64_t* refarray, const SLCr64_t* testarray
);

void SLCLogc64_ERR(SLCerrno_t err,
    const char* refname, const char* testname,
    SLCi32_t index, const SLCc64_t* refarray, const SLCc64_t* testarray
);

void SLCLogc128_ERR(SLCerrno_t err,
    const char* refname, const char* testname,
    SLCi32_t index, const SLCc128_t* refarray, const SLCc128_t* testarray
);
#pragma endregion
```
# Generic
```
#pragma region comparison_of_SLC<VTYPE>_t_numbers
#define SLC<VTYPE>_abssum2(__a, __b) (SLC<VTYPE>_abs(__a) + SLC<VTYPE>_abs(__b))
#define SLC<VTYPE>_absdiff(__a, __b) SLC<VTYPE>_abs((__a) - (__b))
#define SLC<VTYPE>_relabsdiff(__a, __b) SLC<VTYPE>_absdiff(__a, __b)/SLC<VTYPE>_abssum2(__a, __b)
#define SLC<VTYPE>_areequal(__a, __b, __tol) \
    (((SLC<VTYPE>_abs(__a) < __tol) || (SLC<VTYPE>_abs(__b) < __tol)) ? \
    (SLC<VTYPE>_absdiff(__a, __b) < __tol) : (SLC<VTYPE>_relabsdiff(__a, __b) < __tol))
#define SLC<VTYPE>Pnt_areequal(__p0, __p1, __tol) ( \
    SLC<VTYPE>_areequal((__p0)[0]/(__p0)[3], (__p1)[0]/(__p1)[3], __tol) && \
    SLC<VTYPE>_areequal((__p0)[1]/(__p0)[3], (__p1)[1]/(__p1)[3], __tol) && \
    SLC<VTYPE>_areequal((__p0)[2]/(__p0)[3], (__p1)[2]/(__p1)[3], __tol))
#pragma endregion
```
# Foot
```
#endif
```