# Control
```
{
    "out": "Geom3D.c",
    "vtypes": ["r32", "r64"],
    "rtypes": ["r32", "r64"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
```
#include "SLC/Geom3D.h"
#include "SLC/NumbersCopy.h"
#include <stdio.h>
#include <memory.h>
```
# Generic
## Generic Transform and Linear translation
Linear translation is represented by a matrix
$$\begin{equation}\begin{bmatrix}
1 && 0 && 0 && x \\
0 && 1 && 0 && y \\
0 && 0 && 1 && z \\
0 && 0 && 0 && 1
\end{bmatrix}\end{equation}$$

The following functions are defined to create rotation transform matrices.

```
SLCCPnt<VTYPE>_t SLCTMat<VTYPE>_Transform(
    SLCCTMat<VTYPE>_t tmat, SLCCPnt<VTYPE>_t pnt, SLCPnt<VTYPE>_t work
) {
    work[0] = tmat[0] * pnt[0] + tmat[1] * pnt[1] + tmat[2] * pnt[2] + tmat[3] * pnt[3];
    work[1] = tmat[4] * pnt[0] + tmat[5] * pnt[1] + tmat[6] * pnt[2] + tmat[7] * pnt[3];
    work[2] = tmat[8] * pnt[0] + tmat[9] * pnt[1] + tmat[10] * pnt[2] + tmat[11] * pnt[3];
    work[3] = tmat[12] * pnt[0] + tmat[13] * pnt[1] + tmat[14] * pnt[2] + tmat[15] * pnt[3];
    return work;
}

static const SLC<VTYPE>_t SLCTMat<VTYPE>_IDENTITY[] = {
    (SLC<VTYPE>_t)1, (SLC<VTYPE>_t)0, (SLC<VTYPE>_t)0, (SLC<VTYPE>_t)0,
    (SLC<VTYPE>_t)0, (SLC<VTYPE>_t)1, (SLC<VTYPE>_t)0, (SLC<VTYPE>_t)0,
    (SLC<VTYPE>_t)0, (SLC<VTYPE>_t)0, (SLC<VTYPE>_t)1, (SLC<VTYPE>_t)0,
    (SLC<VTYPE>_t)0, (SLC<VTYPE>_t)0, (SLC<VTYPE>_t)0, (SLC<VTYPE>_t)1
};

SLCCTMat<VTYPE>_t SLCTMat<VTYPE>_Identity() { return SLCTMat<VTYPE>_IDENTITY; }

