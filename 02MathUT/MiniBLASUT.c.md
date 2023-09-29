# Control
```
{
    "out": "MiniBLASUT.c",
    "vtypes": ["r32", "r64", "c64", "c128"],
    "rtypes": ["r32", "r64", "r32", "r64"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
```
#include "SLC/MiniBLAS.h"
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
static const SLCr32_t
    r32_src0[] = { -1.8f, -1.0f, 0.0f, 1.2f, 1.6f },
    r32_src1[] = { 16.0f, 12.0f, 0.0f, -10.0f, -18.0f },
    r32_scale0 = 1.5f, r32_scale1 = -2.0f;

static const SLCr32_t
// src0 + src1
    r32_src0_plus_src1[] = { 14.2f, 11.0f, 0.0f, -8.8f, -16.4f },
// src0 + scale1 * src1
    r32_src0_plus_scale1_src1[] = { -33.8f, -25.0f, 0.0f, 21.2f, 37.6f },
// scale0 * src0 + scale1 * src1
    r32_scale0_src0_plus_scale1_src1[] = { -34.7f, -25.5f, 0.0f, 21.8f, 38.4f },
// { src0[i]*src1[i] (i = 0..4) }
    r32_src0_src1_ebe[] = { -28.8f, -12.0f, 0.0f, -12.0f, -28.8f },
// scale0 * src0
    r32_scale0_src0[] = { -2.7f, -1.5f, 0.0f, 1.8f, 2.4f },
// conj(src0)
    r32_conj_src0[] = { -1.8f, -1.0f, 0.0f, 1.2f, 1.6f };
static const SLCi32_t r32arraysize = SLCarraysize(r32_src0);
#pragma endregion r32_test_data
```
## SLCr64_t test data
```
#pragma region r32_test_data
static const SLCr64_t
    r64_src0[] = { -1.8, -1.0, 0.0, 1.2, 1.6 },
    r64_src1[] = { 16.0, 12.0, 0.0, -10.0, -18.0 },
    r64_scale0 = 1.5, r64_scale1 = -2.0;

static const SLCr64_t
// src0 + src1
    r64_src0_plus_src1[] = { 14.2, 11.0, 0.0, -8.8, -16.4 },
// src0 + scale1 * src1
    r64_src0_plus_scale1_src1[] = { -33.8, -25.0, 0.0, 21.2, 37.6 },
// scale0 * src0 + scale1 * src1
    r64_scale0_src0_plus_scale1_src1[] = { -34.7, -25.5, 0.0, 21.8, 38.4 },
// { src0[i]*src1[i] (i = 0..4) }
    r64_src0_src1_ebe[] = { -28.8, -12.0, 0.0, -12.0, -28.8 },
// scale0 * src0
    r64_scale0_src0[] = { -2.7, -1.5, 0.0, 1.8, 2.4 },
// conj(src0)
    r64_conj_src0[] = { -1.8, -1.0, 0.0, 1.2, 1.6 };
static const SLCi32_t r64arraysize = SLCarraysize(r64_src0);
#pragma endregion r64_test_data
```
## SLCc64_t test data
```
#pragma region c64_test_data
static  const SLCc64_t
    c64_src0[] = { CMPLXF(-1.8f,-1.0f), CMPLXF(0.0f,1.2f), CMPLXF(1.6f,-1.8f) },
    c64_src1[] = { CMPLXF(16.0f,12.0f), CMPLXF(0.0f,-10.0f), CMPLXF(-18.0f,16.0f) },
    c64_scale0 = CMPLXF(1.5f,-2.0f), c64_scale1 = CMPLXF(-2.0f,1.5f);

static  const SLCc64_t
// src0 + src1
    c64_src0_plus_src1[] = { CMPLXF(14.2f,11.0f), CMPLXF(0.0f,-8.8f), CMPLXF(-16.4f,14.2f) },
// src0 + scale1 * src1
    c64_src0_plus_scale1_src1[] = { CMPLXF(-51.8f,-1.0f), CMPLXF(15.0f,21.2f), CMPLXF(13.6f,-60.8f) },
