# Control
```
{
    "out": "ExecuteNumbersCopyUT.c",
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
#pragma region r32_constants
static const SLCr32_t r32src[] = { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f };
static const SLCr32_t r32src2[] = { -3.5f, -2.5f, -1.5f, -0.5f, 0.5f, 1.5f, 2.5f, 3.5f};
static const SLCr32_t r32ref0[] = { -3.5f, 0.0f, 0.0f, -0.5f, 0.0f, 0.0, 2.5f, 0.0f};
static const SLCr32_t r32ref[] = { 0.0f, 2.0f, 4.0f, 6.0f };
static const SLCr32_t r32ref2[] = { -3.5f, -0.5f, 2.5f };
#pragma endregion
#pragma region r64_constants
static const SLCr64_t r64src[] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 };
static const SLCr64_t r64src2[] = { -3.5, -2.5, -1.5, -0.5, 0.5, 1.5, 2.5, 3.5};
static const SLCr64_t r64ref0[] = { -3.5, 0.0, 0.0, -0.5, 0.0, 0.0, 2.5, 0.0};
static const SLCr64_t r64ref[] = { 0.0, 2.0, 4.0, 6.0 };
static const SLCr64_t r64ref2[] = { -3.5, -0.5, 2.5 };
#pragma endregion
#pragma region c64_constants
static const SLCc64_t c64src[] = {
    CMPLXF(0.0f,0.0f), CMPLXF(1.0f,1.0f), CMPLXF(2.0f,2.0f), CMPLXF(3.0f,3.0f),
    CMPLXF(4.0f,4.0f), CMPLXF(5.0f,5.0f), CMPLXF(6.0f,6.0f), CMPLXF(7.0f,7.0f)
};
static const SLCc64_t c64src2[] = {
    CMPLXF(-3.5f,-3.5f), CMPLXF(-2.5f,-2.5f), CMPLXF(-1.5f,-1.5f), CMPLXF(-0.5f,-0.5f),
    CMPLXF(0.5f,0.5f), CMPLXF(1.5f,1.5f), CMPLXF(2.5f,2.5f), CMPLXF(3.5f,3.5f)
};
static const SLCc64_t c64ref0[] = {
    CMPLXF(-3.5f,-3.5f), CMPLXF(0.0f,0.0f), CMPLXF(0.0f,0.0f), CMPLXF(-0.5f,-0.5f),
    CMPLXF(0.0f,0.0f), CMPLXF(0.0f,0.0f), CMPLXF(2.5f,2.5f), CMPLXF(0.0f,0.0f)
};
static const SLCc64_t c64ref[] = {
    CMPLXF(0.0f,0.0f), CMPLXF(2.0f,2.0f), CMPLXF(4.0f,4.0f), CMPLXF(6.0f,6.0f)
};
static const SLCc64_t c64ref2[] = {
    CMPLXF(-3.5f,-3.5f), CMPLXF(-0.5f,-0.5f), CMPLXF(2.5f,2.5f)
};
#pragma endregion
#pragma region r128_constants
static const SLCc128_t c128src[] = {
    CMPLX(0.0,0.0), CMPLX(1.0,1.0), CMPLX(2.0,2.0), CMPLX(3.0,3.0),
    CMPLX(4.0,4.0), CMPLX(5.0,5.0), CMPLX(6.0,6.0), CMPLX(7.0,7.0)
};
static const SLCc128_t c128src2[] = {
    CMPLX(-3.5,-3.5), CMPLX(-2.5,-2.5), CMPLX(-1.5,-1.5), CMPLX(-0.5,-0.5),
    CMPLX(0.5,0.5), CMPLX(1.5,1.5), CMPLX(2.5,2.5), CMPLX(3.5,3.5)
};
static const SLCc128_t c128ref0[] = {
    CMPLX(-3.5,-3.5), CMPLX(0.0,0.0), CMPLX(0.0,0.0), CMPLX(-0.5,-0.5),
    CMPLX(0.0,0.0), CMPLX(0.0,0.0), CMPLX(2.5,2.5), CMPLX(0.0,0.0)
};
static const SLCc128_t c128ref[] = {
    CMPLX(0.0,0.0), CMPLX(2.0,2.0), CMPLX(4.0,4.0), CMPLX(6.0,6.0)
};
static const SLCc128_t c128ref2[] = {
    CMPLX(-3.5,-3.5), CMPLX(-0.5,-0.5), CMPLX(2.5,2.5)
};
#pragma endregion
```
# Generic
```
#pragma region <VTYPE>_functions
static void ClearArray<VTYPE>(SLC<VTYPE>_t* a, SLC<ITYPE>_t size_a)
{
    const SLC<VTYPE>_t _0 = SLC<VTYPE>_units[0];
    for (SLC<ITYPE>_t i = 0; i < size_a; i++)
    {
        a[i] = _0;
    }
}
int SLC<VTYPE>_copyUT()
{
    int err = EXIT_SUCCESS;
    SLC<VTYPE>_t dest_buf[SLCarraysize(<VTYPE>src)];
    const SLC<ITYPE>_t size = SLCarraysize(<VTYPE>src);
    do {
        // dense copy
        ClearArray<VTYPE>(dest_buf, size);
        SLC<VTYPE>_copy(dest_buf, 1, <VTYPE>src, 1, size);
        for (SLC<ITYPE>_t i = 0; i < size; i++)
        {
            if (<VTYPE>src[i] != dest_buf[i])
            {
                err = EXIT_FAILURE;
                SLCLog_ERR(err, "value mismatch i=%d @ %s,%d\n", i, __FILE__, __LINE__);
                break;
            }
        }
        ClearArray<VTYPE>(dest_buf, size);
        SLC<VTYPE>_copy(dest_buf, 1, <VTYPE>src2, 1, size);
        for (SLC<ITYPE>_t i = 0; i < size; i++)
        {
            if (<VTYPE>src2[i] != dest_buf[i])
            {
                err = EXIT_FAILURE;
                SLCLog_ERR(err, "value mismatch i=%d @ %s,%d\n", i, __FILE__, __LINE__);
                break;
            }
        }

        // sparse copy
        ClearArray<VTYPE>(dest_buf, size);
        const SLC<ITYPE>_t copySize = 3;
        SLC<VTYPE>_copy(dest_buf, 3, <VTYPE>src2, 3, 3);
        for (SLC<ITYPE>_t i = 0; i < size; i++)
        {
            if (<VTYPE>ref0[i] != dest_buf[i])
            {
                err = EXIT_FAILURE;
                SLCLog_ERR(err, "value mismatch i=%d @ %s,%d\n", i, __FILE__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __FILE__, __LINE__);
    return err;
}

int SLC<VTYPE>_swapUT()
{
    const SLC<VTYPE>_t _0 = SLC<VTYPE>_units[0];
    int err = EXIT_SUCCESS;
    SLC<VTYPE>_t swap_buf0[SLCarraysize(<VTYPE>src)], swap_buf1[SLCarraysize(<VTYPE>src)];
    const SLC<ITYPE>_t size = SLCarraysize(<VTYPE>src);
    do {
        // dense swap
        // init swap_buf0 and swap_buf1
        ClearArray<VTYPE>(swap_buf0, size);
        ClearArray<VTYPE>(swap_buf1, size);
        SLC<VTYPE>_copy(swap_buf0, 1, <VTYPE>src, 1, size);
        SLC<VTYPE>_copy(swap_buf1, 1, <VTYPE>src2, 1, size);
        SLC<VTYPE>_swap(swap_buf0, 1, swap_buf1, 1, size);
        for (SLC<ITYPE>_t i = 0; i < size; i++)
        {
            if ((<VTYPE>src[i] != swap_buf1[i]) || (<VTYPE>src2[i] != swap_buf0[i]))
            {
                err = EXIT_FAILURE;
                SLCLog_ERR(err, "value mismatch i=%d @ %s,%d\n", i, __FILE__, __LINE__);
                break;
            }
        }

        // sparse swap
        ClearArray<VTYPE>(swap_buf0, size);
        ClearArray<VTYPE>(swap_buf1, size);
        // sparse swap 1st stage
        SLC<VTYPE>_copy(swap_buf0, 1, <VTYPE>src2, 1, size);
        SLC<VTYPE>_swap(swap_buf0, 3, swap_buf1, 3, 3);
        for (SLC<ITYPE>_t i = 0; i < size; i++)
        {
            if ((i % 3) == 0)
            { // swapped element
                if ((swap_buf1[i] != <VTYPE>src2[i]) || (swap_buf0[i] != _0))
                {
                    err = EXIT_FAILURE;
                    SLCLog_ERR(err, "value mismatch i=%d @ %s,%d\n", i, __FILE__, __LINE__);
                    break;
                }
            }
            else
            { // not swapped element
                if ((swap_buf1[i] != _0) || swap_buf0[i] != <VTYPE>src2[i])
                {
                    err = EXIT_FAILURE;
                    SLCLog_ERR(err, "value mismatch i=%d @ %s,%d\n", i, __FILE__, __LINE__);
                    break;
                }
            }
        }

        // sparse swap 2nd stage
        SLC<VTYPE>_swap(swap_buf0, 3, swap_buf1, 3, 3);
        for (SLC<ITYPE>_t i = 0; i < size; i++)
        {
            if ((swap_buf0[i] != <VTYPE>src2[i]) || (swap_buf1[i] != _0))
            {
                err = EXIT_FAILURE;
                SLCLog_ERR(err, "value mismatch i=%d @ %s,%d\n", i, __FILE__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}

int SLC<VTYPE>_gatherUT()
{
    int err = EXIT_SUCCESS;
    SLC<VTYPE>_t gathered_buf[3];
    const SLC<ITYPE>_t gathered_size = SLCarraysize(gathered_buf);
    do {
        ClearArray<VTYPE>(gathered_buf, gathered_size);
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}

int SLC<VTYPE>_scatterUT()
{
    int err = EXIT_SUCCESS;
    do {

    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}

int SLC<VTYPE>_allUT()
{
    int err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = SLC<VTYPE>_copyUT())) break;
        if (EXIT_SUCCESS != (err = SLC<VTYPE>_swapUT())) break;
        if (EXIT_SUCCESS != (err = SLC<VTYPE>_gatherUT())) break;
        if (EXIT_SUCCESS != (err = SLC<VTYPE>_scatterUT())) break;
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
#pragma endregion <VTYPE>_functions
```
# Foot
```
int ExecuteNumbersCopyUT()
{
    int err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = SLCr32_allUT())) break;
        if (EXIT_SUCCESS != (err = SLCr64_allUT())) break;
        if (EXIT_SUCCESS != (err = SLCc64_allUT())) break;
        if (EXIT_SUCCESS != (err = SLCc128_allUT())) break;
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