SLCCTMat<VTYPE>_t SLCTMat<VTYPE>_Translate(SLCCVec<VTYPE>_t move, SLCTMat<VTYPE>_t work
) {
    // fill with 4x4 identity matrix
    memcpy(work, SLCTMat<VTYPE>_Identity(), sizeof(SLCTMat<VTYPE>_IDENTITY));

    // copy move to work
    const SLC<VTYPE>_t _1_move_w = SLC<VTYPE>_units[1] / move[3];
    const SLC3<VTYPE>_t _move = { move[0] * _1_move_w, move[1] * _1_move_w, move[2] * _1_move_w };
    SLC<VTYPE>_copy(work + 3, 4, _move, 1, 3);
    
    return work;
}
```
## Rotation matrix around basic axes
CCW rotation seen from positive Z axis is defined as
$$\begin{equation}\begin{bmatrix}x_1 \\ y_1\end{bmatrix}=\begin{bmatrix}
    \cos(A_{\text{z}}) & -\sin(A_{\text{z}}) \\
    \sin(A_{\text{z}}) & \cos(A_{\text{z}}) \\
\end{bmatrix}\begin{bmatrix}x_0 \\ y_0\end{bmatrix}
\end{equation}$$
, where $A_{\text{z}}$ is a rotatioin angle in radian. Extending the above into 3-D,
$$\begin{equation}
\begin{bmatrix}x_1 \\ y_1 \\ z_1 \end{bmatrix}\begin{bmatrix}
    \cos(A_{\text{z}}) & -\sin(A_{\text{z}}) & 0 \\
    \sin(A_{\text{z}}) & \cos(A_{\text{z}}) & 0 \\
    0 & 0 & 1
\end{bmatrix}\begin{bmatrix}x_0 \\ y_0 \\ z_0 \end{bmatrix}
\end{equation}$$
CCW rotatioon seen from positive X asis is defined as
$$\begin{equation}\begin{bmatrix}y_1 \\ z_1\end{bmatrix}\begin{bmatrix}
\cos(A_{\text{x}}) & -\sin(A_{\text{x}}) \\
\sin(A_{\text{x}}) & \cos(A_{\text{x}})
\end{bmatrix}\begin{bmatrix}y_0 \\ z_0\end{bmatrix}
\end{equation}$$
, where $A_\text{x}$ is a rotatioin angle in radian. Extending the above into 3-D,
$$\begin{equation}\begin{bmatrix}x_1 \\ y_1 \\ z_1\end{bmatrix}\begin{bmatrix}
1 & 0 & 0 \\
0 & \cos(A_{\text{x}}) & -\sin(A_{\text{x}}) \\
0 & \sin(A_{\text{x}}) & \cos(A_{\text{x}})
\end{bmatrix}\begin{bmatrix}x_0 \\ y_0 \\ z_0\end{bmatrix}
\end{equation}$$
CCW rotation seen from positive Y axis is defined as
$$\begin{equation}\begin{bmatrix}z_1 \\ x_1\end{bmatrix}\begin{bmatrix}
\cos(A_\text{y}) & -\sin(A_\text{y}) \\
\sin(A_\text{y}) & \cos(A_\text{y}) \\
\end{bmatrix}\begin{bmatrix}z_0 \\ x_0\end{bmatrix}
\end{equation}$$
Swapping (row0 and row1) and (column0 and column1),
$$\begin{equation}\begin{bmatrix}x_1 \\ z_1\end{bmatrix}\begin{bmatrix}
\cos(A_\text{y}) & \sin(A_\text{y}) \\
-\sin(A_\text{y}) & \cos(A_\text{y}) \\
\end{bmatrix}\begin{bmatrix}x_0 \\ z_0\end{bmatrix}
\end{equation}$$
, where $A_\text{y}$ is a rotatioin angle in radian. Extending the above into 3-D,
$$\begin{equation}\begin{bmatrix}x_1 \\ y_1 \\ z_1\end{bmatrix}\begin{bmatrix}
\cos(A_\text{y}) & 0 & \sin(A_\text{y}) \\
0 & 1 & 0 \\
-\sin(A_\text{y}) & 0 & \cos(A_\text{y}) \\
\end{bmatrix}
\begin{bmatrix}x_0 \\ y_0 \\ z_0 \end{bmatrix}
\end{equation}$$
Arbitrary rotation in 3-D space is defined by a product of (2), (4), and (7),
$$\begin{equation}\begin{bmatrix}(2)\end{bmatrix}\begin{bmatrix}(4)\end{bmatrix}\begin{bmatrix}(7)\end{bmatrix} =
\begin{bmatrix}
c_\text{z}c_\text{y}-s_\text{z}s_\text{x}s_\text{y} && -s_\text{z}c_\text{x} && c_\text{z}s_\text{y}+s_\text{z}s_\text{x}c_\text{y} \\
s_\text{z}c_\text{y}+c_\text{z}s_\text{x}s_\text{y} && c_\text{z}c_\text{x} && s_\text{z}s_\text{y}-c_\text{z}s_\text{x}c_\text{y} \\
-c_\text{x}s_\text{y} && s_\text{x} && c_\text{x}c_\text{y}
\end{bmatrix}
\end{equation}$$
For homogenous coordinate, (8) is rewriten as
$$\begin{equation}\begin{bmatrix}
c_\text{z}c_\text{y}-s_\text{z}s_\text{x}s_\text{y} && -s_\text{z}c_\text{x} && c_\text{z}s_\text{y}+s_\text{z}s_\text{x}c_\text{y} && 0 \\
s_\text{z}c_\text{y}+c_\text{z}s_\text{x}s_\text{y} && c_\text{z}c_\text{x} && s_\text{z}s_\text{y}-c_\text{z}s_\text{x}c_\text{y} && 0 \\
-c_\text{x}s_\text{y} && s_\text{x} && c_\text{x}c_\text{y} && 0 \\
0 && 0 && 0 && 1
\end{bmatrix}\end{equation}$$
```
SLCCTMat<VTYPE>_t SLCTMat<VTYPE>_RotateZ(SLC<VTYPE>_t c, SLC<VTYPE>_t s, SLCTMat<VTYPE>_t work)
{
    // fill with 4x4 identity matrix
    memcpy(work, SLCTMat<VTYPE>_Identity(), sizeof(SLCTMat<VTYPE>_IDENTITY));

    work[0] = work[5] = c;
    work[1] = -(work[4] = s);
    return work;
}

