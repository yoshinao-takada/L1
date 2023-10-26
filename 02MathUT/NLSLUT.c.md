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
    * a 2x2 matrix $\text{M}_1$ is unknown, A known value $\text{M}_\text{K}$ is given for
    ${\text{M}_1}^2+{\text{M}_1}^3$;<br/>i.e. ${\text{M}_1}^2+{\text{M}_1}^3-\text{M}_\text{K} = 0$ in standard
    nonlinear equation form.
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
#pragma region test_data
static const SLCi32_t PolyOrder = 3;
static const SLCi32_t PolyCoeffCount = 4;
static const SLCi32_t XPointCount = 20;
```
### test data for r32_t
```
#pragma region r32_test_data
static const SLC4r32_t r32PolyCoeff = { 0.5f, -1.0f, -0.3f, 0.1f };
static const SLCr32_t
    r32XBegin0 = -2.0f, r32XBegin1 = -2.2f,
    r32XStep0 = 0.15f, r32XStep1 = 0.33f;
static const SLCr32_t* r32Mat2x2 = r32PolyCoeff;
static const SLC2r32_t r32DiagonalOffsets = { 0.2f, -0.3f };
#pragma endregion r32_test_data
```
### test data for r64_t
```
#pragma region r64_test_data
static const SLC4r64_t r64PolyCoeff = { 0.5, -1.0, -0.3, 0.1 };
static const SLCr64_t
    r64XBegin0 = -2.0, r64XBegin1 = -2.2,
    r64XStep0 = 0.15, r64XStep1 = 0.33;
static const SLCr64_t* r64Mat2x2 = r64PolyCoeff;
static const SLC2r64_t r64DiagonalOffsets = { 0.2, -0.3 };
#pragma endregion r64_test_data
```
### test data for c64_t
```
#pragma region c64_test_data
static const SLC4c64_t c64PolyCoeff = {
    CMPLXF(0.5f,-0.45f), CMPLXF(-1.0f,0.95f),
    CMPLXF(-0.3f,-0.27f), CMPLXF(0.1f,0.0f) };
static const SLCc64_t
    c64XBegin0 = CMPLXF(-2.0f,-1.5f), c64XBegin1 = CMPLXF(-2.2f, 1.5f),
    c64XStep0 = CMPLXF(0.15f,0.15f), c64XStep1 = CMPLXF(0.33f,-0.2f);
static const SLCc64_t* c64Mat2x2 = c64PolyCoeff;
static const SLC2c64_t c64DiagonalOffsets = { CMPLXF(0.2f, 0.0f), CMPLXF(-0.3f, -1.0f) };
#pragma endregion c64_test_data
```
### test data for c128_t
```
#pragma region c128_test_data
static const SLC4c128_t c128PolyCoeff = {
    CMPLX(0.5,-0.45), CMPLX(-1.0,0.95),
    CMPLX(-0.3,-0.27), CMPLX(0.1,0.0) };
static const SLCc128_t
    c128XBegin0 = CMPLX(-2.0,-1.5), c128XBegin1 = CMPLX(-2.2, 1.5),
    c128XStep0 = CMPLX(0.15,0.15), c128XStep1 = CMPLX(0.33,-0.2);
static const SLCc128_t* c128Mat2x2 = c128PolyCoeff;
static const SLC2c128_t c128DiagonalOffsets = { CMPLX(0.2, 0.0), CMPLX(-0.3, -1.0) };
#pragma endregion c128_test_data
#pragma endregion test_data
```
# Generic
## Overly determined linear equation: 3rd order polynomial fitting
```
#pragma region <VTYPE>_functions
#pragma region <VTYPE>_Overly_determined_linear_equation
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
#pragma endregion <VTYPE>_Overly_determined_linear_equation
```
## Nonlinear equation: A 2x2 matrix to the power of 2 and 3
Details of the problem are described in [NLSL Sample 0](NLSLSample0.md).
### Objective and Jacobian: context and its memory management
```
#pragma region <VTYPE>_Objective_and_Jacobian
typedef struct <VTYPE>MatPower2And3 {
    SLCPArray_t M1, M2, dM1dx0, dM1dx1, dM1dx2, dM1dx3;
    SLCPArray_t work[8];
} <VTYPE>MatPower2And3_t, *<VTYPE>PMatPower2And3_t;