// scale0 * src0 + scale1 * src1
    c64_scale0_src0_plus_scale1_src1[] = { CMPLXF(-54.7f,2.1f), CMPLXF(17.4f,21.8f), CMPLXF(10.8f,-64.9f) },
// { src0[i]*src1[i] (i = 0..4) }
    c64_src0_src1_ebe[] = { CMPLXF(-16.8f,-37.6f), CMPLXF(12.0f,0.0f), CMPLXF(0.0f,58.0f) },
// scale0 * src0
    c64_scale0_src0[] = { CMPLXF(-4.7f,2.1f), CMPLXF(2.4f,1.8f), CMPLXF(-1.2f,-5.9f) },
// conj(src0)
    c64_conj_src0[] = { CMPLXF(-1.8f,1.0f), CMPLXF(0.0f,-1.2f), CMPLXF(1.6f,1.8f) };
static const SLCi32_t c64arraysize = SLCarraysize(c64_src0);
#pragma endregion c64_test_data
```
## SLCc128_t test data
```
#pragma region c128_test_data
static  const SLCc128_t
    c128_src0[] = { CMPLX(-1.8,-1.0), CMPLX(0.0,1.2), CMPLX(1.6,-1.8) },
    c128_src1[] = { CMPLX(16.0,12.0), CMPLX(0.0,-10.0), CMPLX(-18.0,16.0) },
    c128_scale0 = CMPLX(1.5,-2.0), c128_scale1 = CMPLX(-2.0,1.5);

static  const SLCc128_t
// src0 + src1
    c128_src0_plus_src1[] = { CMPLX(14.2,11.0), CMPLX(0.0,-8.8), CMPLX(-16.4,14.2) },
// src0 + scale1 * src1
    c128_src0_plus_scale1_src1[] = { CMPLX(-51.8,-1.0), CMPLX(15.0,21.2), CMPLX(13.6,-60.8) },
// scale0 * src0 + scale1 * src1
    c128_scale0_src0_plus_scale1_src1[] = { CMPLX(-54.7,2.1), CMPLX(17.4,21.8), CMPLX(10.8,-64.9) },
// { src0[i]*src1[i] (i = 0..4) }
    c128_src0_src1_ebe[] = { CMPLX(-16.8,-37.6), CMPLX(12.0,0.0), CMPLX(0.0,58.0) },
// scale0 * src0
    c128_scale0_src0[] = { CMPLX(-4.7,2.1), CMPLX(2.4,1.8), CMPLX(-1.2,-5.9) },
// conj(src0)
    c128_conj_src0[] = { CMPLX(-1.8,1.0), CMPLX(0.0,-1.2), CMPLX(1.6,1.8) };