SLCCTMat<VTYPE>_t SLCTMat<VTYPE>_RotateX(SLC<VTYPE>_t c, SLC<VTYPE>_t s, SLCTMat<VTYPE>_t work)
{
    // fill with 4x4 identity matrix
    memcpy(work, SLCTMat<VTYPE>_Identity(), sizeof(SLCTMat<VTYPE>_IDENTITY));

    work[5] = work[10] = c;
    work[6] = -(work[9] = s);
    return work;
}

SLCCTMat<VTYPE>_t SLCTMat<VTYPE>_RotateY(SLC<VTYPE>_t c, SLC<VTYPE>_t s, SLCTMat<VTYPE>_t work)
{
    // fill with 4x4 identity matrix
    memcpy(work, SLCTMat<VTYPE>_Identity(), sizeof(SLCTMat<VTYPE>_IDENTITY));

    work[0] = work[10] = c;
    work[8] = -(work[2] = s);
    return work;
}

```
## Polar-Cartesian Conversion
A polar coordinate is represented by  
$r$ : a distance from the origin,  
$\theta$ : elevation angle from Z-plane,  
$\phi$ : azimuthal angle from X-axis,  
and the relationship between the polar coordinate and the cartesian coordinate is
$$\begin{equation}\begin{matrix}
x & = & r\cos(\theta)\cos(\phi) & = & r c_\theta c_\phi \\
y & = & r\cos(\theta)\sin(\phi) & = & r c_\theta s_\phi \\
z & = & r\sin(\theta) & = & r s_\theta\\
& & 1 &  = & {c_\theta}^2+{s_\theta}^2 \\
& & 1 & = & {c_\phi}^2+{s_\phi}^2
\end{matrix}\end{equation}$$
$$\begin{equation}
r = \sqrt(x^2+y^2+z^2)
\end{equation}$$
$$\begin{equation}
\cos(\theta) = \sqrt(x^2+y^2)/r, \sin(\theta)=z/r
\end{equation}$$
$$\begin{equation}
\cos(\phi)=x/\sqrt(x^2+y^2), \sin(\phi)=y/\sqrt(x^2+y^2)
\end{equation}$$

Getting the polar coordinate from the cartesian coordinate using Gauss-Newton method,
the objective function is

$$\begin{equation}\bold{F}(r,c_\theta, s_\theta, c_\phi, s_\phi) = \begin{bmatrix}
r c_\theta c_\phi - x \\
r c_\theta s_\phi - y \\
r s_\theta - z \\
{c_\theta}^2+{s_\theta}^2-1 \\
{c_\phi}^2+{s_\phi}^2-1 \\
\end{bmatrix} = \bold{0}
\end{equation}$$
Jacobian $\bold{J}$ is

$$\begin{equation}
\bold{J}=\begin{bmatrix}\frac{\partial\bold{F}}{\partial r} && \frac{\partial\bold{F}}{\partial c_\theta} && \frac{\partial\bold{F}}{\partial s_\theta} && \frac{\partial\bold{F}}{\partial c_\phi} && \frac{\partial\bold{F}}{\partial s_\phi} \end{bmatrix}\end{equation}$$

$$\begin{equation}
\frac{\partial\bold{F}}{\partial r} = \begin{bmatrix}
c_\theta c_\phi &
c_\theta s_\phi &
s_\theta & 0 & 0
\end{bmatrix}^t\end{equation}$$

$$\begin{equation}\frac{\partial\bold{F}}{\partial c_\theta} = \begin{bmatrix}r c_\phi & r s_\phi & 0 & 0 & 0
\end{bmatrix}^t\end{equation}$$

$$\begin{equation}\frac{\partial\bold{F}}{\partial s_\theta} = \begin{bmatrix}0 & 0 & r & 2 s_\theta & 0\end{bmatrix}^t\end{equation}$$

$$\begin{equation}
\frac{\partial\bold{F}}{\partial c_\phi} = \begin{bmatrix}
r c_\theta & 0 & 0 & 0 & 2c_\phi
\end{bmatrix}^t
\end{equation}$$

$$\begin{equation}
\frac{\partial\bold{F}}{\partial s_\phi} = \begin{bmatrix}
0 & r c_\theta & 0 & 0 & 2 s_\phi
\end{bmatrix}^t
\end{equation}$$

```
void SLCPolar<VTYPE>_FromCartesian(SLCPPolar<VTYPE>_t polar, SLCCPnt<VTYPE>_t cartesian)
{
    const SLC<VTYPE>_t _1_cartesian_w = SLC<VTYPE>_units[1]/cartesian[3];
    const SLC3<VTYPE>_t _cartesian = 
        { cartesian[0]/_1_cartesian_w, cartesian[1]/_1_cartesian_w, cartesian[2]/_1_cartesian_w };
    const SLC<VTYPE>_t L2NormXY = _cartesian[0]*_cartesian[0] + _cartesian[1]*_cartesian[1];
    const SLC<VTYPE>_t L2NormXYZ = L2NormXY + _cartesian[2]*_cartesian[2];
    const SLC<VTYPE>_t Rxy = SLC<VTYPE>sqrt(L2NormXY);
    polar->r = SLC<VTYPE>sqrt(L2NormXYZ);
    polar->ctheta = Rxy / polar->r;
    polar->stheta = _cartesian[2]/polar->r;
    polar->cphi = _cartesian[0]/Rxy;
    polar->sphi = _cartesian[1]/Rxy;
}

