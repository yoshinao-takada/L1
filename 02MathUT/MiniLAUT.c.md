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
```
## SLCr64_t test data
```
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
```
## SLCc64_t test data
```
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
```
## SLCc128_t test data
```
// source values
static const SLCc128_t c128src0[] = {
    CMPLXF(1.0, 2.0), CMPLXF(2.5,-2.2), CMPLXF(-0.5,0.5),
    CMPLXF(1.2, -10.0), CMPLXF(-5.5, -2.5), CMPLXF(2.5,2.2)
};
static const SLCc128_t c128src1[] = {
    CMPLXF(-1.0, -2.0), CMPLXF(-2.0, 0.0), CMPLXF(-0.0,0.5),
    CMPLXF(-1.5, 10.5), CMPLXF(6.0, 0.0), CMPLXF(0.0,0.2)
};
static const SLCc128_t c128src2[] = {
    CMPLXF(-1.0, -2.0), CMPLXF(-2.0, -4.0), CMPLXF(-1.0, -2.0), CMPLXF(-2.0, -4.0),
    CMPLXF(2.0, 2.2), CMPLXF(-3.3, -5.0), CMPLXF(2.0, -2.2), CMPLXF(3.3, -5.0),
    CMPLXF(1.5, -1.5), CMPLXF(-2.2, -5.0), CMPLXF(-1.5, -1.5), CMPLXF(2.2, -5.0),
};
static const SLCc128_t c128scale0 = CMPLXF(0.1,1.1), c128scale1 = CMPLXF(-1.5,0.1);

// test reference values
// src0 + src1
static const SLCc128_t c128_src0_plus_src1[] = {
    CMPLXF(0.0, 0.0), CMPLXF(0.5,-2.2), CMPLXF(-0.5,1.0),
    CMPLXF(-0.3,0.5), CMPLXF(0.5,-2.5), CMPLXF(2.5,2.4)
};
// scale0 * src0 + scale1 * src1
static const SLCc128_t c128_scale0_src0_plus_scale1_src1[] = {
    CMPLXF(-0.4,4.2), CMPLXF(5.67,2.33), CMPLXF(-0.65,-1.25),
    CMPLXF(12.32,-15.58), CMPLXF(-6.8, -5.7), CMPLXF(-2.19,2.67)
};
// scale0 * src0
static const SLCc128_t c128_scale0_src0[] = {
    CMPLXF(-2.1,1.3), CMPLXF(2.67,2.53), CMPLXF(-0.6,-0.5),
    CMPLXF(11.12,0.32), CMPLXF(2.2,-6.3), CMPLXF(-2.17,2.97)
};
```
# Generic
## matrix sizes
```
static const SLC4i16_t <VTYPE>matsize2x3 = { sizeof(SLC<VTYPE>_t), 3, 2, 1 };
static const SLC4i16_t <VTYPE>matsize3x2 = { sizeof(SLC<VTYPE>_t), 2, 3, 1 };
static const SLC4i16_t <VTYPE>matsize3x4 = { sizeof(SLC<VTYPE>_t), 4, 3, 1 };
static const SLC4i16_t <VTYPE>matsize3x3 = { sizeof(SLC<VTYPE>_t), 3, 3, 1 };
```
## add two matrices
```
static SLCerrno_t <VTYPE>AddUT() 
{
    SLCerrno_t err = EXIT_SUCCESS;
    do {

    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}

static SLCerrno_t <VTYPE>ScaleAddUT() 
{
    SLCerrno_t err = EXIT_SUCCESS;
    do {

    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}

static SLCerrno_t <VTYPE>ScaleUT() 
{
    SLCerrno_t err = EXIT_SUCCESS;
    do {

    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## multiply two matrices
```
```
## Invert a matrix
```
```
## Solve a fully determined equation
```
```
## Solve an overly determined equation
```
```
## Simplified API to solve overly determined equation
```
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
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
}
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
