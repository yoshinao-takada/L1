# Control
```
{
    "out": "NLSLUT.c",
    "vtypes": ["r32", "r64", "c64", "c128"],
    "rtypes": ["r32", "r64", "r32", "r64"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
## Test objective
1) Reconfirm LMS solver more rigorously than `MiniLAUT`.
2) Confirm `02Math/NLSL`.

1) Reconfirm LMS solver more rigorously than `MiniLAUT`.
    * 3rd order polynomial curve fitting
2) Confirm `02Math/NLSL`.
    * a 2x2 matrix to the power of 2 and 3,
    * a 3x3 matrix to the power of 2 and the trace of the original matrix.

## includes
```
#include "SLC/Numbers.h"
#include "SLC/NumbersCopy.h"
#include "SLC/NLSL.h"
#include "SLC/MiniLA.h"
#include "SLC/Log.h"
#include "SLC/errno.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <memory.h>
```
## test data
### common test data
```
static const SLCi32_t PolyOrder = 3;
static const SLCi32_t PolyCoeffCount = 4;
static const SLCi32_t XPointCount = 20;
```
### test data for r32_t
```
static const SLC4r32_t r32PolyCoeff = { 0.5f, -1.0f, -0.3f, 0.1f };
static const SLCr32_t
    r32XBegin0 = -2.0f, r32XBegin1 = -2.2f,
    r32XStep0 = 0.15f, r32XStep1 = 0.33f;
static const SLCr32_t* r32Mat2x2 = r32PolyCoeff;
static const SLC2r32_t r32DiagonalOffsets = { 0.2f, -0.3f };
```
### test data for r64_t
```
static const SLC4r64_t r64PolyCoeff = { 0.5, -1.0, -0.3, 0.1 };
static const SLCr64_t
    r64XBegin0 = -2.0, r64XBegin1 = -2.2,
    r64XStep0 = 0.15, r64XStep1 = 0.33;
static const SLCr64_t* r64Mat2x2 = r64PolyCoeff;
static const SLC2r64_t r64DiagonalOffsets = { 0.2, -0.3 };
```
### test data for c64_t
```
static const SLC4c64_t c64PolyCoeff = {
    CMPLXF(0.5f,-0.45f), CMPLXF(-1.0f,0.95f),
    CMPLXF(-0.3f,-0.27f), CMPLXF(0.1f,0.0f) };
static const SLCc64_t
    c64XBegin0 = CMPLXF(-2.0f,-1.5f), c64XBegin1 = CMPLXF(-2.2f, 1.5f),
    c64XStep0 = CMPLXF(0.15f,0.15f), c64XStep1 = CMPLXF(0.33f,-0.2f);
static const SLCc64_t* c64Mat2x2 = c64PolyCoeff;
static const SLC2c64_t c64DiagonalOffsets = { CMPLXF(0.2f, 0.0f), CMPLXF(-0.3f, -1.0f) };
```
### test data for c128_t
```
static const SLC4c128_t c128PolyCoeff = {
    CMPLX(0.5,-0.45), CMPLX(-1.0,0.95),
    CMPLX(-0.3,-0.27), CMPLX(0.1,0.0) };
static const SLCc128_t
    c128XBegin0 = CMPLX(-2.0,-1.5), c128XBegin1 = CMPLX(-2.2, 1.5),
    c128XStep0 = CMPLX(0.15,0.15), c128XStep1 = CMPLX(0.33,-0.2);
static const SLCc128_t* c128Mat2x2 = c128PolyCoeff;
static const SLC2c128_t c128DiagonalOffsets = { CMPLX(0.2, 0.0), CMPLX(-0.3, -1.0) };
```
# Generic
## Overly determined linear equation: 3rd order polynomial fitting
```
#pragma region <VTYPE>_functions
// calculate test polynomial value for independent variable x.
static SLC<VTYPE>_t <VTYPE>PolyFit_PolyValue(SLC<VTYPE>_t x)
{
    SLC<VTYPE>_t value = SLC<VTYPE>_units[0];
    SLC<ITYPE>_t order_index = PolyCoeffCount;
    for (SLC<ITYPE>_t i = 0; i < PolyCoeffCount; i++)
    {
        --order_index;
        value = value * x + <VTYPE>PolyCoeff[order_index];
    }
    return value;
}

static void <VTYPE>PolyFit_CreateTestRHS(SLCPArray_t rhs)
{
    SLC<VTYPE>_t x = <VTYPE>XBegin0, xstep = <VTYPE>XStep0;
    SLC<ITYPE>_t count2 = XPointCount / 2;
    SLC<ITYPE>_t i = 0;
    for (; i < count2; i++, x += xstep)
    {
        rhs->data.<VTYPE>[i] = <VTYPE>PolyFit_PolyValue(x);
    }
    x = <VTYPE>XBegin1, xstep = <VTYPE>XStep1;
    for (; i < XPointCount; i++, x += xstep) 
    {
        rhs->data.<VTYPE>[i] = <VTYPE>PolyFit_PolyValue(x);
    }
}

static void <VTYPE>PolyFit_CreateXPowers(SLC<VTYPE>_t* XpowN, SLC<VTYPE>_t x)
{
    XpowN[0] = SLC<VTYPE>_units[1];
    XpowN[1] = XpowN[0] * x;
    XpowN[2] = XpowN[1] * x;
    XpowN[3] = XpowN[2] * x;
}