static const SLCi32_t c128arraysize = SLCarraysize(c128_src0);
#pragma endregion c128_test_data
```
# Generic
```
#pragma region <VTYPE>_functions
```
## AddAss, ScaleAss, ScaleAddAss, MultiplyEbeAss
```
static SLCerrno_t <VTYPE>AddAssUT() 
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLC<VTYPE>_t dst[SLCarraysize(<VTYPE>_src0)];
    do {
        SLC<VTYPE>_copy(dst, 1, <VTYPE>_src0, 1, <VTYPE>arraysize);
        SLCBLAS<VTYPE>_AddAss(dst, <VTYPE>_src1, <VTYPE>arraysize);
        for (SLC<ITYPE>_t i = 0; i < <VTYPE>arraysize; i++)
        {
            if (!SLC<VTYPE>_areequal(dst[i], <VTYPE>_src0_plus_src1[i], SLC<VTYPE>_stdtol))
            {
                err = EXIT_FAILURE;
                SLCLog<VTYPE>_ERR(err, "<VTYPE>_src0_plus_src1", "dst", i, <VTYPE>_src0_plus_src1, dst);
            }
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
```
static SLCerrno_t <VTYPE>ScaleAssUT() 
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLC<VTYPE>_t dst[SLCarraysize(<VTYPE>_src0)];
    do {
        SLC<VTYPE>_copy(dst, 1, <VTYPE>_src0, 1, <VTYPE>arraysize);
        SLCBLAS<VTYPE>_ScaleAss(dst, &<VTYPE>_scale0, <VTYPE>arraysize);
        for (SLC<ITYPE>_t i = 0; i < <VTYPE>arraysize; i++)
        {
            if (!SLC<VTYPE>_areequal(dst[i], <VTYPE>_scale0_src0[i], SLC<VTYPE>_stdtol))
            {
                err = EXIT_FAILURE;
                SLCLog<VTYPE>_ERR(err, "<VTYPE>_scale0_src0", "dst", i, <VTYPE>_scale0_src0, dst);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
```
static SLCerrno_t <VTYPE>ScaleAddAssUT() 
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLC<VTYPE>_t dst[SLCarraysize(<VTYPE>_src0)];
    do {
        SLC<VTYPE>_copy(dst, 1, <VTYPE>_src0, 1, <VTYPE>arraysize);
        SLCBLAS<VTYPE>_ScaleAddAss(dst, <VTYPE>_src1, &<VTYPE>_scale1, <VTYPE>arraysize);
        for (SLC<ITYPE>_t i = 0; i < <VTYPE>arraysize; i++)
        {
            if (!SLC<VTYPE>_areequal(dst[i], <VTYPE>_src0_plus_scale1_src1[i], SLC<VTYPE>_stdtol))
            {
                err = EXIT_FAILURE;
                SLCLog<VTYPE>_ERR(
                    err, "<VTYPE>_src0_plus_scale1_src1", "dst",
                    i, <VTYPE>_src0_plus_scale1_src1, dst);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
```
SLCerrno_t <VTYPE>MultiplyEbeAssUT() 
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLC<VTYPE>_t dst[SLCarraysize(<VTYPE>_src0)];
    do {
        SLC<VTYPE>_copy(dst, 1, <VTYPE>_src0, 1, <VTYPE>arraysize);
        SLCBLAS<VTYPE>_MultiplyEbeAss(dst, <VTYPE>_src1, <VTYPE>arraysize);
        for (SLC<ITYPE>_t i = 0; i < <VTYPE>arraysize; i++)
        {
            if (!SLC<VTYPE>_areequal(dst[i], <VTYPE>_src0_src1_ebe[i], SLC<VTYPE>_stdtol))
            {
                err = EXIT_FAILURE;
                SLCLog<VTYPE>_ERR(err, "<VTYPE>_src0_src1_ebe", "dst", i, <VTYPE>_src0_src1_ebe, dst);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## Add, Scale, ScaleAdd, MultiplyEbe
```
static SLCerrno_t <VTYPE>AddUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLC<VTYPE>_t dst[SLCarraysize(<VTYPE>_src0)];
    do {
        SLCBLAS<VTYPE>_Add(dst, <VTYPE>_src0, <VTYPE>_src1, <VTYPE>arraysize);
        for (SLC<ITYPE>_t i = 0; i < <VTYPE>arraysize; i++)
        {
            if (!SLC<VTYPE>_areequal(dst[i], <VTYPE>_src0_plus_src1[i], SLC<VTYPE>_stdtol))
            {
                err = EXIT_FAILURE;
                SLCLog<VTYPE>_ERR(err, "<VTYPE>_src0_plus_src1", "dst", i, <VTYPE>_src0_plus_src1, dst);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
```
static SLCerrno_t <VTYPE>ScaleUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLC<VTYPE>_t dst[SLCarraysize(<VTYPE>_src0)];
    do {
        SLCBLAS<VTYPE>_Scale(dst, <VTYPE>_src0, &<VTYPE>_scale0, <VTYPE>arraysize);
        for (SLC<ITYPE>_t i = 0; i < <VTYPE>arraysize; i++)
        {
            if (!SLC<VTYPE>_areequal(dst[i], <VTYPE>_scale0_src0[i], SLC<VTYPE>_stdtol))
            {
                err = EXIT_FAILURE;
                SLCLog<VTYPE>_ERR(err, "<VTYPE>_scale0_src0", "dst", i, <VTYPE>_scale0_src0, dst);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
```
static SLCerrno_t <VTYPE>ScaleAddUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLC<VTYPE>_t dst[SLCarraysize(<VTYPE>_src0)];
    do {
        SLCBLAS<VTYPE>_ScaleAdd
            (dst,
             <VTYPE>_src0, &<VTYPE>_scale0,
             <VTYPE>_src1, &<VTYPE>_scale1,
             <VTYPE>arraysize);
        for (SLC<ITYPE>_t i = 0; i < <VTYPE>arraysize; i++)
        {
            if (!SLC<VTYPE>_areequal(dst[i], <VTYPE>_scale0_src0_plus_scale1_src1[i], SLC<VTYPE>_stdtol))
            {
                err = EXIT_FAILURE;
                SLCLog<VTYPE>_ERR(err, "<VTYPE>_scale0_src0_plus_scale1_src1", "dst",
                    i, <VTYPE>_scale0_src0_plus_scale1_src1, dst);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
```
static SLCerrno_t <VTYPE>MultiplyEbeUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLC<VTYPE>_t dst[SLCarraysize(<VTYPE>_src0)];
    do {
        SLCBLAS<VTYPE>_MultiplyEbe(dst, <VTYPE>_src0, <VTYPE>_src1, <VTYPE>arraysize);
        for (SLC<ITYPE>_t i = 0; i < <VTYPE>arraysize; i++)
        {
            if (!SLC<VTYPE>_areequal(dst[i], <VTYPE>_src0_src1_ebe[i], SLC<VTYPE>_stdtol))
            {
                err = EXIT_FAILURE;
                SLCLog<VTYPE>_ERR(err, "<VTYPE>_src0_src1_ebe", "dst", i, <VTYPE>_src0_src1_ebe, dst);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## CopyConj
```
static SLCerrno_t <VTYPE>CopyConjUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLC<VTYPE>_t dst[SLCarraysize(<VTYPE>_src0)];
    do {
        SLCBLAS<VTYPE>_CopyConj(dst, 1, <VTYPE>_src0, 1, <VTYPE>arraysize);
        for (SLC<ITYPE>_t i = 0; i < <VTYPE>arraysize; i++)
        {
            if (!SLC<VTYPE>_areequal(dst[i], <VTYPE>_conj_src0[i], SLC<VTYPE>_stdtol))
            {
                err == EXIT_FAILURE;
                SLCLog<VTYPE>_ERR(err, "<VTYPE>_conj_src0", "dst", i, <VTYPE>_conj_src0, dst);
                break;
            }
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## InnreProduct, ProductSum, Sum, AbsSum
```
```
## submain harnessing MiniBLASUT functions
```
SLCerrno_t <VTYPE>MiniBLASUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    do {
        err = <VTYPE>AddAssUT();
        if (err) break;
        err = <VTYPE>ScaleAssUT();
        if (err) break;
        err = <VTYPE>ScaleAddAssUT();
        if (err) break;
        err = <VTYPE>MultiplyEbeAssUT();
        if (err) break;
        err = <VTYPE>AddUT();
        if (err) break;
        err = <VTYPE>ScaleUT();
        if (err) break;
        err = <VTYPE>ScaleAddUT();
        if (err) break;
        err = <VTYPE>MultiplyEbeUT();
        if (err) break;
        err = <VTYPE>CopyConjUT();
        if (err) break;
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
#pragma endregion <VTYPE>_functions
```
# Foot
```
SLCerrno_t MiniBLASUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = r32MiniBLASUT()))
        {
            SLCLog_ERR(err, " in r32MiniBLASUT @ %s,%d\n", __FILE__, __LINE__);
            break;
        }
        
        if (EXIT_SUCCESS != (err = r64MiniBLASUT()))
        {
            SLCLog_ERR(err, " in r64MiniBLASUT @ %s,%d\n", __FILE__, __LINE__);
            break;
        }

        if (EXIT_SUCCESS != (err = c64MiniBLASUT()))
        {
            SLCLog_ERR(err, " in c64MiniBLASUT @ %s,%d\n", __FILE__, __LINE__);
            break;
        }

        if (EXIT_SUCCESS != (err = c128MiniBLASUT()))
        {
            SLCLog_ERR(err, " in c128MiniBLASUT @ %s,%d\n", __FILE__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
