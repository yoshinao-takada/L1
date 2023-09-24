#include "SLC/MiniBLAS.h"
#pragma region r32_basic_algebraic_operations
void SLCBLASr32_AddAss(SLCr32_t* dst, const SLCr32_t* src,         SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst += *src++;
    }
}

void SLCBLASr32_ScaleAss(SLCr32_t* dst, const SLCr32_t* scale, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ *= *scale;
    }
}

void SLCBLASr32_ScaleAddAss(SLCr32_t* dst, const SLCr32_t* src, const SLCr32_t* scale, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ += *src++ * *scale;
    }
}

void SLCBLASr32_multiplyEbeAss(SLCr32_t* dst, const SLCr32_t* src, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ *= *src++;
    }
}

void SLCBLASr32_Add(SLCr32_t* dst, const SLCr32_t* src0, const SLCr32_t* src1, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src0++ + *src1++;
    }
}

void SLCBLASr32_Scale(SLCr32_t* dst, const SLCr32_t* src, const SLCr32_t* scale, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src++ * *scale;
    }
}

void SLCBLASr32_ScaleAdd(
    SLCr32_t* dst, 
    const SLCr32_t* src0, const SLCr32_t* scale0, 
    const SLCr32_t* src1, const SLCr32_t* scale1,
    SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src0++ * *scale0 + *src1++ * *scale1;
    }
}

void SLCBLASr32_MultyplyEbe(SLCr32_t* dst, const SLCr32_t* src0, const SLCr32_t* src1, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src0++ * *src1++;
    }
}

void SLCBLASr32_CopyConj(
    SLCr32_t* dst, SLCi32_t dst_step,
    const SLCr32_t* src, SLCi32_t src_step,
    SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst = SLCr32_conj(*src);
        dst += dst_step;
        src += src_step;
    }
}

SLCr32_t SLCBLASr32_InnerProduct(const SLCr32_t* src0, const SLCr32_t* src1, SLCi32_t count
) {
    SLCr32_t result = (SLCr32_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += *src0++ * SLCr32_conj(*src1++);
    }
    return result;
}

SLCr32_t SLCBLASr32_ProductSum(const SLCr32_t* src0, const SLCr32_t* src1, SLCi32_t count
) {
    SLCr32_t result = (SLCr32_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += *src0++ * *src1++;
    }
    return result;
}

SLCr32_t SLCBLASr32_Sum(const SLCr32_t* src, SLCi32_t count)
{
    SLCr32_t result = (SLCr32_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += *src++;
    }
    return result;
}

SLCr32_t SLCBLASr32_AbsSum(const SLCr32_t* src, SLCi32_t count)
{
    SLCr32_t result = (SLCr32_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += SLCr32_abs(*src++);
    }
    return result;
}
#pragma endregion r32_basic_algebraic_operations
#pragma region r64_basic_algebraic_operations
void SLCBLASr64_AddAss(SLCr64_t* dst, const SLCr64_t* src,         SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst += *src++;
    }
}

void SLCBLASr64_ScaleAss(SLCr64_t* dst, const SLCr64_t* scale, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ *= *scale;
    }
}

void SLCBLASr64_ScaleAddAss(SLCr64_t* dst, const SLCr64_t* src, const SLCr64_t* scale, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ += *src++ * *scale;
    }
}

void SLCBLASr64_multiplyEbeAss(SLCr64_t* dst, const SLCr64_t* src, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ *= *src++;
    }
}

void SLCBLASr64_Add(SLCr64_t* dst, const SLCr64_t* src0, const SLCr64_t* src1, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src0++ + *src1++;
    }
}

void SLCBLASr64_Scale(SLCr64_t* dst, const SLCr64_t* src, const SLCr64_t* scale, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src++ * *scale;
    }
}

void SLCBLASr64_ScaleAdd(
    SLCr64_t* dst, 
    const SLCr64_t* src0, const SLCr64_t* scale0, 
    const SLCr64_t* src1, const SLCr64_t* scale1,
    SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src0++ * *scale0 + *src1++ * *scale1;
    }
}

void SLCBLASr64_MultyplyEbe(SLCr64_t* dst, const SLCr64_t* src0, const SLCr64_t* src1, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src0++ * *src1++;
    }
}

void SLCBLASr64_CopyConj(
    SLCr64_t* dst, SLCi32_t dst_step,
    const SLCr64_t* src, SLCi32_t src_step,
    SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst = SLCr64_conj(*src);
        dst += dst_step;
        src += src_step;
    }
}

SLCr64_t SLCBLASr64_InnerProduct(const SLCr64_t* src0, const SLCr64_t* src1, SLCi32_t count
) {
    SLCr64_t result = (SLCr64_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += *src0++ * SLCr64_conj(*src1++);
    }
    return result;
}

SLCr64_t SLCBLASr64_ProductSum(const SLCr64_t* src0, const SLCr64_t* src1, SLCi32_t count
) {
    SLCr64_t result = (SLCr64_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += *src0++ * *src1++;
    }
    return result;
}

SLCr64_t SLCBLASr64_Sum(const SLCr64_t* src, SLCi32_t count)
{
    SLCr64_t result = (SLCr64_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += *src++;
    }
    return result;
}

SLCr64_t SLCBLASr64_AbsSum(const SLCr64_t* src, SLCi32_t count)
{
    SLCr64_t result = (SLCr64_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += SLCr64_abs(*src++);
    }
    return result;
}
#pragma endregion r64_basic_algebraic_operations
#pragma region c64_basic_algebraic_operations
void SLCBLASc64_AddAss(SLCc64_t* dst, const SLCc64_t* src,         SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst += *src++;
    }
}

