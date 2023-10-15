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
#include "SLC/LinePlane.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
            SLCLog_ERR(err, "value mismatch @ %s, %d\n", __FILE__, __LINE__);
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
            SLCLog_ERR(err, "value mismatch @ %s, %d\n", __FILE__, __LINE__);
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
            SLCLog_ERR(err, "value mismatch @ %s, %d\n", __FILE__, __LINE__);
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
            SLCLog_ERR(err, "value mismatch @ %s,%d\n", __FILE__, __LINE__);
            break;
        }
        dot = SLCVec<VTYPE>_Dot(unit_vector0A, unit_vector1);
        SLC<VTYPE>_t dot3 = dot+dot+dot;
        if (!SLC<VTYPE>_areequal(dot3, _1, SLC<VTYPE>_stdtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch @ %s,%d\n", __FILE__, __LINE__);
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
            SLCLog_ERR(err, "value mismatch @ %s,%d\n", __FILE__, __LINE__);
            break;
        }
        cross = SLCVec<VTYPE>_Cross(uv1,uv0, work);
        if (!SLCPnt<VTYPE>_areequal(uv1_cross_uv0, cross, SLC<VTYPE>_stdtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch @ %s,%d\n", __FILE__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## Line and Plane
```
void <VTYPE>OrthX(SLCVec<VTYPE>_t orth, SLCCVec<VTYPE>_t src)
{
    SLC<VTYPE>_t _0 = SLC<VTYPE>_units[0], _1 = SLC<VTYPE>_units[1];
    SLC4<VTYPE>_t x = { _1, _0, _0, _1 };
    SLC4<VTYPE>_t _src_cross_x;
    SLCVec<VTYPE>_Cross(src, x, _src_cross_x);
    SLCVec<VTYPE>_Normalize(_src_cross_x, orth);
}

void <VTYPE>OrthY(SLCVec<VTYPE>_t orth, SLCCVec<VTYPE>_t src)
{
    SLC<VTYPE>_t _0 = SLC<VTYPE>_units[0], _1 = SLC<VTYPE>_units[1];
    SLC4<VTYPE>_t y = { _0, _1, _0, _1 };
    SLC4<VTYPE>_t _src_cross_y;
    SLCVec<VTYPE>_Cross(src, y, _src_cross_y);
    SLCVec<VTYPE>_Normalize(_src_cross_y, orth);
}

SLCerrno_t <VTYPE>LineUT()
{
    const SLC<VTYPE>_t _0 = SLC<VTYPE>_units[0], _1 = SLC<VTYPE>_units[1];
    SLCerrno_t err = EXIT_SUCCESS;
    // setup line
    SLCLine<VTYPE>_t line;
    SLC4<VTYPE>_t _orth0, _orth1, _refPntOnLine;
    SLC4<VTYPE>_t _pe0, _pe1, _foot0, _foot1;
    SLCcopy4(line.p0, <VTYPE>pnt0A);
    SLCVec<VTYPE>_Normalize(<VTYPE>move0A, line.d0);
    do {
        // refPntOnLine is a reference point of foot from pe0 and pe1
        SLCCVec<VTYPE>_t refPntOnLine = SLCVec<VTYPE>_ScaleAdd(line.p0, _1, line.d0, <VTYPE>_2p5, _refPntOnLine);

        // _orth0, orth1 are unit vectors orthogonal to line.d0
        <VTYPE>OrthX(_orth0, line.d0);
        <VTYPE>OrthY(_orth1, line.d0);

        // pe0, pe1 are test point apart from the line
        SLCCVec<VTYPE>_t pe0 = SLCVec<VTYPE>_ScaleAdd(refPntOnLine, _1, _orth0, _1, _pe0);
        SLCCVec<VTYPE>_t pe1 = SLCVec<VTYPE>_ScaleAdd(refPntOnLine, _1, _orth1, _1, _pe1);

        // calculate coordinate of a foot from pe0 as foot0.
        SLCCPnt<VTYPE>_t foot0 = SLCLine<VTYPE>_Foot(&line, pe0, _foot0);

        // calculate coordinate of a foot from pe1 as foot1.
        SLCCPnt<VTYPE>_t foot1 = SLCLine<VTYPE>_Foot(&line, pe1, _foot1);

        // confirm equality of foot0, foot1, and refPntOnLine.
        if (!SLCPnt<VTYPE>_areequal(refPntOnLine, foot0, SLC<VTYPE>_stdtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch with foot0 @ %s,%d\n", __FILE__, __LINE__);
            break;
        }
        if (!SLCPnt<VTYPE>_areequal(refPntOnLine, foot1, SLC<VTYPE>_stdtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch with foot1 @ %s,%d\n", __FILE__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}

SLCerrno_t <VTYPE>PlaneUT()
{
    const SLC<VTYPE>_t _0 = SLC<VTYPE>_units[0], _1 = SLC<VTYPE>_units[1];
    SLCerrno_t err = EXIT_SUCCESS;
    SLCPlane<VTYPE>_t plane;
    SLC4<VTYPE>_t _orth0, _orth1, _refPntOnPlane0, _refPntOnPlane1;
    SLC4<VTYPE>_t _pe0, _pe1, _foot0, _foot1;
    SLCcopy4(plane.p0, <VTYPE>pnt0A);
    SLCVec<VTYPE>_Normalize(<VTYPE>move0A, plane.n0);
    do {
        // _orth0, orth1 are unit vectors orthogonal to plane.n0
        <VTYPE>OrthX(_orth0, plane.n0);
        <VTYPE>OrthY(_orth1, plane.n0);

        // _refPntOnPlane0, _refPntOnPlane1 are reference points on the plane
        // but not equal to plane.p0.
        SLCCPnt<VTYPE>_t refPntOnPlane0 = SLCVec<VTYPE>_ScaleAdd(
            plane.p0, _1, _orth0, <VTYPE>_2p5, _refPntOnPlane0);
        SLCCPnt<VTYPE>_t refPntOnPlane1 = SLCVec<VTYPE>_ScaleAdd(
            plane.p0, _1, _orth1, <VTYPE>_2p5, _refPntOnPlane1);

        // test points apart from the reference points by multiple of plane normal vector
        SLCCPnt<VTYPE>_t pe0 = SLCVec<VTYPE>_ScaleAdd(
            _refPntOnPlane0, _1, plane.n0, -<VTYPE>_2p5, _pe0);
        SLCCPnt<VTYPE>_t pe1 = SLCVec<VTYPE>_ScaleAdd(
            _refPntOnPlane1, _1, plane.n0, _1, _pe1);
        
        // calculate coordinates of foot points.
        SLCCPnt<VTYPE>_t foot0 = SLCPlane<VTYPE>_Foot(&plane, pe0, _foot0);
        SLCCPnt<VTYPE>_t foot1 = SLCPlane<VTYPE>_Foot(&plane, pe1, _foot1);

        // confirm equality of foot0 and refPntOnPlane0
        if (!SLCPnt<VTYPE>_areequal(refPntOnPlane0, foot0, SLC<VTYPE>_stdtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch of foot0 @ %s,%d\n", __FILE__, __LINE__);
            break;
        }

        // confirm equality of foot1 and refPntOnPlane1
        if (!SLCPnt<VTYPE>_areequal(refPntOnPlane1, foot1, SLC<VTYPE>_stdtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch of foot1 @ %s,%d\n", __FILE__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}

```
## Plane-Line Intersection Test Data
```
// create test data for Intersection APIs
void <VTYPE>CreateData(SLCPLine<VTYPE>_t line,
    SLCPPlane<VTYPE>_t plane0, SLCPPlane<VTYPE>_t plane1, SLCPPlane<VTYPE>_t plane2
) {
    const SLC<VTYPE>_t _0 = SLC<VTYPE>_units[0], _1 = SLC<VTYPE>_units[1];
    SLCcopy4(line->p0, <VTYPE>pnt0A);
    SLCVec<VTYPE>_Normalize(<VTYPE>move0A, line->d0);

    plane0->p0[0] = _1; plane0->p0[1] = _0; plane0->p0[2] = _0; plane0->p0[3] = _1;
    plane0->n0[0] = plane0->n0[1] = (SLC<VTYPE>_t)0.5;
    plane0->n0[2] = SLC<VTYPE>_sqrt(_1
        - plane0->n0[0] * plane0->n0[0]
        - plane0->n0[1] * plane0->n0[1]);
    plane0->n0[3] = _1;

    plane1->p0[0] = plane1->p0[1] = plane1->p0[2] = _0;
    plane1->p0[3] = _1;
    plane1->n0[0] = -(plane1->n0[1] = (SLC<VTYPE>_t)0.55);
    plane1->n0[2] = SLC<VTYPE>_sqrt(_1
        - plane1->n0[0] * plane1->n0[0]
        - plane1->n0[1] * plane1->n0[1]);
    plane1->n0[3] = -_1;

    plane2->p0[0] = plane2->p0[1] = -(plane2->p0[2] = _1);
    plane2->p0[3] = _1;
    plane2->n0[0] = -(plane2->n0[1] = -(SLC<VTYPE>_t)0.57);
    plane2->n0[2] = SLC<VTYPE>_sqrt(_1
        - plane2->n0[0] * plane2->n0[0]
        - plane2->n0[1] * plane2->n0[1]);
    plane2->n0[3] = _1;
}

void <VTYPE>ValidateData(SLCPLine<VTYPE>_t line,
    SLCPPlane<VTYPE>_t plane0, SLCPPlane<VTYPE>_t plane1, SLCPPlane<VTYPE>_t plane2
) {
    const SLC<VTYPE>_t _0 = SLC<VTYPE>_units[0], _1 = SLC<VTYPE>_units[1];

    // direction vector and normal vectors are all unit vector
    assert(SLC<VTYPE>_areequal(_1, SLCVec<VTYPE>_Dot(line->d0, line->d0), SLC<VTYPE>_stdtol));
    assert(SLC<VTYPE>_areequal(_1, SLCVec<VTYPE>_Dot(plane0->n0, plane0->n0), SLC<VTYPE>_stdtol));
    assert(SLC<VTYPE>_areequal(_1, SLCVec<VTYPE>_Dot(plane1->n0, plane1->n0),
    SLC<VTYPE>_stdtol));
    assert(SLC<VTYPE>_areequal(_1, SLCVec<VTYPE>_Dot(plane2->n0, plane2->n0),
    SLC<VTYPE>_stdtol));

    // direction vector and normal vectors are not identical.
    assert(!SLC<VTYPE>_areequal(_1, SLCVec<VTYPE>_Dot(line->d0, plane0->n0), SLC<VTYPE>_stdtol));
    assert(!SLC<VTYPE>_areequal(-_1, SLCVec<VTYPE>_Dot(line->d0, plane0->n0), SLC<VTYPE>_stdtol));
    assert(!SLC<VTYPE>_areequal(_1, SLCVec<VTYPE>_Dot(line->d0, plane1->n0), SLC<VTYPE>_stdtol));
    assert(!SLC<VTYPE>_areequal(-_1, SLCVec<VTYPE>_Dot(line->d0, plane1->n0), SLC<VTYPE>_stdtol));
    assert(!SLC<VTYPE>_areequal(_1, SLCVec<VTYPE>_Dot(line->d0, plane2->n0), SLC<VTYPE>_stdtol));
    assert(!SLC<VTYPE>_areequal(-_1, SLCVec<VTYPE>_Dot(line->d0, plane2->n0), SLC<VTYPE>_stdtol));
    assert(!SLC<VTYPE>_areequal(_1, SLCVec<VTYPE>_Dot(plane0->n0, plane1->n0), SLC<VTYPE>_stdtol));
    assert(!SLC<VTYPE>_areequal(-_1, SLCVec<VTYPE>_Dot(plane0->n0, plane1->n0), SLC<VTYPE>_stdtol));
    assert(!SLC<VTYPE>_areequal(_1, SLCVec<VTYPE>_Dot(plane0->n0, plane2->n0), SLC<VTYPE>_stdtol));
    assert(!SLC<VTYPE>_areequal(-_1, SLCVec<VTYPE>_Dot(plane0->n0, plane2->n0), SLC<VTYPE>_stdtol));
    assert(!SLC<VTYPE>_areequal(_1, SLCVec<VTYPE>_Dot(plane1->n0, plane2->n0), SLC<VTYPE>_stdtol));
    assert(!SLC<VTYPE>_areequal(-_1, SLCVec<VTYPE>_Dot(plane1->n0, plane2->n0), SLC<VTYPE>_stdtol));
}
```
## Plane-Line Intersection
```
static SLCLine<VTYPE>_t <VTYPE>line;
static SLCPlane<VTYPE>_t <VTYPE>plane0, <VTYPE>plane1, <VTYPE>plane2;

SLCerrno_t <VTYPE>PlaneLineIntersectionUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    <VTYPE>CreateData(&<VTYPE>line, &<VTYPE>plane0, &<VTYPE>plane1, &<VTYPE>plane2);
    <VTYPE>ValidateData(&<VTYPE>line, &<VTYPE>plane0, &<VTYPE>plane1, &<VTYPE>plane2);
    SLC4<VTYPE>_t _intersection, _p0_intersection, _cross;
    do {
        // Get the intersection of the plane and the line
        if (EXIT_SUCCESS != (err = SLCPlane<VTYPE>_IntersectionLinePlane(
            &<VTYPE>plane0, &<VTYPE>line, _intersection
        )))
        {
            SLCLog_ERR(err, "Equation near singular @ %s,%d\n", __FILE__, __LINE__);
            break;
        }

        // Check if the intersection belongs to the plane.
        SLCCVec<VTYPE>_t p0_intersection = SLCVec<VTYPE>_ToVector(
            <VTYPE>plane0.p0, _intersection, _p0_intersection
        );
        SLC<VTYPE>_t dot = SLCVec<VTYPE>_Dot(<VTYPE>plane0.n0, p0_intersection);
        if (dot > (SLC<VTYPE>_stdtol * SLC<VTYPE>_stdtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "Value mismatch @ %s,%d\n", __FILE__, __LINE__);
            break;
        }

        // Check if the intersection belongs to the line.
        p0_intersection = SLCVec<VTYPE>_ToVector(
            <VTYPE>line.p0, _intersection, _p0_intersection
        );
        SLCCVec<VTYPE>_t cross = SLCVec<VTYPE>_Cross(
            <VTYPE>line.d0, p0_intersection, _cross
        );
        SLC<VTYPE>_t L2norm_cross = SLCVec<VTYPE>_Dot(cross, cross);
        if (L2norm_cross > (SLC<VTYPE>_stdtol * SLC<VTYPE>_stdtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "Value mismatch @ %s,%d\n", __FILE__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## Plane-Plane Intersection
```
SLCerrno_t <VTYPE>PlaneIntersectionUT()
{
    const SLC<VTYPE>_t _0 = SLC<VTYPE>_units[0], _1 = SLC<VTYPE>_units[1];
    SLCerrno_t err = EXIT_SUCCESS;
    SLCLine<VTYPE>_t _intersection;
    SLC4<VTYPE>_t _d0end, _linep0_planep0, _d0end_planep0;
    do {
        if (EXIT_SUCCESS != (err = SLCPlane<VTYPE>_Intersection2Planes(
            &<VTYPE>plane0, &<VTYPE>plane1, &_intersection)))
        {
            SLCLog_ERR(err, "Equation is near singular @ %s,%d\n",
                __FILE__, __LINE__);
            break;
        }

        // check if the intersection line reference point is on plane0
        SLCCVec<VTYPE>_t linep0_planep0 = 
            SLCVec<VTYPE>_ToVector(<VTYPE>plane0.p0, _intersection.p0, _linep0_planep0);
        SLC<VTYPE>_t absdot = SLC<VTYPE>_abs(SLCVec<VTYPE>_Dot(
            <VTYPE>plane0.n0, linep0_planep0));
        if (absdot > (SLC<VTYPE>_bigtol * SLC<VTYPE>_bigtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch @ %s,%d\n", __FILE__, __LINE__);
            break;
        }

        // check if the intersection line reference point is on plane1
        linep0_planep0 =
            SLCVec<VTYPE>_ToVector(<VTYPE>plane1.p0, _intersection.p0, _linep0_planep0);
        absdot = SLC<VTYPE>_abs(SLCVec<VTYPE>_Dot(
            <VTYPE>plane1.n0, linep0_planep0));
        if (absdot > (SLC<VTYPE>_bigtol * SLC<VTYPE>_bigtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch @ %s,%d\n", __FILE__, __LINE__);
            break;
        }

        // get the end point of the direction vector
        SLCCVec<VTYPE>_t d0end = 
            SLCVec<VTYPE>_ScaleAdd(_intersection.p0, _1, _intersection.d0, _1, _d0end);

        // check if the end point is on plane0
        SLCCVec<VTYPE>_t d0end_planep0 = 
            SLCVec<VTYPE>_ToVector(<VTYPE>plane0.p0, d0end, _d0end_planep0);
        absdot = SLC<VTYPE>_abs(SLCVec<VTYPE>_Dot(<VTYPE>plane0.n0, d0end_planep0));
        if (absdot > (SLC<VTYPE>_bigtol * SLC<VTYPE>_bigtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch @ %s,%d\n", __FILE__, __LINE__);
            break;
        }

        // check if the end point is on plane1
        d0end_planep0 = SLCVec<VTYPE>_ToVector(<VTYPE>plane1.p0, d0end, _d0end_planep0);
        absdot = SLC<VTYPE>_abs(SLCVec<VTYPE>_Dot(<VTYPE>plane1.n0, d0end_planep0));
        if (absdot > (SLC<VTYPE>_bigtol * SLC<VTYPE>_bigtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "value mismatch @ %s,%d\n", __FILE__, __LINE__);
            break;
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}
```
## Three-Plane Intersection
```
SLCerrno_t <VTYPE>ThreePlaneIntersectionUT()
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLC4<VTYPE>_t _intersection, _p0_intersection;
    do {
        if (EXIT_SUCCESS != (err = SLCPlane<VTYPE>_Intersection3Planes(
            &<VTYPE>plane0, &<VTYPE>plane1, &<VTYPE>plane2, _intersection)))
        {
            SLCLog_ERR(err, "Equation is near singular @ %s,%d\n",
                __FILE__, __LINE__);
            break;
        }

        // check if _intersection belongs to plane0.
        SLCCVec<VTYPE>_t p0_intersection = SLCVec<VTYPE>_ToVector(
            <VTYPE>plane0.p0, _intersection, _p0_intersection);
        SLC<VTYPE>_t dot = SLCVec<VTYPE>_Dot(p0_intersection, <VTYPE>plane0.n0);
        if (dot > (SLC<VTYPE>_bigtol * SLC<VTYPE>_bigtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "Value mismatch @ %s,%d\n", __FILE__, __LINE__);
            break;
        }

        // check if _intersection belongs to plane1.
        p0_intersection = SLCVec<VTYPE>_ToVector(
            <VTYPE>plane1.p0, _intersection, _p0_intersection);
        dot = SLCVec<VTYPE>_Dot(p0_intersection, <VTYPE>plane1.n0);
        if (dot > (SLC<VTYPE>_bigtol * SLC<VTYPE>_bigtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "Value mismatch @ %s,%d\n", __FILE__, __LINE__);
            break;
        }

        // check if _intersection belongs to plane2.
        p0_intersection = SLCVec<VTYPE>_ToVector(
            <VTYPE>plane2.p0, _intersection, _p0_intersection);
        dot = SLCVec<VTYPE>_Dot(p0_intersection, <VTYPE>plane2.n0);
        if (dot > (SLC<VTYPE>_bigtol * SLC<VTYPE>_bigtol))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "Value mismatch @ %s,%d\n", __FILE__, __LINE__);
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
        err = <VTYPE>LineUT();
        if (err) break;
        err = <VTYPE>PlaneUT();
        if (err) break;
        err = <VTYPE>PlaneLineIntersectionUT();
        if (err) break;
        err = <VTYPE>PlaneIntersectionUT();
        if (err) break;
        err = <VTYPE>ThreePlaneIntersectionUT();
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
