# Control
```
{
    "out": "MiniBLAS.c",
    "vtypes": ["r32", "r64", "c64", "c128"],
    "rtypes": ["r32", "r64", "r32", "r64"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
```
#include "SLC/MiniBLAS.h"
```

# Generic
```
#pragma region <VTYPE>_basic_algebraic_operations
void SLCBLAS<VTYPE>_AddAss(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src,         SLC<ITYPE>_t count
) {
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        *dst += *src++;
    }
}

void SLCBLAS<VTYPE>_ScaleAss(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* scale, SLC<ITYPE>_t count
) {
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        *dst++ *= *scale;
    }
}

void SLCBLAS<VTYPE>_ScaleAddAss(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src, const SLC<VTYPE>_t* scale, SLC<ITYPE>_t count
) {
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        *dst++ += *src++ * *scale;
    }
}

void SLCBLAS<VTYPE>_multiplyEbeAss(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src, SLC<ITYPE>_t count
) {
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        *dst++ *= *src++;
    }
}
```
```

void SLCBLAS<VTYPE>_Add(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src0, const SLC<VTYPE>_t* src1, SLC<ITYPE>_t count
) {
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        *dst++ = *src0++ + *src1++;
    }
}

void SLCBLAS<VTYPE>_Scale(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src, const SLC<VTYPE>_t* scale, SLC<ITYPE>_t count
) {
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        *dst++ = *src++ * *scale;
    }
}

void SLCBLAS<VTYPE>_ScaleAdd(
    SLC<VTYPE>_t* dst, 
    const SLC<VTYPE>_t* src0, const SLC<VTYPE>_t* scale0, 
    const SLC<VTYPE>_t* src1, const SLC<VTYPE>_t* scale1,
    SLC<ITYPE>_t count
) {
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        *dst++ = *src0++ * *scale0 + *src1++ * *scale1;
    }
}

void SLCBLAS<VTYPE>_MultyplyEbe(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src0, const SLC<VTYPE>_t* src1, SLC<ITYPE>_t count
) {
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        *dst++ = *src0++ * *src1++;
    }
}

void SLCBLAS<VTYPE>_CopyConj(
    SLC<VTYPE>_t* dst, SLC<ITYPE>_t dst_step,
    const SLC<VTYPE>_t* src, SLC<ITYPE>_t src_step,
    SLC<ITYPE>_t count
) {
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        *dst = SLC<VTYPE>_conj(*src);
        dst += dst_step;
        src += src_step;
    }
}
```
```

SLC<VTYPE>_t SLCBLAS<VTYPE>_InnerProduct(const SLC<VTYPE>_t* src0, const SLC<VTYPE>_t* src1, SLC<ITYPE>_t count
) {
    SLC<VTYPE>_t result = (SLC<VTYPE>_t)0;
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        result += *src0++ * SLC<VTYPE>_conj(*src1++);
    }
    return result;
}

SLC<VTYPE>_t SLCBLAS<VTYPE>_ProductSum(const SLC<VTYPE>_t* src0, const SLC<VTYPE>_t* src1, SLC<ITYPE>_t count
) {
    SLC<VTYPE>_t result = (SLC<VTYPE>_t)0;
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        result += *src0++ * *src1++;
    }
    return result;
}

SLC<VTYPE>_t SLCBLAS<VTYPE>_Sum(const SLC<VTYPE>_t* src, SLC<ITYPE>_t count)
{
    SLC<VTYPE>_t result = (SLC<VTYPE>_t)0;
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        result += *src++;
    }
    return result;
}

SLC<RTYPE>_t SLCBLAS<VTYPE>_AbsSum(const SLC<VTYPE>_t* src, SLC<ITYPE>_t count)
{
    SLC<RTYPE>_t result = (SLC<RTYPE>_t)0;
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        result += SLC<VTYPE>_abs(*src++);
    }
    return result;
}
#pragma endregion <VTYPE>_basic_algebraic_operations
```

# Foot
```
```