static void <VTYPE>MatPower2And3_Init(<VTYPE>PMatPower2And3_t context)
{
    SLC4i16_t matsize = { sizeof(SLC<VTYPE>_t), 2, 2, 1 };
    context->M1 = SLCArray_Alloc(matsize);
    context->M2 = SLCArray_Alloc(matsize);
    context->dM1dx0 = SLCArray_Alloc(matsize);
    context->dM1dx1 = SLCArray_Alloc(matsize);
    context->dM1dx2 = SLCArray_Alloc(matsize);
    context->dM1dx3 = SLCArray_Alloc(matsize);
    // zero clear all dM1dxN.
    SLC<VTYPE>_copy(context->dM1dx0->data.<VTYPE>, 1, SLC<VTYPE>_units, 0, 4);
    SLC<VTYPE>_copy(context->dM1dx1->data.<VTYPE>, 1, SLC<VTYPE>_units, 0, 4);
    SLC<VTYPE>_copy(context->dM1dx2->data.<VTYPE>, 1, SLC<VTYPE>_units, 0, 4);
    SLC<VTYPE>_copy(context->dM1dx3->data.<VTYPE>, 1, SLC<VTYPE>_units, 0, 4);
    // set 1 elements in dM1dxN.
    context->dM1dx0->data.<VTYPE>[0] = 
    context->dM1dx1->data.<VTYPE>[1] = 
    context->dM1dx2->data.<VTYPE>[2] = 
    context->dM1dx3->data.<VTYPE>[3] = SLC<VTYPE>_units[1];
    for (SLC<ITYPE>_t i = 0; i < SLCarraysize(context->work); i++)
    {
        context->work[i] = SLCArray_Alloc(matsize);
    }
}