void SLCBLASc64_ScaleAss(SLCc64_t* dst, const SLCc64_t* scale, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ *= *scale;
    }
}

void SLCBLASc64_ScaleAddAss(SLCc64_t* dst, const SLCc64_t* src, const SLCc64_t* scale, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ += *src++ * *scale;
    }
}

void SLCBLASc64_multiplyEbeAss(SLCc64_t* dst, const SLCc64_t* src, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ *= *src++;
    }
}

void SLCBLASc64_Add(SLCc64_t* dst, const SLCc64_t* src0, const SLCc64_t* src1, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src0++ + *src1++;
    }
}

void SLCBLASc64_Scale(SLCc64_t* dst, const SLCc64_t* src, const SLCc64_t* scale, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src++ * *scale;
    }
}

void SLCBLASc64_ScaleAdd(
    SLCc64_t* dst, 
    const SLCc64_t* src0, const SLCc64_t* scale0, 
    const SLCc64_t* src1, const SLCc64_t* scale1,
    SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src0++ * *scale0 + *src1++ * *scale1;
    }
}

void SLCBLASc64_MultyplyEbe(SLCc64_t* dst, const SLCc64_t* src0, const SLCc64_t* src1, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src0++ * *src1++;
    }
}

void SLCBLASc64_CopyConj(
    SLCc64_t* dst, SLCi32_t dst_step,
    const SLCc64_t* src, SLCi32_t src_step,
    SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst = SLCc64_conj(*src);
        dst += dst_step;
        src += src_step;
    }
}

SLCc64_t SLCBLASc64_InnerProduct(const SLCc64_t* src0, const SLCc64_t* src1, SLCi32_t count
) {
    SLCc64_t result = (SLCc64_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += *src0++ * SLCc64_conj(*src1++);
    }
    return result;
}

SLCc64_t SLCBLASc64_ProductSum(const SLCc64_t* src0, const SLCc64_t* src1, SLCi32_t count
) {
    SLCc64_t result = (SLCc64_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += *src0++ * *src1++;
    }
    return result;
}

SLCc64_t SLCBLASc64_Sum(const SLCc64_t* src, SLCi32_t count)
{
    SLCc64_t result = (SLCc64_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += *src++;
    }
    return result;
}

SLCr32_t SLCBLASc64_AbsSum(const SLCc64_t* src, SLCi32_t count)
{
    SLCr32_t result = (SLCr32_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += SLCc64_abs(*src++);
    }
    return result;
}
#pragma endregion c64_basic_algebraic_operations
#pragma region c128_basic_algebraic_operations
void SLCBLASc128_AddAss(SLCc128_t* dst, const SLCc128_t* src,         SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst += *src++;
    }
}

void SLCBLASc128_ScaleAss(SLCc128_t* dst, const SLCc128_t* scale, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ *= *scale;
    }
}

void SLCBLASc128_ScaleAddAss(SLCc128_t* dst, const SLCc128_t* src, const SLCc128_t* scale, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ += *src++ * *scale;
    }
}

void SLCBLASc128_multiplyEbeAss(SLCc128_t* dst, const SLCc128_t* src, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ *= *src++;
    }
}

void SLCBLASc128_Add(SLCc128_t* dst, const SLCc128_t* src0, const SLCc128_t* src1, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src0++ + *src1++;
    }
}

void SLCBLASc128_Scale(SLCc128_t* dst, const SLCc128_t* src, const SLCc128_t* scale, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src++ * *scale;
    }
}

void SLCBLASc128_ScaleAdd(
    SLCc128_t* dst, 
    const SLCc128_t* src0, const SLCc128_t* scale0, 
    const SLCc128_t* src1, const SLCc128_t* scale1,
    SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src0++ * *scale0 + *src1++ * *scale1;
    }
}

void SLCBLASc128_MultyplyEbe(SLCc128_t* dst, const SLCc128_t* src0, const SLCc128_t* src1, SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst++ = *src0++ * *src1++;
    }
}

void SLCBLASc128_CopyConj(
    SLCc128_t* dst, SLCi32_t dst_step,
    const SLCc128_t* src, SLCi32_t src_step,
    SLCi32_t count
) {
    for (SLCi32_t i = 0; i < count; i++)
    {
        *dst = SLCc128_conj(*src);
        dst += dst_step;
        src += src_step;
    }
}

SLCc128_t SLCBLASc128_InnerProduct(const SLCc128_t* src0, const SLCc128_t* src1, SLCi32_t count
) {
    SLCc128_t result = (SLCc128_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += *src0++ * SLCc128_conj(*src1++);
    }
    return result;
}

SLCc128_t SLCBLASc128_ProductSum(const SLCc128_t* src0, const SLCc128_t* src1, SLCi32_t count
) {
    SLCc128_t result = (SLCc128_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += *src0++ * *src1++;
    }
    return result;
}

SLCc128_t SLCBLASc128_Sum(const SLCc128_t* src, SLCi32_t count)
{
    SLCc128_t result = (SLCc128_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += *src++;
    }
    return result;
}

SLCr64_t SLCBLASc128_AbsSum(const SLCc128_t* src, SLCi32_t count)
{
    SLCr64_t result = (SLCr64_t)0;
    for (SLCi32_t i = 0; i < count; i++)
    {
        result += SLCc128_abs(*src++);
    }
    return result;
}
#pragma endregion c128_basic_algebraic_operations
