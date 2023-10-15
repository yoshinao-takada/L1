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
## Includes
```
#include "SLC/LinePlane.h"
#include "SLC/MiniLA.h"
#include <errno.h>
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
## Plane-Line Crosssection
A point on a line, $\bold{P}$ is represented by
$$\begin{equation}
\bold{P} = \bold{P}_0 + A\bold{D}_0\text{,}
\end{equation}$$
where $\bold{P}_0$ is a reference point of the line, $A$ is an arbitrary scalar
number, and $\bold{D}_0$ is the direction vector of the line.
Any point $\bold{P}$ on the plane with the reference point $\bold{P}_1$ is
represented by
$$\begin{equation}
(\bold{P} - \bold{P}_1)\cdot{\bold{N}_1} = 0\text{,}
\end{equation}$$
where $\bold{P}_1$ is the reference point of the plane, $\bold{N}_1$ is the normal
vector of the plane.
Assigning $\bold{P}$ in (1) to (2),
$$\begin{equation}
(\bold{P}_0 + A\bold{D}_0 - \bold{P}_1)\cdot{\bold{N}_1} = 0\text{,}
\end{equation}$$
where $A$ is uniquely determined as $A_\text{CROSS}$,
$$\begin{equation}
A_\text{CROSS} = {{{(\bold{P}_1-\bold{P}_0)}\cdot{\bold{N}}_1}\over
    {\bold{D}_0}\cdot{\bold{N}_1}}\text{.}
\end{equation}$$
Assigning $A_\text{CROSS}$ to (11), the crosssection point coordinate is
$$\begin{equation}
\bold{P}_\text{CROSS} = \bold{P}_0 + A_\text{CROSS}\bold{D}_0\text{.}
\end{equation}$$
```
SLCerrno_t SLCPlane<VTYPE>_IntersectionLinePlane(
    SLCPCPlane<VTYPE>_t plane, SLCPCLine<VTYPE>_t line, SLCPnt<VTYPE>_t intersection
) {
    SLCerrno_t err = EXIT_SUCCESS;
    SLC4<VTYPE>_t _p1_p0;
    do {
        const SLC<VTYPE>_t d0_dot_n1 = SLCVec<VTYPE>_Dot(line->d0, plane->n0);
        if (SLC<VTYPE>_abs(d0_dot_n1) < (SLC<VTYPE>_stdtol * SLC<VTYPE>_stdtol))
        {
            err = SLC_ESINGULAR;
            break;
        }
        SLCCVec<VTYPE>_t p1_p0 = SLCVec<VTYPE>_ToVector(
            line->p0, plane->p0, _p1_p0);
        SLC<VTYPE>_t a_cross = SLCVec<VTYPE>_Dot(p1_p0, plane->n0) / d0_dot_n1;

        // calculate P_CROSS
        SLCVec<VTYPE>_ScaleAdd(line->p0, SLC<VTYPE>_units[1],
            line->d0, a_cross, intersection);
    } while (0);
    return err;
}
```
## Three Plane Crosssection
Any point $\bold{P}$ on a plane is represented by
$$\begin{equation}
(\bold{P} - \bold{P}_0)\cdot{\bold{N}_0} = 0\text{.}
\end{equation}$$
Organizing the equation for $\bold{P}$ with three planes (0, 1, 2),
$$\begin{equation}\begin{matrix}
    \bold{P}\cdot{\bold{N}_0} & = & \bold{P}_0\cdot{\bold{N}_0}\text{,} \\
    \bold{P}\cdot{\bold{N}_1} & = & \bold{P}_1\cdot{\bold{N}_1}\text{,} \\
    \bold{P}\cdot{\bold{N}_2} & = & \bold{P}_2\cdot{\bold{N}_2}\text{.} \\
\end{matrix}\end{equation}$$
Organizing them in a matrix formula,
$$\begin{equation}\begin{bmatrix}
n_\text{0x} & n_\text{0y} & n_\text{0z} \\
n_\text{1x} & n_\text{1y} & n_\text{1z} \\
n_\text{2x} & n_\text{2y} & n_\text{2z} \\
\end{bmatrix}\begin{bmatrix}
p_\text{x} \\ p_\text{y} \\ p_\text{z}
\end{bmatrix} = \begin{bmatrix}
\bold{P}_0\cdot{\bold{N}_0} \\
\bold{P}_1\cdot{\bold{N}_1} \\
\bold{P}_2\cdot{\bold{N}_2} \\
\end{bmatrix}\text{.}\end{equation}$$
Solving (18), the crosssection point is determined.
```
SLCerrno_t SLCPlane<VTYPE>_Intersection3Planes(
    SLCPCPlane<VTYPE>_t plane0, SLCPCPlane<VTYPE>_t plane1, SLCPCPlane<VTYPE>_t plane2,
    SLCPnt<VTYPE>_t intersection
) {
    SLCerrno_t err = EXIT_SUCCESS;
    SLCPArray_t left = NULL, right = NULL, work = NULL;
    SLCArray_t pxyz = { { sizeof(SLC<VTYPE>_t), 1, 3, 1 }, { intersection } };
    const SLCi16_t 
        left_size[] = { sizeof(SLC<VTYPE>_t), 3, 3, 1 },
        right_size[] = { sizeof(SLC<VTYPE>_t), 1, 3, 1 },
        work_size[] = { sizeof(SLC<VTYPE>_t), 4, 3, 1 };
    intersection[3] = SLC<VTYPE>_units[1]; // = 1.0;
    do {
        left = SLCArray_Alloc(left_size);
        right = SLCArray_Alloc(right_size);
        work = SLCArray_Alloc(work_size);
        if ((left == NULL) || (right == NULL) || (work == NULL))
        {
            err = ENOMEM;
            break;
        }

        // fill LHS matrix
        SLC<VTYPE>_t _1_n3 = SLC<VTYPE>_units[1]/plane0->n0[3];
        left->data.<VTYPE>[0] = plane0->n0[0] * _1_n3;
        left->data.<VTYPE>[1] = plane0->n0[1] * _1_n3;
        left->data.<VTYPE>[2] = plane0->n0[2] * _1_n3;
        _1_n3 = SLC<VTYPE>_units[1]/plane1->n0[3];
        left->data.<VTYPE>[3] = plane1->n0[0] * _1_n3;
        left->data.<VTYPE>[4] = plane1->n0[1] * _1_n3;
        left->data.<VTYPE>[5] = plane1->n0[2] * _1_n3;
        _1_n3 = SLC<VTYPE>_units[1]/plane2->n0[3];
        left->data.<VTYPE>[6] = plane2->n0[0] * _1_n3;
        left->data.<VTYPE>[7] = plane2->n0[1] * _1_n3;
        left->data.<VTYPE>[8] = plane2->n0[2] * _1_n3;
        // fill RHS matrix
        right->data.<VTYPE>[0] = SLCVec<VTYPE>_Dot(plane0->p0, plane0->n0);
        right->data.<VTYPE>[1] = SLCVec<VTYPE>_Dot(plane1->p0, plane1->n0);
        right->data.<VTYPE>[2] = SLCVec<VTYPE>_Dot(plane2->p0, plane2->n0);
        // Solve the equation
        if (EXIT_SUCCESS == (err = SLCMat<VTYPE>_Solve(&pxyz, left, right, work)))
        {
            break;
        }
    } while (0);
    SLCArray_SafeFree(left);
    SLCArray_SafeFree(right);
    SLCArray_SafeFree(work);
    return err;
}
```
## Two Plane Crosssection
A line exists as a crosssection of two planes if the planes are not parallel.
The planes are represented by
$$\begin{equation}\begin{matrix}
(\bold{P}-\bold{P}_0)\cdot{\bold{N}}_0 & = & 0\text{,}\\
(\bold{P}-\bold{P}_1)\cdot{\bold{N}}_1 & = & 0\text{.}
\end{matrix}\end{equation}$$
Any point on the crosssection line is represented by
$$\begin{equation}
\bold{P} = \bold{P}_2 + A(\bold{N}_0\times{\bold{N}_1})\text{,}
\end{equation}$$
because $\bold{N}_0\times{\bold{N}_1}$ is orthogonal to both $\bold{N}_0$ and
$\bold{N}_1$; i.e. parallel to the both plane.<br/>
$\bold{P}_2$ is unknown right now. By the way, a virtual third plane can be assumed.
The third plane is parallel to neither of the first plane or the second plane.
And the third plane have a reference point common to the first plane, $\bold{P}_0$
and the normal vector $\bold{N}_0\times\bold{N}_1$. Any point on the third plane
is represented by
$$\begin{equation}
(\bold{P} - \bold{P}_0)\cdot(\bold{N}_0\times\bold{N}_1) = 0\text{.}
\end{equation}$$
Combining (19) and (21) to determine $\bold{P}_2$ as a solution of the equation.
$$\begin{equation}\begin{matrix}
\bold{P}\cdot{\bold{N}_0} & = & \bold{P}_0\cdot{\bold{N}_0}\text{,} \\
\bold{P}\cdot{\bold{N}_1} & = & \bold{P}_1\cdot{\bold{N}_1}\text{,} \\
\bold{P}\cdot{(\bold{N}_0\times{\bold{N}_1})} & = & \bold{P}_0\cdot{(\bold{N}_0\times{\bold{N}_1})}\text{,}
\end{matrix}\end{equation}$$
Replacing $\bold{N}_0\times{\bold{N}_1}$ with $\bold{N}_2$, the equation is
$$\begin{equation}\begin{matrix}
\bold{P}\cdot{\bold{N}_0} & = & \bold{P}_0\cdot{\bold{N}_0}\text{,} \\
\bold{P}\cdot{\bold{N}_1} & = & \bold{P}_1\cdot{\bold{N}_1}\text{,} \\
\bold{P}\cdot{\bold{N}_2} & = & \bold{P}_0\cdot{\bold{N}_2}\text{.}
\end{matrix}\end{equation}$$
Rewriting in a matrix formula,
$$\begin{equation}\begin{bmatrix}
    n_{\text{0x}} & n_{\text{0y}} & n_{\text{0z}} \\
    n_{\text{1x}} & n_{\text{1y}} & n_{\text{1z}} \\
    n_{\text{2x}} & n_{\text{2y}} & n_{\text{2z}} \\
\end{bmatrix}\begin{bmatrix}
    p_\text{x} \\ p_\text{y} \\ p_\text{z}
\end{bmatrix} = \begin{bmatrix}
    \bold{P}_0\cdot{\bold{N}_0} \\
    \bold{P}_1\cdot{\bold{N}_1} \\
    \bold{P}_0\cdot{\bold{N}_2} \\
\end{bmatrix}\text{.}\end{equation}$$
Solving the equation, the solution is $\bold{P}_2$.
```
SLCerrno_t SLCPlane<VTYPE>_Intersection2Planes(
    SLCPCPlane<VTYPE>_t plane0, SLCPCPlane<VTYPE>_t plane1, SLCPLine<VTYPE>_t intersection
) {
    SLCerrno_t err = EXIT_SUCCESS;
    SLCPlane<VTYPE>_t plane2;
    SLC4<VTYPE>_t _p2, _n0_cross_n1;
    SLCcopy4(plane2.p0, plane0->p0);
    SLCVec<VTYPE>_Cross(plane0->n0, plane1->n0, _n0_cross_n1);
    SLCVec<VTYPE>_Normalize(_n0_cross_n1, plane2.n0);
    do {
        if (EXIT_SUCCESS != 
            (err = SLCPlane<VTYPE>_Intersection3Planes(plane0, plane1, &plane2, _p2)))
        {
            break;
        }
        SLCcopy4(intersection->p0, _p2);
        SLCcopy4(intersection->d0, plane2.n0);
    } while (0);
    return err;
}
```
# Foot
```
```
