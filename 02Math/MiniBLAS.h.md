# Control
```
{
    "out": "../include/SLC/MiniBLAS.h",
    "vtypes": ["r32", "r64", "c64", "c128"],
    "rtypes": ["r32", "r64", "r32", "r64"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
```
#if !defined(_02MATH_MINIBLAS_H)
#define _02MATH_MINIBLAS_H
#include "SLC/Numbers.h"
```

# Generic
```
#pragma region <VTYPE>_functions
// additional assignment (dst += src)
void SLCBLAS<VTYPE>_AddAss(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src, SLC<ITYPE>_t count);

// scaling assignment (dst *= scale)
void SLCBLAS<VTYPE>_ScaleAss(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* scale, SLC<ITYPE>_t count);

// scaling additional assignment (dst += src * scale)
void SLCBLAS<VTYPE>_ScaleAddAss(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src, const SLC<VTYPE>_t* scale, SLC<ITYPE>_t count);

// element-by-element operation has a secondary postfix L'ebe'
// element-by-element multiplication assignment
void SLCBLAS<VTYPE>_MultiplyEbeAss(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src, SLC<ITYPE>_t count);
```
```

// non-assignment addition; i.e. +=
void SLCBLAS<VTYPE>_Add(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src0, const SLC<VTYPE>_t* src1, SLC<ITYPE>_t count);

// non-assignment scaling; i.e. *=
void SLCBLAS<VTYPE>_Scale(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src, const SLC<VTYPE>_t* scale, SLC<ITYPE>_t count);

// non-assignment scaling addition; i.e. += scale0 * src0[i] + scale1 * src1[i]
void SLCBLAS<VTYPE>_ScaleAdd(
    SLC<VTYPE>_t* dst, 
    const SLC<VTYPE>_t* src0, const SLC<VTYPE>_t* scale0, 
    const SLC<VTYPE>_t* src1, const SLC<VTYPE>_t* scale1,
    SLC<ITYPE>_t count);

// element-by-element operation has a postfix 'ebe'
// element-by-element product
void SLCBLAS<VTYPE>_MultiplyEbe(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src0, const SLC<VTYPE>_t* src1, SLC<ITYPE>_t count);

// it is effective only for complex numbers. in the case of real numbers, it is same as copy.
void SLCBLAS<VTYPE>_CopyConj(
    SLC<VTYPE>_t* dst, SLC<ITYPE>_t dst_step,
    const SLC<VTYPE>_t* src, SLC<ITYPE>_t src_step,
    SLC<ITYPE>_t count
);
```
```

//--- vector-in, scalar-out operation identifier does not have any postfix. ---
// inner product (sum(src0[]*conj(src1[])))
SLC<VTYPE>_t SLCBLAS<VTYPE>_InnerProduct(const SLC<VTYPE>_t* src0, const SLC<VTYPE>_t* src1, SLC<ITYPE>_t count);

// product-sum (sum(src0[]*src1[]))
SLC<VTYPE>_t SLCBLAS<VTYPE>_ProductSum(const SLC<VTYPE>_t* src0, const SLC<VTYPE>_t* src1, SLC<ITYPE>_t count);

// sum of elements in an array
SLC<VTYPE>_t SLCBLAS<VTYPE>_Sum(const SLC<VTYPE>_t* src, SLC<ITYPE>_t count);

// absolute sum of elements in an array
SLC<RTYPE>_t SLCBLAS<VTYPE>_AbsSum(const SLC<VTYPE>_t* src, SLC<ITYPE>_t count);
#pragma endregion <VTYPE>_functions
```

# Foot
```
#endif
```
