# Control
```
{
    "out": "Geom3DUT.c",
    "vtypes": ["r32", "r64"],
    "rtypes": ["r32", "r64"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
## Header block
```
#include "SLC/Numbers.h"
#include "SLC/NumbersCopy.h"
#include "SLC/errno.h"
#include "SLC/Log.h"
#include "SLC/MiniBLAS.h"
#include "SLC/Geom3D.h"
#include <stdio.h>
#include <stdlib.h>
```
## Test data
### SLCr32_t test data
```
#pragma region SLCr32_t_test_data
// initial point of linear translation
static const SLC4r32_t r32pnt0A = { 0.0f, 1.0f, -2.5f, 1.0f };
static const SLC4r32_t r32pnt0B = { 0.0f, -2.0f, 5.0f, -2.0f };

// translation vector
static const SLC4r32_t r32move0A = { -1.0f, -1.0f, 1.2f, 1.0f };
static const SLC4r32_t r32move0B = { 3.0f, 3.0f, -3.6f, -3.0f };

// scalar numbers
static const SLCr32_t r32_2p5 = 2.5f;
#pragma endregion SLCr32_t_test_data
```
### SLCr64_t test data
```
#pragma region SLCr64_t_test_data
// initial point of linear translation
static const SLC4r64_t r64pnt0A = { 0.0, 1.0, -2.5, 1.0 };
static const SLC4r64_t r64pnt0B = { 0.0, -2.0, 5.0, -2.0 };

// translation vector
static const SLC4r64_t r64move0A = { -1.0, -1.0, 1.2, 1.0 };
static const SLC4r64_t r64move0B = { 3.0, 3.0, -3.6, -3.0 };

