# Control
```
{
    "out": "LinePlane.c",
    "vtypes": ["r32", "r64"],
    "rtypes": ["r32", "r64"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
```
#include "SLC/LinePlane.h"
```
# Generic
## Line Properties and Plane Properties
The line properties are determined by two points, __P__<sub>0</sub> and __P__<sub>1</sub>.
The reference point is equal to __P__<sub>0</sub>. The unit direction vector is
(__P__<sub>1</sub> - __P__<sub>0</sub>)/|__P__<sub>1</sub> - __P__<sub>0</sub>|.
```
SLCerrno_t SLCLine<VTYPE>_Property
(SLCPLine<VTYPE>_t line, SLCCPnt<VTYPE>_t p0, SLCCPnt<VTYPE>_t p1)
{
    SLC4<VTYPE>_t _p1_p0;
    SLCVec<VTYPE>_ToVector(p0, p1, _p1_p0);
    const SLC<VTYPE>_t AbsDiff_p1_p0 = SLC<VTYPE>_sqrt(SLCVec<VTYPE>_Dot(_p1_p0, _p1_p0));
    if (AbsDiff_p1_p0 < SLC<VTYPE>_stdtol)
    {
        return SLC_EDIVBY0;
    }
    SLCcopy4(line->p0, p0);
    SLCVec<VTYPE>_Normalize(_p1_p0, line->d0);
    return EXIT_SUCCESS;
}
```
A set of plane properties is determined by three points, __P__<sub>0</sub>, __P__<sub>1</sub> and __P__<sub>2</sub>. The plane normal is determined by cross-product of
(__P__<sub>1</sub> - __P__<sub>0</sub>) and (__P__<sub>2</sub> - __P__<sub>0</sub>).
The reference point is equal to __P__<sub>0</sub>. The API is defined as
```
SLCerrno_t SLCPlane<VTYPE>_Property
(SLCPPlane<VTYPE>_t plane, SLCCPnt<VTYPE>_t p0, SLCCPnt<VTYPE>_t p1, SLCCPnt<VTYPE>_t p2)
{
    SLC4<VTYPE>_t _p1_p0, _p2_p0, cross;
    SLCVec<VTYPE>_ToVector(p0, p1, _p1_p0);
    SLCVec<VTYPE>_ToVector(p0, p2, _p2_p0);
    SLCVec<VTYPE>_Cross(_p1_p0, _p2_p0, cross);
    const SLC<VTYPE>_t 
        AbsCross = SLC<VTYPE>_sqrt(SLCVec<VTYPE>_Dot(cross, cross)),
        _1 = SLC<VTYPE>_units[1];
    if (AbsCross < SLC<VTYPE>_stdtol)
    {
        return SLC_EDIVBY0;
    }
    SLCcopy4(plane->p0, p0);
    SLCVec<VTYPE>_Normalize(cross, plane->n0);
    return EXIT_SUCCESS;
}
```
## Foot Point of Normal Line to Line
A function to get a foot point of a normal line from a point to a line is described.
A line is represented by its reference point $\bold{\text{P}}_0$ and its unit direction vector $\bold{\text{D}}_0$. An arbitrary point $\bold{\text{P}}$ on the line and
a number $A$ have a relationship,
$$\begin{equation}
\bold{P} = \bold{P}_0 + A\bold{D}_0\text{.}
\end{equation}$$
Draw a line from $\bold{P}$ normal to the reference line. Consider a point apart from the reference line and on the normal line as $\bold{P}_\text{e}$.
A vector, $\bold{P}_\text{e} - \bold{P}$ is normal to the direction vector of the reference line, $\bold{\text{D}}_0$ as the next equation.
$$\begin{equation}
(\bold{P}_\text{e} - \bold{P})\cdot{\bold{D}_0} = 0\text{.}
\end{equation}$$
Assign $\bold{P}$ in (1) to (2),
$$\begin{equation}
(\bold{P}_\text{e} - \bold{P}_0 - A\bold{D}_0)\cdot{\bold{D}_0} = 0\text{.}
\end{equation}$$
$$\begin{equation}
A_\text{f} = A = (\bold{P}_\text{e} - \bold{P}_0)\cdot{\bold{D}_0}\text{,}
\end{equation}$$
where $A_\text{f}$ is a scalar number $A$ corresponding to the foot point of the
normal line. Then the foot point $\bold{P}_\text{f}$ is
$$\begin{equation}
\bold{P}_\text{f} = \bold{P}_0 + A_\text{f}\bold{D}_0\text{.}
\end{equation}$$
```
SLCCPnt<VTYPE>_t SLCLine<VTYPE>_Foot(
    SLCPCLine<VTYPE>_t line, SLCCPnt<VTYPE>_t pnt, SLCPnt<VTYPE>_t work
) {
    // Pe - P0
    SLC4<VTYPE>_t _pe_p0;
    SLCCVec<VTYPE>_t pe_p0 = SLCVec<VTYPE>_ToVector(line->p0, pnt, _pe_p0);

    // Af = <<(Pe - P0), D0>>
    SLC<VTYPE>_t af = SLCVec<VTYPE>_Dot(pe_p0, line->d0);

    // Pf
    return SLCVec<VTYPE>_ScaleAdd(
        line->p0, SLC<VTYPE>_units[1], line->d0, af, work);
}
```
## Foot Point of Normal Line to Plane
A function to get a foot point of a normal line from a point to a plane is described.
A plane is represented by its reference point $\bold{\text{P}}_0$ and its unit normal vector $\bold{\text{N}}_0$. An arbitrary point on the plane is represented as
$$\begin{equation}
(\bold{P} - \bold{P}_0)\cdot{\bold{N}_0} = 0\text{.}
\end{equation}$$
Considerinig an external point $\bold{P}_\text{e}$ apart from the reference plane,
and draw a normal line from the point to the plane,
an arbitarary point $\bold{P}$ on the line is represented by
$$\begin{equation}
\bold{P} = \bold{P}_\text{e} + A\bold{N}_0\text{,}
\end{equation}$$
where $A$ is an arbitrary scalar number.
Considering the intersection of the normal line and the reference plane, a scalar
number $A$ satisfies,
$$\begin{equation}
(\bold{P}_\text{e} + A\bold{N}_0 - \bold{P}_0)\cdot{\bold{N}_0} = 0\text{,}
\end{equation}$$
$$\begin{equation}
A_\text{f} = A = (\bold{P}_0 - \bold{P}_\text{e})\cdot{\bold{N}_0}\text{.}
\end{equation}$$
$A_\text{f}$ is the special case that point $\bold{P}$ is the foot of the normal line
to the plane. Assigning $A_\text{f}$ to (7), the foot point $\bold{P}_\text{f}$ is
represented by
$$\begin{equation}
\bold{P}_\text{f} =
\bold{P}_\text{e} + A_\text{f}\bold{N}_0
\text{.}
\end{equation}$$
```
SLCCPnt<VTYPE>_t SLCPlane<VTYPE>_Foot(
    SLCPCPlane<VTYPE>_t plane, SLCCPnt<VTYPE>_t pnt, SLCPnt<VTYPE>_t work
) {
    // P0 - Pe
    SLC4<VTYPE>_t _p0_pe;
    SLCCVec<VTYPE>_t p0_pe = SLCVec<VTYPE>_ToVector(pnt, plane->p0, _p0_pe);

    // Af = <<P0 - Pe, N0>>
    const SLC<VTYPE>_t af = SLCVec<VTYPE>_Dot(p0_pe, plane->n0);

    // Pf = Pe + Af*N0
    return SLCVec<VTYPE>_ScaleAdd(pnt, SLC<VTYPE>_units[1], plane->n0, af, work);
}
```
Functions to discriminate a point is on a line or on a plane.
```
SLCbool_t SLCLine<VTYPE>_IsOn(
    SLCPCLine<VTYPE>_t line, SLCCPnt<VTYPE>_t pnt, SLC<RTYPE>_t tol
) {
    SLC4<VTYPE>_t _foot, _pnt_foot;
    SLCCPnt<VTYPE>_t foot = SLCLine<VTYPE>_Foot(line, pnt, _foot);
    SLCCVec<VTYPE>_t pnt_foot = SLCVec<VTYPE>_ToVector(pnt, foot, _pnt_foot);
    const SLC<VTYPE>_t sqdistance = SLCVec<VTYPE>_Dot(pnt_foot, pnt_foot);
    return sqdistance < (SLC<VTYPE>_stdtol * SLC<VTYPE>_stdtol);
}

SLCbool_t SLCPlane<VTYPE>_IsOn(
    SLCPCPlane<VTYPE>_t plane, SLCCPnt<VTYPE>_t pnt, SLC<RTYPE>_t tol
) {
    SLC4<VTYPE>_t _foot, _pnt_foot;
    SLCCPnt<VTYPE>_t foot = SLCPlane<VTYPE>_Foot(plane, pnt, _foot);
    SLCCVec<VTYPE>_t pnt_foot = SLCVec<VTYPE>_ToVector(pnt, foot, _pnt_foot);
    const SLC<VTYPE>_t sqdistance = SLCVec<VTYPE>_Dot(pnt_foot, pnt_foot);
    return sqdistance < (SLC<VTYPE>_stdtol * SLC<VTYPE>_stdtol);
}
```
# Foot
```
```
