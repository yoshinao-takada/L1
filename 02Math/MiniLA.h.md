# Control
```
{
    "out": "../include/SLC/MiniLA.h",
    "vtypes": ["r32", "r64", "c64", "c128"],
    "rtypes": ["r32", "r64", "r32", "r64"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
```
#if !defined(_02MATH_MINILA_H)
#define _02MATH_MINILA_H
#include "SLC/MiniBLAS.h"
#include "SLC/Array.h"
#include "SLC/errno.h"
#include <stdio.h>
// [Note about error detection]
// The matrix methods assume that matrix size mismatch errors are detected
// in developing time and do NOT check the errors in runtime.
// Only near singular matrix error is detected in runtime.
```
# Generic
## Basic matrix operations
```
#pragma region <VTYPE>_functions
// --- basic matrix operations ---
// dst = src0 + src1
void SLCMat<VTYPE>_Add(SLCPArray_t dst, SLCPCArray_t src0, SLCPCArray_t src1);

// dst = src0 * scale0 + src1 + scale1
void SLCMat<VTYPE>_ScaleAdd(SLCPArray_t dst, SLCPCArray_t src0, const SLC<VTYPE>_t* scale0,
    SLCPCArray_t src1, const SLC<VTYPE>_t* scale1);

// dst = src * scale
void SLCMat<VTYPE>_Scale(SLCPArray_t dst, SLCPCArray_t src, const SLC<VTYPE>_t* scale);

// dst = src0 * src1
// work holds the transpose of src1.
void SLCMat<VTYPE>_Multiply(SLCPArray_t dst, SLCPCArray_t src0, SLCPCArray_t src1, SLCPArray_t work);

// dst = transpose of src
void SLCMat<VTYPE>_Transpose(SLCPArray_t dst, SLCPCArray_t src);

// dst = transposed conjugate of src
void SLCMat<VTYPE>_TransConj(SLCPArray_t dst, SLCPCArray_t src);

// dst = invese of src. work holds a work matrix for Gaussian elimination.
SLCerrno_t SLCMat<VTYPE>_Inv(SLCPArray_t dst, SLCPCArray_t src, SLCPArray_t work);
```
## Constant matrix
```
// zero matrix
void SLCMat<VTYPE>_0(SLCPArray_t dst);

// identity matrix
void SLCMat<VTYPE>_I(SLCPArray_t dst);
```
## Linear equation solvers
```
// --- linear equation solvers ---
// solve fully determined linear equation
// left * dst = right, where left and right are known matrices.
// dst is the unknown solution.
// work is a matrix for Gaussian elimination and back assignment.
SLCerrno_t SLCMat<VTYPE>_Solve(
    SLCPArray_t dst, SLCPCArray_t left, SLCPCArray_t right, SLCPArray_t work);

// solve overly determined linear equation with an easy API hiding work matrices.
SLCerrno_t SLCMat<VTYPE>_EasySolveOD(SLCPArray_t dst, SLCPCArray_t left, SLCPCArray_t right);

typedef struct {
    SLCPArray_t leftT, /* transpose of left */
        leftTC, /* transpose-conjugate of left */
        leftTC_left, /* product of leftTC and left; i.e. leftTC * left */
        rightT, /* transpose of right */
        leftTC_right, /* product of leftTC and right; i.e. leftTC * right */
        work; /* work matrix for a fully determined linear equation, leftTC_left * dst = leftTC_right */
} SLCMat<VTYPE>_SolveODWorkMatSet_t, *SLCMat<VTYPE>_PSolveODWorkMatSet_t;

// create working matrix set for EasySolveOD
void SLCMat<VTYPE>_InitSolveODWorkMatSet(
    SLCPCArray_t left, SLCPCArray_t right, SLCMat<VTYPE>_PSolveODWorkMatSet_t wkset);

// solve overly determined linear equation with explicitly defined work matrices.
// It is a little quicker than the easy version.
SLCerrno_t SLCMat<VTYPE>_SolveOD(SLCPArray_t dst, SLCPCArray_t left, SLCPCArray_t right,
    SLCMat<VTYPE>_PSolveODWorkMatSet_t wkset);
```
## QR decomposition
```

// QR decomposition
void SLCMat<VTYPE>_QRD(SLCPArray_t dst, SLCPArray_t src);
```
## Utilities
```
// human readable print
void SLCMat<VTYPE>_Print(FILE* out, const char* header, SLCPArray_t mat, const char* footer);
#pragma endregion <VTYPE>_functions
```
# Foot
```
#endif
```
