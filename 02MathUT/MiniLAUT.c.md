# Control
```
{
    "out": "MiniLAUT.c",
    "vtypes": ["r32", "r64", "c64", "c128"],
    "rtypes": ["r32", "r64", "r32", "r64"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
```
#include "SLC/MiniLA.h"
#include "SLC/Numbers.h"
#include "SLC/NumbersCopy.h"
#include "SLC/errno.h"
#include "SLC/Log.h"
#include <stdio.h>
#include <stdlib.h>
```
## SLCr32_t test data
```
#pragma region r32_test_data
// source values
static const SLCr32_t r32src0[] = {
    1.0f, 2.0f, 2.5f,
    1.2f, -10.0f, -5.5f
};
static const SLCr32_t r32src1[] = {
    -1.0f, -2.0f, -2.0f,
    -1.5f, 10.5f, 6.0f
};
static const SLCr32_t r32src2[] = {
    -1.0f, -2.0f, -2.0f, -4.0f,
    2.0f, 2.2f, -3.3f, -5.0f,
    1.5f, -1.5f, -2.2f, -5.0f
};
static const SLCr32_t r32src3[] = {
    -1.0f, -2.0f, -2.0f,
    -4.0f, 2.0f, 2.2f,
    -3.3f, -5.0f, 1.5f
};
static const SLCr32_t r32right[] = {
    1.0f, 1.2f,
    2.0f, -10.0f,
    2.5f, -5.5f
};
// 5x3 matrix
static const SLCr32_t r32leftOD[] = {
    -1.0f, -2.0f, -2.0f,
    -4.0f, 2.0f, 2.2f,
    -3.3f, -5.0f, 1.5f,
    -4.0f, 2.2f, 2.0f,
    -3.3f, 1.5f, -5.0f,
};
// solution for overly determined linear equation
static const SLCr32_t* r32solutionOD = r32right;

static const SLCr32_t r32scale0 = 1.1f, r32scale1 = -1.5f;

// test reference values
// src0 + src1
static const SLCr32_t r32_src0_plus_src1[] = {
    0.0f, 0.0f, 0.5f,
    -0.3f, 0.5f, 0.5f
};
// scale0 * src0 + scale1 * src1
static const SLCr32_t r32_scale0_src0_plus_scale1_src1[] = {
    2.6f, 5.2f, 5.75f,
    3.57f, -26.75f, -15.05f
};
// scale0 * src0
static const SLCr32_t r32_scale0_src0[] = {
    1.1f, 2.2f, 2.75f,
    1.32f, -11.0f, -6.05f
};
// src0 * src2
static const SLCr32_t r32_src0_src2[] = {
    6.75f, -1.35f, -14.1f, -26.5f,
    -29.45f, -16.15f, 42.7f, 72.7f
};
#pragma endregion r32_test_data
```
## SLCr64_t test data
```
#pragma region r64_test_data
// source values
static const SLCr64_t r64src0[] = {
    1.0, 2.0, 2.5,
    1.2, -10.0, -5.5
};
static const SLCr64_t r64src1[] = {
    -1.0, -2.0, -2.0,
    -1.5, 10.5, 6.0f
};
static const SLCr64_t r64src2[] = {
    -1.0, -2.0, -2.0, -4.0,
    2.0, 2.2, -3.3, -5.0,
    1.5, -1.5, -2.2, -5.0
};
static const SLCr64_t r64src3[] = {
    -1.0, -2.0, -2.0,
    -4.0, 2.0, 2.2,
    -3.3, -5.0, 1.5
};
static const SLCr64_t r64right[] = {
    1.0, 1.2,
    2.0, -10.0,
    2.5, -5.5
};
// 5x3 matrix
static const SLCr64_t r64leftOD[] = {
    -1.0, -2.0, -2.0,
    -4.0, 2.0, 2.2,
    -3.3, -5.0, 1.5,
    -4.0, 2.2, 2.0,
    -3.3, 1.5, -5.0
};
// solution for overly determined linear equation
static const SLCr64_t* r64solutionOD = r64right;

static const SLCr64_t r64scale0 = 1.1, r64scale1 = -1.5f;

