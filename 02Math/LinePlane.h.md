# Control
```
{
    "out": "../include/SLC/LinePlane.h",
    "vtypes": ["r32", "r64"],
    "rtypes": ["r32", "r64"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
```
#if !defined(_02MATH_MINILA_H)
#define _02MATH_LINEPLANE_H
#include "SLC/Numbers.h"
#include "SLC/NumbersCopy.h"
#include "SLC/Geom3D.h"
#include "SLC/errno.h"
#include <stdio.h>
```
# Generic
## Line Properties and Plane Properties
## Data Structures
Line and plane properties are declared as
```
// A line and a plane can be represented by a point and a unit vector.
typedef struct {
    SLC4<VTYPE>_t p0; // reference point
    SLC4<VTYPE>_t d0; // a unit vector of line direction
} SLCLine<VTYPE>_t, *SLCPLine<VTYPE>_t;
typedef const SLCLine<VTYPE>_t *SLCPCLine<VTYPE>_t;

// A line and a plane can be represented by a point and a unit vector.
typedef struct {
    SLC4<VTYPE>_t p0; // reference point
    SLC4<VTYPE>_t n0; // a unit vector normal to a plane
} SLCPlane<VTYPE>_t, *SLCPPlane<VTYPE>_t;
typedef const SLCPlane<VTYPE>_t *SLCPCPlane<VTYPE>_t;
```
## Line
A line is represented by a point $\bold{P}_0$ and a direction vector $\bold{D}$ ($|\bold{D}| = 1$).  
An arbitrary point 
$\bold{P}$ in the line and an arbitrary number $A$ have a relationship,
$$\begin{equation}
\bold{P} = \bold{P}_0 + A\bold{D}\text{.}
\end{equation}$$

## Plane
A plane is represented by a point $\bold{P}_0$ and a normal vector $\bold{N}$ ($|\bold{N}| = 1$).  
An arbitrary point $\bold{P}$ in the plane satisfies
$$\begin{equation}
(\bold{P} - \bold{P}_0)\cdot\bold{N} = 0.
\end{equation}$$

## APIs
The API to get a set of line properties are declared here.
```
/*!
\brief Create a line object from two 3D points in homobeneous coordinate
\param line [out] line object
\param p0 [in] a point
\param p1 [in] another point
\return SLC_ESINGULAR if p0 and p1 are too close.
*/
SLCerrno_t SLCLine<VTYPE>_Property
(SLCPLine<VTYPE>_t line, SLCCPnt<VTYPE>_t p0, SLCCPnt<VTYPE>_t p1);
```
The API to get a set of plane properties is declared here.
```
/*!
\brief Create a plane object from three 3D points in homobeneous coordinate
\param plane [out] plane object
\param p0 [in] a point
\param p1 [in] another point
\param p2 [in] 2nd another point
\return SLC_ESINGULAR if |(p1-p0)x(p2-p0)| is too small
*/
SLCerrno_t SLCPlane<VTYPE>_Property
(SLCPPlane<VTYPE>_t plane, SLCCPnt<VTYPE>_t p0, SLCCPnt<VTYPE>_t p1, SLCCPnt<VTYPE>_t p2);
```
The APIs to get a foot point of a normal line from a point to a line or to a plane.
```
/*!
\brief Get a foot point of a normal line from a point to a line.
\param line [in] A set of properties of the line.
\param pnt [in] The point.
\param work [in] The working memory block used as the return value.
\return The foot point
*/
SLCCPnt<VTYPE>_t SLCLine<VTYPE>_Foot(
    SLCPCLine<VTYPE>_t line, SLCCPnt<VTYPE>_t pnt, SLCPnt<VTYPE>_t work);

/*!
\brief Get a foot point of a normal line from a point to a plane.
\param plane [in] A set of properties of the plane.
\param pnt [in] The point.
\param work [in] The working memory block used as the return value.
\return The foot point
*/
SLCCPnt<VTYPE>_t SLCPlane<VTYPE>_Foot(
    SLCPCPlane<VTYPE>_t plane, SLCCPnt<VTYPE>_t pnt, SLCPnt<VTYPE>_t work);
```
The APIs to determin whether a point is on a line is declared here.
```
/*!
\brief Determine whether a point is on a line.
\param line [in] a set of properties of a linear line
\param pnt [in] a point
\param tol [in] criteria to discriminate an innerproduct of two unit vectors is
nearly equal to 1 or not.
\return true: pnt is on the line, false: pnt is NOT on the line.
*/
SLCbool_t SLCLine<VTYPE>_IsOn(SLCPCLine<VTYPE>_t line, SLCCPnt<VTYPE>_t pnt,
    SLC<RTYPE>_t tol);
```
The API to determin whether a point is on a plane is declared here.
```
/*!
\brief Return false if pnt is not on a plane.
\param plane [in] reference plane
\param pnt [in] target point to discriminate
\param tol [in] criteria to discriminate an inner product of two unit vectors is nearly equal to 0 or not.
\return true: pnt is on the plane, false: pnt is NOT on the plane.
*/
SLCbool_t SLCPlane<VTYPE>_IsOn(SLCPCPlane<VTYPE>_t plane, SLCCPnt<VTYPE>_t pnt,
    SLC<RTYPE>_t tol);
```
# Foot
```
#endif
```