static void <VTYPE>PolyFit_CreateTestLHS(SLCPArray_t lhs)
{
    SLC<VTYPE>_t x = <VTYPE>XBegin0, xstep = <VTYPE>XStep0;
    SLC<ITYPE>_t count2 = XPointCount / 2;
    SLC<VTYPE>_t* lhs_elements = lhs->data.<VTYPE>;
    SLC<ITYPE>_t i = 0;
    for (; i < count2; i++, x += xstep, lhs_elements += PolyCoeffCount)
    {
        <VTYPE>PolyFit_CreateXPowers(lhs_elements, x);
    }
    x = <VTYPE>XBegin1, xstep = <VTYPE>XStep1;
    for (; i < XPointCount; i++, x += xstep, lhs_elements += PolyCoeffCount)
    {
        <VTYPE>PolyFit_CreateXPowers(lhs_elements, x);
    }
}

static SLCerrno_t <VTYPE>SolveODUT()
{
    const SLCi16_t left_size[] = { sizeof(SLC<VTYPE>_t), PolyCoeffCount, XPointCount, 1 };
    const SLCi16_t right_size[] = { sizeof(SLC<VTYPE>_t), 1, XPointCount, 1 };
    const SLCi16_t x_size[] = { sizeof(SLC<VTYPE>_t), 1, (SLCi16_t)PolyCoeffCount, 1 };
    SLCPArray_t left = NULL, right = NULL, xretrieved = NULL;
    SLCMat_SolveODWorkMatSet_t wkset = { NULL, NULL, NULL, NULL, NULL, NULL };
    SLCerrno_t err = EXIT_SUCCESS;
    do {
        left = SLCArray_Alloc(left_size);
        right = SLCArray_Alloc(right_size);
        xretrieved = SLCArray_Alloc(x_size);
        if (!left || !right || !xretrieved)
        {
            err = ENOMEM;
            SLCLog_ERR(err, "Insufficient memory @ %s,%d\n", __FILE__, __LINE__);
            break;
        }
        SLCMat_InitSolveODWorkMatSet(left, right, &wkset);
        <VTYPE>PolyFit_CreateTestRHS(right);
        <VTYPE>PolyFit_CreateTestLHS(left);
        err = SLCMat<VTYPE>_SolveOD(xretrieved, left, right, &wkset);
        if (err)
        {
            SLCLog_ERR(err, "Fail in SLCMat<VTYPE>_SolveOD() @ %s,%d\n",
                __FILE__, __LINE__);
            break;
        }
        for (SLC<ITYPE>_t i = 0; i < PolyCoeffCount; i++)
        {
            if (!SLC<VTYPE>_areequal(<VTYPE>PolyCoeff[i], xretrieved->data.<VTYPE>[i], SLC<VTYPE>_bigtol))
            {
                err = SLC_EVALMISMATCH;
                SLCLog_ERR(err, 
                    "Value mismatch, <VTYPE>PolyCoeff[%d]=%f, xretrieved[%d]=%f @ %s,%d\n",
                    i, <VTYPE>PolyCoeff[i], i, xretrieved->data.<VTYPE>[i], __FILE__, __LINE__);
                break;
            }
        }
    } while (0);
    SLCArray_SafeFree(left);
    SLCArray_SafeFree(right);
    SLCMat_DestroySolveODWorkMatSet(&wkset);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
```
#pragma endregion <VTYPE>_functions
```
## Nonlinear equation: A 2x2 matrix to the power of 2 and 3
```
static SLCerrno_t <VTYPE>Objective00(
    SLC<VTYPE>_t* y, SLCi32_t cy,
    const SLC<VTYPE>_t* x, SLCi32_t cx,
    const SLC<VTYPE>_t* params, SLCi32_t cc
) {
    SLCerrno_t err = EXIT_SUCCESS;
    const SLCi16_t unitsize = sizeof(SLC<VTYPE>_t);
    const SLC4i16_t matsize = { unitsize, 2, 2, 1 };
    SLCPArray_t
        xoffset = SLCArray_Alloca(matsize),
        xpow2 = SLCArray_Alloca(matsize),
        xpow3 = SLCArray_Alloca(matsize),
        work = SLCArray_Alloca(matsize);
    do {
        SLC<ITYPE>_t matbytesize = unitsize*4;
        memcpy(xoffset->data.u8, x, matbytesize);
        xoffset->data.<VTYPE>[0] += params[0];
        xoffset->data.<VTYPE>[2] += params[1];
        SLCMat<VTYPE>_Multiply(xpow2, xoffset, xoffset, work);
        SLCMat<VTYPE>_Multiply(xpow3, xpow2, xoffset, work);
        memcpy(y, xpow2->data.u8, matbytesize);
        memcpy(y + matbytesize, xpow3->data.u8, matbytesize);
    } while (0);
    return err;
}
```
## Test Harness for <VTYPE>_t
```
static SLCerrno_t <VTYPE>NLSLUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    do {
        err = <VTYPE>SolveODUT();
        if (err) break;
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
# Foot
## Test Harness for all base number types
```
SLCerrno_t NLSLUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = r32NLSLUT())) break;
        if (EXIT_SUCCESS != (err = r64NLSLUT())) break;
        if (EXIT_SUCCESS != (err = c64NLSLUT())) break;
        if (EXIT_SUCCESS != (err = c128NLSLUT())) break;
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