// test reference values
// src0 + src1
static const SLCr64_t r64_src0_plus_src1[] = {
    0.0, 0.0, 0.5,
    -0.3, 0.5, 0.5
};
// scale0 * src0 + scale1 * src1
static const SLCr64_t r64_scale0_src0_plus_scale1_src1[] = {
    2.6, 5.2, 5.75,
    3.57, -26.75, -15.05
};
// scale0 * src0
static const SLCr64_t r64_scale0_src0[] = {
    1.1, 2.2, 2.75,
    1.32, -11.0, -6.05
};
// src0 * src2
static const SLCr64_t r64_src0_src2[] = {
    6.75, -1.35, -14.1, -26.5,
    -29.45, -16.15, 42.7, 72.7
};
#pragma endregion r64_test_data
```
## SLCc64_t test data
```
#pragma region c64_test_data
// source values
static const SLCc64_t c64src0[] = {
    CMPLXF(1.0f, 2.0f), CMPLXF(2.5f,-2.2f), CMPLXF(-0.5f,0.5f),
    CMPLXF(1.2f, -10.0f), CMPLXF(-5.5f, -2.5f), CMPLXF(2.5f,2.2f)
};
static const SLCc64_t c64src1[] = {
    CMPLXF(-1.0f, -2.0f), CMPLXF(-2.0f, 0.0f), CMPLXF(-0.0f,0.5f),
    CMPLXF(-1.5f, 10.5f), CMPLXF(6.0f, 0.0f), CMPLXF(0.0f,0.2f)
};
static const SLCc64_t c64src2[] = {
    CMPLXF(-1.0f, -2.0f), CMPLXF(-2.0f, -4.0f), CMPLXF(-1.0f, -2.0f), CMPLXF(-2.0f, -4.0f),
    CMPLXF(2.0f, 2.2f), CMPLXF(-3.3f, -5.0f), CMPLXF(2.0f, -2.2f), CMPLXF(3.3f, -5.0f),
    CMPLXF(1.5f, -1.5f), CMPLXF(-2.2f, -5.0f), CMPLXF(-1.5f, -1.5f), CMPLXF(2.2f, -5.0f),
};
static const SLCc64_t c64src3[] = {
    CMPLXF(-1.0f, -2.0f), CMPLXF(-2.0f, -4.0f), CMPLXF(2.0f, 2.2f),
    CMPLXF(-4.0f, 2.0f), CMPLXF(2.2f, -3.3f), CMPLXF(-5.0f, 1.5f),
    CMPLXF(-3.3f, -5.0f), CMPLXF(1.5f, -1.0f), CMPLXF(-2.0f, -2.0f)
};
static const SLCc64_t c64right[] = {
    CMPLXF(1.0f, 2.0f), CMPLXF(1.2f, -10.0f),
    CMPLXF(2.5f, -2.2f), CMPLXF(-5.5f, -2.5f),
    CMPLXF(-0.5f, 0.5f), CMPLXF(2.5f, 2.2f)
};
// 5x3 matrix
static const SLCc64_t c64leftOD[] = {
    CMPLXF(-1.0f, -2.0f), CMPLXF(-2.0f, -4.0f), CMPLXF(2.0f, 2.2f),
    CMPLXF(-4.0f, 2.0f), CMPLXF(2.2f, -3.3f), CMPLXF(-5.0f, 1.5f),
    CMPLXF(-3.3f, -5.0f), CMPLXF(1.5f, -1.0f), CMPLXF(-2.0f, -2.0f),
    CMPLXF(-4.0f, 2.0f), CMPLXF(-5.0f, 1.5f), CMPLXF(2.2f, -3.3f),
    CMPLXF(-3.3f, -5.0f), CMPLXF(-2.0f, -2.0f), CMPLXF(1.5f, -1.0f)
};
// solution for overly determined linear equation
static const SLCc64_t* c64solutionOD = c64right;

static const SLCc64_t c64scale0 = CMPLXF(0.1f,1.1f), c64scale1 = CMPLXF(-1.5f,0.1f);

