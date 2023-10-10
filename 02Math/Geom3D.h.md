# Control
```
{
    "out": "../include/SLC/Geom3D.h",
    "vtypes": ["r32", "r64"],
    "rtypes": ["r32", "r64"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
```
#if !defined(_02MATH_GEOM3D_H)
#define _02MATH_GEOM3D_H
#include "SLC/Numbers.h"
#include "SLC/Log.h"
#include "SLC/errno.h"
#include <stdio.h>
#include <stdlib.h>

#define SLCPnt_homo2real(__pntA) __pntA[0]/__pntA[3],__pntA[1]/__pntA[3],__pntA[2]/__pntA[3]
```
# Generic
## Point, Vector, and Transform matrix
```
#pragma region <VTYPE>_geometry_3D_basic_data_types
typedef SLC<VTYPE>_t *SLCPnt<VTYPE>_t, *SLCVec<VTYPE>_t, *SLCTMat<VTYPE>_t;
typedef const SLC<VTYPE>_t *SLCCPnt<VTYPE>_t, *SLCCVec<VTYPE>_t, *SLCCTMat<VTYPE>_t;
#pragma endregion <VTYPE>_geometry_3D_basic_data_types
```
## Rotation and Linear Translate
```
/*!
\brief Generic 3D transform by a generic transform matrix
\param tmat [in] The transform matrix
\param pnt [in] The point to transform
\param work [in] working memory block with the size of four dimensional number array
\return same as work filled with the transformed point
*/
SLCCPnt<VTYPE>_t SLCTMat<VTYPE>_Transform(
    SLCCTMat<VTYPE>_t tmat, SLCCPnt<VTYPE>_t pnt, SLCPnt<VTYPE>_t work);

/*!
\brief create an identity 4x4 matrix
*/
SLCCTMat<VTYPE>_t SLCTMat<VTYPE>_Identity();

/*!
\brief Linear translation matrix
\param move [in] linear moving vector
\param work [in] working memory block with the size of 4x4 matrix
\return same as work filled with the translate matrix
*/
SLCCTMat<VTYPE>_t SLCTMat<VTYPE>_Translate(SLCCVec<VTYPE>_t move, SLCTMat<VTYPE>_t work);

/*!
\brief Rotation matrix around Z-axis
\param c [in] cosine of rotation angle
\param s [in] sine of rotation angle
\param work [in] working memory block with the size of 4x4 matrix
\return same as work filled with the translate matrix
*/
SLCCTMat<VTYPE>_t SLCTMat<VTYPE>_RotateZ(SLC<VTYPE>_t c, SLC<VTYPE>_t s, SLCTMat<VTYPE>_t work);
#define SLCTMat<VTYPE>_RotateZrad(__rad, __work) \
    SLCTMat<VTYPE>_RotateZ(SLC<VTYPE>cos(__rad), SLC<VTYPE>sin(__rad), __work)
#define SLCTMat<VTYPE>_RotateZdeg(__deg, __work) \
    SLCTMat<VTYPE>_RotateZrad(SLC<VTYPE>deg2rad(__deg), __work)

SLCCTMat<VTYPE>_t SLCTMat<VTYPE>_RotateX(SLC<VTYPE>_t c, SLC<VTYPE>_t s, SLCTMat<VTYPE>_t work);
#define SLCTMat<VTYPE>_RotateXrad(__rad, __work) \
    SLCTMat<VTYPE>_RotateX(SLC<VTYPE>cos(__rad), SLC<VTYPE>sin(__rad), __work)
#define SLCTMat<VTYPE>_RotateXdeg(__deg, __work) \
    SLCTMat<VTYPE>_RotateXrad(SLC<VTYPE>deg2rad(__deg), __work)

SLCCTMat<VTYPE>_t SLCTMat<VTYPE>_RotateY(SLC<VTYPE>_t c, SLC<VTYPE>_t s, SLCTMat<VTYPE>_t work);
#define SLCTMat<VTYPE>_RotateYrad(__rad, __work) \
    SLCTMat<VTYPE>_RotateY(SLC<VTYPE>cos(__rad), SLC<VTYPE>sin(__rad), __work)
#define SLCTMat<VTYPE>_RotateYdeg(__deg, __work) \
    SLCTMat<VTYPE>_RotateYrad(SLC<VTYPE>deg2rad(__deg), __work)
```
## Polar-Cartesian Conversion
```
typedef struct SLCPolar<VTYPE> {
    SLC<VTYPE>_t r, cphi, sphi, ctheta, stheta;
} SLCPolar<VTYPE>_t, *SLCPPolar<VTYPE>_t;
typedef const SLCPolar<VTYPE>_t *SLCPCPolar<VTYPE>_t;

/*!
\brief conversion from a Cartesian coordinte to a polar coordinate
\param polar [out] polar coordinate
\param cartesian [in] cartesian coordinate
*/
void SLCPolar<VTYPE>_FromCartesian(SLCPPolar<VTYPE>_t polar, SLCCPnt<VTYPE>_t cartesian);

/*!
\brief conversion from a polar coordinate to a Cartesian coordinate
\param cartesian [out] Cartesian coordinate
\param polar [in] polar coordinate
*/
void SLCPolar<VTYPE>_ToCartesian(SLCPnt<VTYPE>_t cartesian, SLCPCPolar<VTYPE>_t polar);
```
# Foot
```
#endif
```