static void <VTYPE>MatPower2And3_Destroy(<VTYPE>PMatPower2And3_t context)
{
    SLCArray_SafeFree(context->M1);
    SLCArray_SafeFree(context->M2);
    SLCArray_SafeFree(context->dM1dx0);
    SLCArray_SafeFree(context->dM1dx1);
    SLCArray_SafeFree(context->dM1dx2);
    SLCArray_SafeFree(context->dM1dx3);
    for (SLC<ITYPE>_t i = 0; i < SLCarraysize(context->work); i++)
    {
        SLCArray_SafeFree(context->work[i]);
    }
}
```
### Objective and Jacobian: Test parameter initializer
```
static void <VTYPE>MatPower2And3_CreateParams(<VTYPE>PMatPower2And3_t context, SLC<VTYPE>_t* params)
{
    context->M1->data.<VTYPE>[0] = <VTYPE>Mat2x2[0] + <VTYPE>DiagonalOffsets[0];
    context->M1->data.<VTYPE>[1] = <VTYPE>Mat2x2[1];
    context->M1->data.<VTYPE>[2] = <VTYPE>Mat2x2[2];
    context->M1->data.<VTYPE>[3] = <VTYPE>Mat2x2[3] + <VTYPE>DiagonalOffsets[1];
    SLCArray_t M2 = { context->M1->cont, params + 2 };
    SLCArray_t M3 = { context->M1->cont, params + 6 };
    SLCMat<VTYPE>_Multiply(&M2, context->M1, context->M1, context->work[0]);
    SLCMat<VTYPE>_Multiply(&M3, &M2, context->M1, context->work[0]);
    params[0] = <VTYPE>DiagonalOffsets[0];
    params[1] = <VTYPE>DiagonalOffsets[1];
    // negate params[2..9]
    SLCBLAS<VTYPE>_ScaleAss(M2.data.<VTYPE>, SLC<VTYPE>_units + 2, 4);
    SLCBLAS<VTYPE>_ScaleAss(M3.data.<VTYPE>, SLC<VTYPE>_units + 2, 4);
}
```
### Objective and Jacobian: Objective function
```
static SLCerrno_t <VTYPE>Objective00(
    SLC<VTYPE>_t* y, SLCi32_t cy,
    const SLC<VTYPE>_t* x, SLCi32_t cx,
    const SLC<VTYPE>_t* params, SLCi32_t cc,
    void* context
) {
    SLCerrno_t err = EXIT_SUCCESS;
    <VTYPE>PMatPower2And3_t ctx = (<VTYPE>PMatPower2And3_t)context;
    ctx->M1->data.<VTYPE>[0] = x[0] + params[0];
    ctx->M1->data.<VTYPE>[1] = x[1];
    ctx->M1->data.<VTYPE>[2] = x[2];
    ctx->M1->data.<VTYPE>[3] = x[3] + params[1];
    SLCArray_t M2 = { ctx->M1->cont, {(void*)y} };
    SLCArray_t M3 = { ctx->M1->cont, {(void*)(y + 4)} };
    do {
        SLCMat<VTYPE>_Multiply(&M2, ctx->M1, ctx->M1, ctx->work[0]);
        memcpy(ctx->M2->data.<VTYPE>, M2.data.<VTYPE>, SLCprod3(ctx->M2->cont.i16));
        SLCMat<VTYPE>_Multiply(&M3, &M2, ctx->M1, ctx->work[0]);
        SLCBLAS<VTYPE>_AddAss(y, params + 2, cy);
    } while (0);
    return err;
}
```
### Objective and Jacobian: Jacobian
```
// Jacobian column common
static SLCerrno_t <VTYPE>Jcommon(
    SLC<VTYPE>_t* y, SLCi32_t cy,
    const SLC<VTYPE>_t* x, SLCi32_t cx,
    const SLC<VTYPE>_t* params, SLCi32_t cc,
    void* context,
    SLCPCArray_t dM1dx
) {
    <VTYPE>PMatPower2And3_t ctx = (<VTYPE>PMatPower2And3_t)context;
    // work[0] = M1 * dM1dx, work[1] = dM1dx * M1,
    // *y = M1 * dM1dx + dM1dx * M1
    SLCMat<VTYPE>_Multiply(ctx->work[0], ctx->M1, dM1dx, ctx->work[7]);
    SLCMat<VTYPE>_Multiply(ctx->work[1], dM1dx, ctx->M1, ctx->work[7]);
    SLCBLAS<VTYPE>_Add(y, ctx->work[0]->data.<VTYPE>, ctx->work[1]->data.<VTYPE>, 4);
    // work[2] = M1 * M1 * dM1dx, work[3] = M1 * dM1dx * M1, work[4] = dM1dx * M1 * M1
    // *(y + 4) = M1 * M1 * dM1dx + M1 * dM1dx * M1 + dM1dx * M1 * M1
    SLCMat<VTYPE>_Multiply(ctx->work[2], ctx->M1, ctx->work[0], ctx->work[7]);
    SLCMat<VTYPE>_Multiply(ctx->work[3], ctx->M1, ctx->work[1], ctx->work[7]);
    SLCMat<VTYPE>_Multiply(ctx->work[4], ctx->work[1], ctx->M1, ctx->work[7]);
    SLCBLAS<VTYPE>_Add(y + 4, ctx->work[2]->data.<VTYPE>, ctx->work[3]->data.<VTYPE>, 4);
    SLCBLAS<VTYPE>_AddAss(y + 4, ctx->work[4]->data.<VTYPE>, 4);
    return EXIT_SUCCESS;
}
// Jacobian column 0
static SLCerrno_t <VTYPE>J0(
    SLC<VTYPE>_t* y, SLCi32_t cy,
    const SLC<VTYPE>_t* x, SLCi32_t cx,
    const SLC<VTYPE>_t* params, SLCi32_t cc,
    void* context
) {
    SLCerrno_t err = EXIT_SUCCESS;
    <VTYPE>PMatPower2And3_t ctx = (<VTYPE>PMatPower2And3_t)context;
    SLCPCArray_t dM1dx = ctx->dM1dx0;
    return <VTYPE>Jcommon(y, cy, x, cx, params, cc, context, dM1dx);
}