void SLCPolar<VTYPE>_ToCartesian(SLCPnt<VTYPE>_t cartesian, SLCPCPolar<VTYPE>_t polar)
{
    cartesian[0] = polar->r * polar->ctheta * polar->cphi;
    cartesian[1] = polar->r * polar->ctheta * polar->sphi;
    cartesian[2] = polar->r * polar->sphi;
    cartesian[3] = SLC<VTYPE>_units[1];
}

```
## Line Properties and Plane Properties
The line properties are determined by two points, __P__<sub>0</sub> and __P__<sub>1</sub>.
The reference point is equal to __P__<sub>0</sub>. The unit direction vector is
(__P__<sub>1</sub> - __P__<sub>0</sub>)/|__P__<sub>1</sub> - __P__<sub>0</sub>|.
```
SLCerrno_t SLCLine<VTYPE>_Property
(SLCPLinePlane<VTYPE>_t line, SLCCPnt<VTYPE>_t p0, SLCCPnt<VTYPE>_t p1)
{
    SLC4<VTYPE>_t _p1_p0;
    SLCVec<VTYPE>_From2Points(p0, p1, _p1_p0);
    const SLC<VTYPE>_t AbsDiff_p1_p0 = SLC<VTYPE>sqrt(SLCVec<VTYPE>_Dot(_p1_p0, _p1_p0));
    if (AbsDiff_p1_p0 < SLC<VTYPE>_stdtol)
    {
        return SLC_EDIVBY0;
    }
    SLCcopy4(line->p0, p0);
    line->v0[0] = _p1_p0[0]/AbsDiff_p1_p0;
    line->v0[1] = _p1_p0[1]/AbsDiff_p1_p0;
    line->v0[2] = _p1_p0[2]/AbsDiff_p1_p0;
    line->v0[3] = _p1_p0[3];
    return EXIT_SUCCESS;
}
```
A set of plane properties is determined by three points, __P__<sub>0</sub>, __P__<sub>1</sub> and __P__<sub>2</sub>. The plane normal is determined by cross-product of
(__P__<sub>1</sub> - __P__<sub>0</sub>) and (__P__<sub>2</sub> - __P__<sub>0</sub>).
The reference point is equal to __P__<sub>0</sub>. The API is defined as
```
SLCerrno_t SLCPlane<VTYPE>_Property
(SLCPLinePlane<VTYPE>_t plane, SLCCPnt<VTYPE>_t p0, SLCCPnt<VTYPE>_t p1, SLCCPnt<VTYPE>_t p2)
{
    SLCcopy4(plane->p0, p0);
    SLC4<VTYPE>_t _p1_p0, _p2_p0, cross;
    SLCVec<VTYPE>_From2Points(p0, p1, _p1_p0);
    SLCVec<VTYPE>_From2Points(p0, p2, _p2_p0);
    SLCVec<VTYPE>_Cross(_p1_p0, _p2_p0, cross);
    const SLC<VTYPE>_t 
        AbsCross = SLC<VTYPE>sqrt(SLCVec<VTYPE>_Dot(cross, cross)),
        _1 = SLC<VTYPE>_units[1];
    if (AbsCross < SLC<VTYPE>_stdtol)
    {
        return SLC_EDIVBY0;
    }
    const SLC<VTYPE>_t _1_AbsCross = _1/AbsCross;
    plane->v0[0] = cross[0] * _1_AbsCross;
    plane->v0[1] = cross[1] * _1_AbsCross;
    plane->v0[2] = cross[2] * _1_AbsCross;
    plane->v0[3] = _1;
    return EXIT_SUCCESS;
}
```
Basic vector operations are defined as
```
SLCCVec<VTYPE>_t SLCVec<VTYPE>_Cross(SLCCVec<VTYPE>_t v0, SLCCVec<VTYPE>_t v1, SLCVec<VTYPE>_t work)
{
    SLC<VTYPE>_t coeff = v0[3] * v1[3];
    work[0] = (v0[1] * v1[2] - v0[2] * v1[1]) * coeff;
    work[1] = (v0[2] * v1[0] - v0[0] * v1[2]) * coeff;
    work[2] = (v0[0] * v1[1] - v0[1] * v1[0]) * coeff;
    work[3] = (SLC<VTYPE>_t)1;
    return work;
}

SLC<VTYPE>_t SLCVec<VTYPE>_Dot(SLCCVec<VTYPE>_t v0, SLCCVec<VTYPE>_t v1)
{
    SLC<VTYPE>_t dot = 
        (v0[0] * v1[0] + v0[1] * v1[1] + v0[2] * v1[2])/(v0[3] * v1[3]);
    return dot;
}

SLCCVec<VTYPE>_t SLCVec<VTYPE>_From2Points(SLCCPnt<VTYPE>_t p0, SLCCPnt<VTYPE>_t p1, SLCVec<VTYPE>_t work)
{
    const SLC<VTYPE>_t _1 = SLC<VTYPE>_units[1];
    const SLC<VTYPE>_t _1_p0_w = _1 / p0[3];
    const SLC<VTYPE>_t _1_p1_w = _1 / p1[3];
    work[0] = p1[0] * _1_p1_w - p0[0] * _1_p0_w;
    work[1] = p1[1] * _1_p1_w - p0[1] * _1_p0_w;
    work[2] = p1[2] * _1_p1_w - p0[2] * _1_p0_w;
    work[3] = _1;
    return work;
}
```
# Foot
```
```