// test reference values
// src0 + src1
static const SLCc64_t c64_src0_plus_src1[] = {
    CMPLXF(0.0f, 0.0f), CMPLXF(0.5f,-2.2f), CMPLXF(-0.5f,1.0f),
    CMPLXF(-0.3f,0.5f), CMPLXF(0.5f,-2.5f), CMPLXF(2.5f,2.4f)
};
// scale0 * src0 + scale1 * src1
static const SLCc64_t c64_scale0_src0_plus_scale1_src1[] = {
    CMPLXF(-0.4f,4.2f), CMPLXF(5.67f,2.33f), CMPLXF(-0.65f,-1.25f),
    CMPLXF(12.32f,-15.58f), CMPLXF(-6.8f, -5.7f), CMPLXF(-2.19f,2.67f)
};
// scale0 * src0
static const SLCc64_t c64_scale0_src0[] = {
    CMPLXF(-2.1f,1.3f), CMPLXF(2.67f,2.53f), CMPLXF(-0.6f,-0.5f),
    CMPLXF(11.12f,0.32f), CMPLXF(2.2f,-6.3f), CMPLXF(-2.17f,2.97f)
};
// src0 * src2
static const SLCc64_t c64_src0_src2[] = {
    CMPLXF(12.84f,-1.4f), CMPLXF(-9.65f,-11.84f), CMPLXF(4.66f,-13.9f), CMPLXF(4.65f,-24.16f),
    CMPLXF(-19.65f,-9.95f), CMPLXF(-31.25f,33.61f), CMPLXF(-38.15f,7.65f), CMPLXF(-56.55f,26.79f)
};
#pragma endregion c64_test_data
```
## SLCc128_t test data
```
#pragma region c128_test_data
// source values
static const SLCc128_t c128src0[] = {
    CMPLX(1.0, 2.0), CMPLX(2.5,-2.2), CMPLX(-0.5,0.5),
    CMPLX(1.2, -10.0), CMPLX(-5.5, -2.5), CMPLX(2.5,2.2)
};
static const SLCc128_t c128src1[] = {
    CMPLX(-1.0, -2.0), CMPLX(-2.0, 0.0), CMPLX(-0.0,0.5),
    CMPLX(-1.5, 10.5), CMPLX(6.0, 0.0), CMPLX(0.0,0.2)
};
static const SLCc128_t c128src2[] = {
    CMPLX(-1.0, -2.0), CMPLX(-2.0, -4.0), CMPLX(-1.0, -2.0), CMPLX(-2.0, -4.0),
    CMPLX(2.0, 2.2), CMPLX(-3.3, -5.0), CMPLX(2.0, -2.2), CMPLX(3.3, -5.0),
    CMPLX(1.5, -1.5), CMPLX(-2.2, -5.0), CMPLX(-1.5, -1.5), CMPLX(2.2, -5.0),
};
static const SLCc128_t c128src3[] = {
    CMPLX(-1.0, -2.0), CMPLX(-2.0, -4.0), CMPLX(2.0, 2.2),
    CMPLX(-4.0, 2.0), CMPLX(2.2, -3.3), CMPLX(-5.0, 1.5),
    CMPLX(-3.3, -5.0), CMPLX(1.5, -1.0), CMPLX(-2.0, -2.0)
};
static const SLCc128_t c128right[] = {
    CMPLX(1.0, 2.0), CMPLX(1.2, -10.0),
    CMPLX(2.5, -2.2), CMPLX(-5.5, -2.5),
    CMPLX(-0.5, 0.5), CMPLX(2.5, 2.2)
};
// 5x3 matrix
static const SLCc128_t c128leftOD[] = {
    CMPLX(-1.0, -2.0), CMPLX(-2.0, -4.0), CMPLX(2.0, 2.2),
    CMPLX(-4.0, 2.0), CMPLX(2.2, -3.3), CMPLX(-5.0, 1.5),
    CMPLX(-3.3, -5.0), CMPLX(1.5, -1.0), CMPLX(-2.0, -2.0),
    CMPLX(-4.0, 2.0), CMPLX(-5.0, 1.5), CMPLX(2.2, -3.3),
    CMPLX(-3.3, -5.0), CMPLX(-2.0, -2.0), CMPLX(1.5, -1.0)
};
// solution for overly determined linear equation
static const SLCc128_t* c128solutionOD = c128right;

static const SLCc128_t c128scale0 = CMPLX(0.1,1.1), c128scale1 = CMPLX(-1.5,0.1);