// Jacobian column 1
static SLCerrno_t <VTYPE>J1(
    SLC<VTYPE>_t* y, SLCi32_t cy,
    const SLC<VTYPE>_t* x, SLCi32_t cx,
    const SLC<VTYPE>_t* params, SLCi32_t cc,
    void* context
) {
    SLCerrno_t err = EXIT_SUCCESS;
    <VTYPE>PMatPower2And3_t ctx = (<VTYPE>PMatPower2And3_t)context;
    SLCPCArray_t dM1dx = ctx->dM1dx1;
    return <VTYPE>Jcommon(y, cy, x, cx, params, cc, context, dM1dx);
}
// Jacobian column 2
static SLCerrno_t <VTYPE>J2(
    SLC<VTYPE>_t* y, SLCi32_t cy,
    const SLC<VTYPE>_t* x, SLCi32_t cx,
    const SLC<VTYPE>_t* params, SLCi32_t cc,
    void* context
) {
    SLCerrno_t err = EXIT_SUCCESS;
    <VTYPE>PMatPower2And3_t ctx = (<VTYPE>PMatPower2And3_t)context;
    SLCPCArray_t dM1dx = ctx->dM1dx2;
    return <VTYPE>Jcommon(y, cy, x, cx, params, cc, context, dM1dx);
}
// Jacobian column 3
static SLCerrno_t <VTYPE>J3(
    SLC<VTYPE>_t* y, SLCi32_t cy,
    const SLC<VTYPE>_t* x, SLCi32_t cx,
    const SLC<VTYPE>_t* params, SLCi32_t cc,
    void* context
) {
    SLCerrno_t err = EXIT_SUCCESS;
    <VTYPE>PMatPower2And3_t ctx = (<VTYPE>PMatPower2And3_t)context;
    SLCPCArray_t dM1dx = ctx->dM1dx3;
    return <VTYPE>Jcommon(y, cy, x, cx, params, cc, context, dM1dx);
}
#pragma endregion <VTYPE>_Objective_and_Jacobian
```
### Execute Testing Gauss-Newton Solver
```
SLCerrno_t <VTYPE>NLSLGNMat2x2Pow2And3UT()
{
    const SLC<VTYPE>_t _0 = SLC<VTYPE>_units[0], _1 = SLC<VTYPE>_units[1];
    SLCerrno_t err = EXIT_SUCCESS;
    <VTYPE>MatPower2And3_t context;
    const SLC<ITYPE>_t cx = 4, cy = 8, cc = 10;
    const SLC<VTYPE>_t xIni[] = { _0, _0, _0, _0 };
    SLCPNLSLGNSolver<VTYPE>_t solver = NULL;
    do {
        <VTYPE>MatPower2And3_Init(&context);
        solver = SLCNLSLGNSolver<VTYPE>_New(cx, cy, cc);
        SLCPNLSLGNConf<VTYPE>_t conf = SLCNLSLGNSolver<VTYPE>_Conf(solver);
        conf->jacobian[0] = <VTYPE>J0;
        conf->jacobian[1] = <VTYPE>J1;
        conf->jacobian[2] = <VTYPE>J2;
        conf->jacobian[3] = <VTYPE>J3;
        SLCPNLSLConf<VTYPE>_t confbase = &conf->base;
        confbase->traceout = SLCLog_Sink;
        confbase->maxIter = 20;
        memcpy(confbase->xInitial, xIni, sizeof(xIni));
        <VTYPE>MatPower2And3_CreateParams(&context, confbase->cParams);
        confbase->normDxMax = SLC<VTYPE>_stdtol;
        confbase->normYMax = SLC<VTYPE>_stdtol;
        confbase->objective = <VTYPE>Objective00;
        confbase->context = &context;
        if (EXIT_SUCCESS != (err = SLCNLSLGNSolver<VTYPE>_Init(solver)))
        {
            SLCLog_ERR(err, "Fail in SLCNLSLGNSolver<VTYPE>_Init() @ %s,%d\n", __FILE__, __LINE__);
            break;
        }
        if (EXIT_SUCCESS != (err = SLCNLSLGNSolver<VTYPE>_Execute(solver)))
        {
            SLCLog_ERR(err, "Fail in SLCNLSLGNSolver<VTYPE>_Execute() @ %s,%d\n", __FILE__, __LINE__);
            break;
        }
    } while (0);
    SLCNLSLGNSolver<VTYPE>_Delete(&solver);
    <VTYPE>MatPower2And3_Destroy(&context);
    SLC_testend(err, __FUNCTION__, __LINE__);
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
        err = <VTYPE>NLSLGNMat2x2Pow2And3UT();
        if (err) break;
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
#pragma endregion <VTYPE>_functions
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
