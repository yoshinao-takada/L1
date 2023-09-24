# Control
```
{
    "out": "NumbersCopy.c",
    "vtypes": ["r32", "r64", "c64", "c128"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
```
#include "SLC/NumbersCopy.h"
```
# Generic
```
#pragma region <VTYPE>_array_copy_functions
void SLC<VTYPE>_copy(SLC<VTYPE>_t* dst, SLC<ITYPE>_t dststep, const SLC<VTYPE>_t* src, SLC<ITYPE>_t srcstep, SLC<ITYPE>_t count)
{
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        *dst = *src;
        dst += dststep;
        src += srcstep;
    }
}

void SLC<VTYPE>_swap(SLC<VTYPE>_t* var0, SLC<ITYPE>_t step0, SLC<VTYPE>_t* var1, SLC<ITYPE>_t step1, SLC<ITYPE>_t count)
{
    SLC<VTYPE>_t temp;
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        temp = *var0;
        *var0 = *var1;
        *var1 = temp;
        var0 += step0;
        var1 += step1;
    }
}

void SLC<VTYPE>_gather(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src, SLC<ITYPE>_t srcstep, SLC<ITYPE>_t count)
{
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        *dst++ = *src;
        src += srcstep;
    }
}

void SLC<VTYPE>_scatter(SLC<VTYPE>_t* dst, SLC<ITYPE>_t dststep, const SLC<VTYPE>_t* src, SLC<ITYPE>_t count)
{
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        *dst = *src++;
        dst += dststep;
    }
}
#pragma endregion <VTYPE>_array_copy_functions
```