// scalar numbers
static const SLCr64_t r64_2p5 = 2.5;
#pragma endregion SLCr64_t_test_data
```
# Generic
## Linear translation and generic transform
```
SLCerrno_t <VTYPE>TranslateTransformUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLC<VTYPE>_t _transA[16], _transB[16],
        _transApntA[4], _transApntB[4], _transBpntA[4], _transBpntB[4];
    do {
        SLCCTMat<VTYPE>_t transA = SLCTMat<VTYPE>_Translate(<VTYPE>move0A, _transA);
        SLCCTMat<VTYPE>_t transB = SLCTMat<VTYPE>_Translate(<VTYPE>move0B, _transB);
        SLCCPnt<VTYPE>_t transApntA = SLCTMat<VTYPE>_Transform(transA, <VTYPE>pnt0A, _transApntA);
        SLCCPnt<VTYPE>_t transApntB = SLCTMat<VTYPE>_Transform(transA, <VTYPE>pnt0B, _transApntB);
        SLCCPnt<VTYPE>_t transBpntA = SLCTMat<VTYPE>_Transform(transB, <VTYPE>pnt0A, _transBpntA);
        SLCCPnt<VTYPE>_t transBpntB = SLCTMat<VTYPE>_Transform(transB, <VTYPE>pnt0B, _transBpntB);
        if (!SLCPnt<VTYPE>_areequal(transApntA, transApntB, SLC<VTYPE>_stdtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "transApntA = {%f, %f, %f}, transApntB = {%f, %f, %f}\n",
                SLCPnt_homo2real(transApntA), SLCPnt_homo2real(transApntB));
            break;
        }
        if (!SLCPnt<VTYPE>_areequal(transApntA, transBpntA, SLC<VTYPE>_stdtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "transApntA = {%f, %f, %f}, transBpntA = {%f, %f, %f}\n",
                SLCPnt_homo2real(transApntA), SLCPnt_homo2real(transBpntA));
            break;
        }
        if (!SLCPnt<VTYPE>_areequal(transApntA, transBpntB, SLC<VTYPE>_stdtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "transApntA = {%f, %f, %f}, transBpntB = {%f, %f, %f}\n",
                SLCPnt_homo2real(transApntA), SLCPnt_homo2real(transBpntB));
            break;
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## Rotation transform
```
SLCerrno_t <VTYPE>RotateZUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLC<VTYPE>_t work_mat[16];
    // 45 degree rotation around Z-axis
    SLCCTMat<VTYPE>_t mat = SLCTMat<VTYPE>_RotateZdeg((SLC<VTYPE>_t)45, work_mat);
    // vec0 = { 1,1,0,1 }
    const SLC4<VTYPE>_t _vec0 = { SLC<VTYPE>_units[1], SLC<VTYPE>_units[1], SLC<VTYPE>_units[0], SLC<VTYPE>_units[1] };
    SLC4<VTYPE>_t _vec1, _vec2;
    do {
        SLCCVec<VTYPE>_t vec1 = SLCTMat<VTYPE>_Transform(mat, _vec0, _vec1);
        SLCCVec<VTYPE>_t vec2 = SLCTMat<VTYPE>_Transform(mat, vec1, _vec2);
        if (!(SLC<VTYPE>_areequal(_vec0[1], vec2[1], SLC<VTYPE>_stdtol) && 
             SLC<VTYPE>_areequal(_vec0[0], -vec2[0], SLC<VTYPE>_stdtol)))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch @ %s, %d\n", __FUNCTION__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}

SLCerrno_t <VTYPE>RotateXUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLC<VTYPE>_t work_mat[16];
    // 45 degree rotation around X-axis
    SLCCTMat<VTYPE>_t mat = SLCTMat<VTYPE>_RotateXdeg((SLC<VTYPE>_t)45, work_mat);
    // vec0 = { 1, 1, 1, 1 }
    const SLC4<VTYPE>_t _vec0 = { SLC<VTYPE>_units[1], SLC<VTYPE>_units[1], SLC<VTYPE>_units[1], SLC<VTYPE>_units[1] };
    SLC4<VTYPE>_t _vec1, _vec2;
    do {
        SLCCVec<VTYPE>_t vec1 = SLCTMat<VTYPE>_Transform(mat, _vec0, _vec1);
        SLCCVec<VTYPE>_t vec2 = SLCTMat<VTYPE>_Transform(mat, vec1, _vec2);
        if (!(SLC<VTYPE>_areequal(_vec0[0], vec2[0], SLC<VTYPE>_stdtol) &&
              SLC<VTYPE>_areequal(_vec0[1], -vec2[1], SLC<VTYPE>_stdtol) &&
              SLC<VTYPE>_areequal(_vec0[2], vec2[2], SLC<VTYPE>_stdtol)))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch @ %s, %d\n", __FUNCTION__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}

SLCerrno_t <VTYPE>RotateYUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLC<VTYPE>_t work_mat[16];
    // 45 degree rotation around Y-axis
    SLCCTMat<VTYPE>_t mat = SLCTMat<VTYPE>_RotateYdeg((SLC<VTYPE>_t)45, work_mat);
    // vec0 = { 1, 1, 1, 1 }
    const SLC4<VTYPE>_t _vec0 = { SLC<VTYPE>_units[1], SLC<VTYPE>_units[1], SLC<VTYPE>_units[1], SLC<VTYPE>_units[1] };
    SLC4<VTYPE>_t _vec1, _vec2;
    do {
        SLCCVec<VTYPE>_t vec1 = SLCTMat<VTYPE>_Transform(mat, _vec0, _vec1);
        SLCCVec<VTYPE>_t vec2 = SLCTMat<VTYPE>_Transform(mat, vec1, _vec2);
        if (!(SLC<VTYPE>_areequal(_vec0[0], vec2[0], SLC<VTYPE>_stdtol) &&
              SLC<VTYPE>_areequal(_vec0[1], vec2[1], SLC<VTYPE>_stdtol) &&
              SLC<VTYPE>_areequal(_vec0[2], -vec2[2], SLC<VTYPE>_stdtol)))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch @ %s, %d\n", __FUNCTION__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## Vector dot product and cross product
```
SLCerrno_t <VTYPE>VectorDotUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    const SLC<VTYPE>_t _1 = SLC<VTYPE>_units[1];
    const SLC<VTYPE>_t _1_sqrt3 = _1 / SLC<VTYPE>_sqrt((SLC<VTYPE>_t)3);
    SLC4<VTYPE>_t
        unit_vector0 = { _1_sqrt3, _1_sqrt3, _1_sqrt3, _1},
        unit_vector0A;
    SLC4<VTYPE>_t
        unit_vector1 = { _1_sqrt3, _1_sqrt3, -_1_sqrt3, _1};
    SLCBLAS<VTYPE>_Scale(unit_vector0A, unit_vector0, &<VTYPE>_2p5, 4);
    do {
        SLC<VTYPE>_t dot = SLCVec<VTYPE>_Dot(unit_vector0, unit_vector0A);
        if (!SLC<VTYPE>_areequal(dot, _1, SLC<VTYPE>_stdtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch @ %s,%d\n", __FUNCTION__, __LINE__);
            break;
        }
        dot = SLCVec<VTYPE>_Dot(unit_vector0A, unit_vector1);
        SLC<VTYPE>_t dot3 = dot+dot+dot;
        if (!SLC<VTYPE>_areequal(dot3, _1, SLC<VTYPE>_stdtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch @ %s,%d\n", __FUNCTION__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}

SLCerrno_t <VTYPE>VectorCrossUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    const SLC<VTYPE>_t _1 = SLC<VTYPE>_units[1], _0 = SLC<VTYPE>_units[0];
    const SLC<VTYPE>_t _2 = _1 + _1;
    const SLC<VTYPE>_t _1_sqrt2 = SLC<VTYPE>_sqrt(SLC<VTYPE>_units[1]/_2);
    const SLC4<VTYPE>_t uv0 = { _1_sqrt2, _1_sqrt2, _0, _1 };
    const SLC4<VTYPE>_t uv1 = { -_1_sqrt2, _1_sqrt2, _0, _1 };
    const SLC4<VTYPE>_t uv0_cross_uv1 = { _0, _0, _1, _1 };
    const SLC4<VTYPE>_t uv1_cross_uv0 = { _0, _0, -_1, _1 };
    SLC4<VTYPE>_t work;
    do {
        SLCCVec<VTYPE>_t cross = SLCVec<VTYPE>_Cross(uv0, uv1, work);
        if (!SLCPnt<VTYPE>_areequal(uv0_cross_uv1, cross, SLC<VTYPE>_stdtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch @ %s,%d\n", __FUNCTION__, __LINE__);
            break;
        }
        cross = SLCVec<VTYPE>_Cross(uv1,uv0, work);
        if (!SLCPnt<VTYPE>_areequal(uv1_cross_uv0, cross, SLC<VTYPE>_stdtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch @ %s,%d\n", __FUNCTION__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## Test harness
```
SLCerrno_t <VTYPE>Geom3DUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    do {
        err = <VTYPE>TranslateTransformUT();
        if (err) break;
        err = <VTYPE>RotateZUT();
        if (err) break;
        err = <VTYPE>RotateXUT();
        if (err) break;
        err = <VTYPE>RotateYUT();
        if (err) break;
        err = <VTYPE>VectorDotUT();
        if (err) break;
        err = <VTYPE>VectorCrossUT();
        if (err) break;
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
# Foot
```
SLCerrno_t Geom3DUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    do {
        err = r32Geom3DUT();
        if (err) break;
        err = r64Geom3DUT();
        if (err) break;
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