// test reference values
// src0 + src1
static const SLCc128_t c128_src0_plus_src1[] = {
    CMPLX(0.0, 0.0), CMPLX(0.5,-2.2), CMPLX(-0.5,1.0),
    CMPLX(-0.3,0.5), CMPLX(0.5,-2.5), CMPLX(2.5,2.4)
};
// scale0 * src0 + scale1 * src1
static const SLCc128_t c128_scale0_src0_plus_scale1_src1[] = {
    CMPLX(-0.4,4.2), CMPLX(5.67,2.33), CMPLX(-0.65,-1.25),
    CMPLX(12.32,-15.58), CMPLX(-6.8, -5.7), CMPLX(-2.19,2.67)
};
// scale0 * src0
static const SLCc128_t c128_scale0_src0[] = {
    CMPLX(-2.1,1.3), CMPLX(2.67,2.53), CMPLX(-0.6,-0.5),
    CMPLX(11.12,0.32), CMPLX(2.2,-6.3), CMPLX(-2.17,2.97)
};
// src0 * src2
static const SLCc128_t c128_src0_src2[] = {
    CMPLX(12.84,-1.4), CMPLX(-9.65,-11.84), CMPLX(4.66,-13.9), CMPLX(4.65,-24.16),
    CMPLX(-19.65,-9.95), CMPLX(-31.25,33.61), CMPLX(-38.15,7.65), CMPLX(-56.55,26.79)
};
#pragma endregion c128_test_data
```
# Generic
## matrix sizes
```
#pragma region <VTYPE>_test_functions
static const SLC4i16_t <VTYPE>matsize2x3 = { sizeof(SLC<VTYPE>_t), 3, 2, 1 };
static const SLC4i16_t <VTYPE>matsize2x4 = { sizeof(SLC<VTYPE>_t), 4, 2, 1 };
static const SLC4i16_t <VTYPE>matsize4x2 = { sizeof(SLC<VTYPE>_t), 2, 4, 1 };
static const SLC4i16_t <VTYPE>matsize3x2 = { sizeof(SLC<VTYPE>_t), 2, 3, 1 };
static const SLC4i16_t <VTYPE>matsize3x4 = { sizeof(SLC<VTYPE>_t), 4, 3, 1 };
static const SLC4i16_t <VTYPE>matsize4x3 = { sizeof(SLC<VTYPE>_t), 3, 4, 1 };
static const SLC4i16_t <VTYPE>matsize3x3 = { sizeof(SLC<VTYPE>_t), 3, 3, 1 };
static const SLC4i16_t <VTYPE>matsize3x6 = { sizeof(SLC<VTYPE>_t), 6, 3, 1 };
static const SLC4i16_t <VTYPE>matsize3x5 = { sizeof(SLC<VTYPE>_t), 5, 3, 1 };
static const SLC4i16_t <VTYPE>matsize5x2 = { sizeof(SLC<VTYPE>_t), 2, 5, 1 };
static const SLC4i16_t <VTYPE>matsize2x5 = { sizeof(SLC<VTYPE>_t), 5, 2, 1 };
```
## add two matrices
```
static SLCerrno_t <VTYPE>AddUT() 
{
    SLCerrno_t err = EXIT_SUCCESS;
    const SLCArray_t src0 = { {{sizeof(SLC<VTYPE>_t), 3, 2, 1}}, { <VTYPE>src0 } };
    const SLCArray_t src1 = { {{sizeof(SLC<VTYPE>_t), 3, 2, 1}}, { <VTYPE>src1 } };
    SLCPArray_t dst = SLCArray_Alloc(src0.cont.i16);
    do {
        SLCMat<VTYPE>_Add(dst, &src0, &src1);
        const SLC<ITYPE>_t element_count = SLCArray_MatRows(dst) * SLCArray_MatColumns(dst);
        for (SLC<ITYPE>_t i = 0; i < element_count; i++) 
        {
            if (!SLC<VTYPE>_areequal(<VTYPE>_src0_plus_src1[i], dst->data.<VTYPE>[i], SLC<VTYPE>_stdtol))
            {
                err = EXIT_FAILURE;
                SLCLog<VTYPE>_ERR(err, "<VTYPE>_src0_plus_src1", "dst->data.<VTYPE>", i,
                    <VTYPE>_src0_plus_src1, dst->data.<VTYPE>);
                break;
            }
        }
    } while (0);
    SLCArray_SafeFree(dst);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## scaling and add two matrices
```
static SLCerrno_t <VTYPE>ScaleAddUT() 
{
    SLCerrno_t err = EXIT_SUCCESS;
    const SLCArray_t src0 = { {{sizeof(SLC<VTYPE>_t), 3, 2, 1}}, { <VTYPE>src0 } };
    const SLCArray_t src1 = { {{sizeof(SLC<VTYPE>_t), 3, 2, 1}}, { <VTYPE>src1 } };
    SLCPArray_t dst = SLCArray_Alloc(src0.cont.i16);
    do {
        SLCMat<VTYPE>_ScaleAdd(dst, &src0, &<VTYPE>scale0, &src1, &<VTYPE>scale1);
        const SLC<ITYPE>_t element_count = SLCArray_MatRows(dst) * SLCArray_MatColumns(dst);
        for (SLC<ITYPE>_t i = 0; i < element_count; i++) 
        {
            if (!SLC<VTYPE>_areequal(<VTYPE>_scale0_src0_plus_scale1_src1[i], dst->data.<VTYPE>[i], SLC<VTYPE>_stdtol))
            {
                err = EXIT_SUCCESS;
                SLCLog<VTYPE>_ERR(err, "<VTYPE>_scale0_src0_plus_scale1_src1", "dst->data.<VTYPE>", i,
                    <VTYPE>_scale0_src0_plus_scale1_src1, dst->data.<VTYPE>);
                break;
            }
        }
    } while (0);
    SLCArray_SafeFree(dst);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## Scaling a matrix
```
static SLCerrno_t <VTYPE>ScaleUT() 
{
    SLCerrno_t err = EXIT_SUCCESS;
    const SLCArray_t src0 = { {{sizeof(SLC<VTYPE>_t), 3, 2, 1}}, { <VTYPE>src0 } };
    SLCPArray_t dst = SLCArray_Alloc(src0.cont.i16);
    do {
        SLCMat<VTYPE>_Scale(dst, &src0, &<VTYPE>scale0);
        SLC<ITYPE>_t element_count = SLCArray_MatRows(dst) * SLCArray_MatColumns(dst);
        for (SLC<ITYPE>_t i = 0; i < element_count; i++)
        {
            if (!SLC<VTYPE>_areequal(<VTYPE>_scale0_src0[i], dst->data.<VTYPE>[i], SLC<VTYPE>_stdtol))
            {
                err = EXIT_FAILURE;
                SLCLog<VTYPE>_ERR(err, "<VTYPE>_scale0_src0", "dst->data.<VTYPE>",
                    i, <VTYPE>_scale0_src0, dst->data.<VTYPE>);
                break;
            }
        }
    } while (0);
    SLCArray_SafeFree(dst);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## multiply two matrices
```
static SLCerrno_t <VTYPE>MultiplyUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    const SLCArray_t src0 = { {{sizeof(SLC<VTYPE>_t), 3, 2, 1}}, { <VTYPE>src0 } };
    const SLCArray_t src2 = { {{sizeof(SLC<VTYPE>_t), 4, 3, 1}}, { <VTYPE>src2 } };
    SLCPArray_t dst = SLCArray_Alloc(<VTYPE>matsize2x4);
    SLCPArray_t work = SLCArray_Alloc(<VTYPE>matsize4x3);
    do {
        SLCMat<VTYPE>_Multiply(dst, &src0, &src2, work);
        SLC<ITYPE>_t element_count = SLCArray_MatRows(dst) * SLCArray_MatColumns(dst);
        for (SLC<ITYPE>_t i = 0; i < element_count; i++)
        {
            if (!SLC<VTYPE>_areequal(<VTYPE>_src0_src2[i], dst->data.<VTYPE>[i], SLC<VTYPE>_stdtol))
            {
                err = EXIT_FAILURE;
                SLCLog<VTYPE>_ERR(err, "<VTYPE>_src0_src2", "dst->data.<VTYPE>",
                    i, <VTYPE>_src0_src2, dst->data.<VTYPE>);
                break;
            }
        }
    } while (0);
    SLCArray_SafeFree(dst);
    SLCArray_SafeFree(work);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## Invert a matrix
```
static SLCerrno_t <VTYPE>IsIdentity3x3(SLCPCArray_t mat)
{
    const SLC<VTYPE>_t _0 = SLC<VTYPE>_units[0], _1 = SLC<VTYPE>_units[1];
    SLCerrno_t err = (3 == SLCArray_MatRows(mat)) && (3 == SLCArray_MatColumns(mat)) ?
        EXIT_SUCCESS : SLC_EVALMISMATCH;
    const SLC<VTYPE>_t* element_ptr = mat->data.<VTYPE>;
    for (SLC<ITYPE>_t row = 0; row < 3; row++)
    {
        for (SLC<ITYPE>_t column = 0; column < 3; column++, element_ptr++)
        {
            const SLC<VTYPE>_t refval = (row == column) ? _1 : _0;
            if (!SLC<VTYPE>_areequal(refval, *element_ptr, SLC<VTYPE>_stdtol))
            {
                err = SLC_EVALMISMATCH;
                // SLCLog_ERR(err, "(row,column) = (%d,%d) @ %s,%d\n",
                //     row, column, __FUNCTION__, __LINE__);
                break;
            }
        }
        if (err) break;
    }
    return err;
}

static SLCerrno_t <VTYPE>InvertUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLCArray_t src3 = { {{ sizeof(SLC<VTYPE>_t), 3, 3, 1 }}, { <VTYPE>src3 }};
    SLCPArray_t dst = SLCArray_Alloc(<VTYPE>matsize3x3),
        work = SLCArray_Alloc(<VTYPE>matsize3x6),
        work_mult = SLCArray_Alloc(<VTYPE>matsize3x3),
        imat = SLCArray_Alloc(<VTYPE>matsize3x3);
    do {
        err = SLCMat<VTYPE>_Inv(dst, &src3, work);
        SLCMat<VTYPE>_Multiply(imat, &src3, dst, work_mult);
        // SLCMat<VTYPE>_Print(SLCLog_Sink, "imat = ", imat, "");
        if (EXIT_SUCCESS != (err = <VTYPE>IsIdentity3x3(imat))) break;
    } while (0);
    SLCArray_SafeFree(dst);
    SLCArray_SafeFree(work);
    SLCArray_SafeFree(work_mult);
    SLCArray_SafeFree(imat);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## Solve a fully determined equation
```
static SLCerrno_t <VTYPE>CompareMat(SLCPCArray_t matref, SLCPCArray_t mattest)
{
    SLCerrno_t err = ((SLCArray_MatRows(matref) == SLCArray_MatRows(mattest)) &&
                    (SLCArray_MatColumns(matref) == SLCArray_MatColumns(mattest))) ?
                    EXIT_SUCCESS : SLC_EVALMISMATCH;
    if (err) return err;
    const SLC<VTYPE>_t *refptr = matref->data.<VTYPE>, *testptr = mattest->data.<VTYPE>;
    for (SLCi16_t row = 0; row < SLCArray_MatRows(matref); row++)
    {
        for (SLCi16_t column = 0; column < SLCArray_MatColumns(matref); column++, refptr++, testptr++)
        {
            if (!SLC<VTYPE>_areequal(*refptr, *testptr, SLC<VTYPE>_stdtol))
            {
                err = SLC_EVALMISMATCH;
                SLCLog_ERR(err, "Value mismatch (row, column) = (%d, %d) @ %s, %d\n",
                    row, column, __FUNCTION__, __LINE__);
                break;
            }
        }
        if (err) break;
    }
    return err;
}

static SLCerrno_t <VTYPE>SolveUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLCArray_t left = {{{sizeof(SLC<VTYPE>_t), 3, 3, 1}}, { <VTYPE>src3 }},
        right = {{{sizeof(SLC<VTYPE>_t), 2, 3, 1}}, { <VTYPE>right }};
    SLCPArray_t work = SLCArray_Alloc(<VTYPE>matsize3x5),
        dst = SLCArray_Alloc(<VTYPE>matsize3x2),
        work_mult = SLCArray_Alloc(<VTYPE>matsize2x3),
        right2 = SLCArray_Alloc(right.cont.i16);
    do {
        SLCMat<VTYPE>_Solve(dst, &left, &right, work);
        SLCMat<VTYPE>_Multiply(right2, &left, dst, work_mult);
        if (EXIT_SUCCESS != (err = <VTYPE>CompareMat(&right, right2))) break;
    } while (0);
    SLCArray_SafeFree(work);
    SLCArray_SafeFree(dst);
    SLCArray_SafeFree(work_mult);
    SLCArray_SafeFree(right2);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## Solve an overly determined equation
```
static SLCerrno_t <VTYPE>SolveODUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLCArray_t left = {{{sizeof(SLC<VTYPE>_t), 3, 5, 1}}, { <VTYPE>leftOD }};
    SLCArray_t ref_solution = {{{sizeof(SLC<VTYPE>_t), 2, 3, 1}}, { <VTYPE>solutionOD }};
    SLCPArray_t right = SLCArray_Alloc(<VTYPE>matsize5x2),
        work_mult = SLCArray_Alloc(<VTYPE>matsize2x3),
        dst = SLCArray_Alloc(ref_solution.cont.i16);
    SLCMat_SolveODWorkMatSet_t wkset = { NULL, NULL, NULL, NULL, NULL, NULL };
    do {
        // create RHS
        SLCMat<VTYPE>_Multiply(right, &left, &ref_solution, work_mult);

        // create working matrix set
        SLCMat_InitSolveODWorkMatSet(&left, right, &wkset);

        // solve equation
        err = SLCMat<VTYPE>_SolveOD(dst, &left, right, &wkset);
        if (err)
        {
            SLCLog_ERR(err, "Fail in SLCMat<VTYPE>_SolveOD() @ %s,%d\n", __FUNCTION__, __LINE__);
            break;
        }

        // compare results
        err = <VTYPE>CompareMat(&ref_solution, dst);
        if (err)
        {
            SLCLog_ERR(err, "Value mismatcin @ %s,%d\n", __FUNCTION__, __LINE__);
            break;
        }
    } while (0);
    SLCArray_SafeFree(right);
    SLCArray_SafeFree(work_mult);
    SLCArray_SafeFree(dst);
    SLCMat_DestroySolveODWorkMatSet(&wkset);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## Simplified API to solve overly determined equation
```
static SLCerrno_t <VTYPE>EasySolveODUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLCArray_t left = {{{sizeof(SLC<VTYPE>_t), 3, 5, 1}}, { <VTYPE>leftOD }};
    SLCArray_t ref_solution = {{{sizeof(SLC<VTYPE>_t), 2, 3, 1}}, { <VTYPE>solutionOD }};
    SLCPArray_t right = SLCArray_Alloc(<VTYPE>matsize5x2),
        work_mult = SLCArray_Alloc(<VTYPE>matsize2x3),
        dst = SLCArray_Alloc(ref_solution.cont.i16);
    do {
        // create RHS
        SLCMat<VTYPE>_Multiply(right, &left, &ref_solution, work_mult);

        // solve
        err = SLCMat<VTYPE>_EasySolveOD(dst, &left, right);
        if (err)
        {
            SLCLog_ERR(err, "Fail in SLCMat<VTYPE>_EasySolveOD() @ %s,%d\n", __FUNCTION__, __LINE__);
            break;
        }

        // compare results
        err = <VTYPE>CompareMat(&ref_solution, dst);
        if (err)
        {
            SLCLog_ERR(err, "Value mismatcin @ %s,%d\n", __FUNCTION__, __LINE__);
            break;
        }
    } while (0);
    SLCArray_SafeFree(right);
    SLCArray_SafeFree(work_mult);
    SLCArray_SafeFree(dst);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## Submain function harnessing the tests above
```
SLCerrno_t <VTYPE>MiniLAUT() 
{
    SLCerrno_t err = EXIT_SUCCESS;
    do {
        err = <VTYPE>AddUT();
        if (err) break;
        err = <VTYPE>ScaleAddUT();
        if (err) break;
        err = <VTYPE>ScaleUT();
        if (err) break;
        err = <VTYPE>MultiplyUT();
        if (err) break;
        err = <VTYPE>InvertUT();
        if (err) break;
        err = <VTYPE>SolveUT();
        if (err) break;
        err = <VTYPE>SolveODUT();
        if (err) break;
        err = <VTYPE>EasySolveODUT();
        if (err) break;
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
#pragma endregion <VTYPE>_test_functions
```
# Foot
```
SLCerrno_t MiniLAUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = r32MiniLAUT()))
        {
            SLCLog_ERR(err, " in r32MiniLAUT @ %s,%d\n", __FILE__, __LINE__);
            break;
        }

        if (EXIT_SUCCESS != (err = r64MiniLAUT()))
        {
            SLCLog_ERR(err, " in r64MiniLAUT @ %s,%d\n", __FILE__, __LINE__);
            break;
        }

        if (EXIT_SUCCESS != (err = c64MiniLAUT()))
        {
            SLCLog_ERR(err, " in c64MiniLAUT @ %s,%d\n", __FILE__, __LINE__);
            break;
        }

        if (EXIT_SUCCESS != (err = c128MiniLAUT()))
        {
            SLCLog_ERR(err, " in c128MiniLAUT @ %s,%d\n", __FILE__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
