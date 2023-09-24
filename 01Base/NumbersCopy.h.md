# Control
```
{
    "out": "../include/SLC/NumbersCopy.h",
    "vtypes": ["r32", "r64", "c64", "c128"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
```
#if !defined(_01BASE_NUMBERSCOPY_H)
#define _01BASE_NUMBERSCOPY_H
#include "SLC/Numbers.h"
```
# Generic
```
#pragma region <VTYPE>_array_copy_functions
/*!
\brief copy multiple elements in an array to another array.
\param dst [in] destination array pointer
\param dststep [in] step of elements in dst
\param src [in] source array pointer
\param srcstep [in] step of elements in src
\param count [in] numbers of elements to copy
*/
void SLC<VTYPE>_copy(SLC<VTYPE>_t* dst, SLC<ITYPE>_t dststep, const SLC<VTYPE>_t* src, SLC<ITYPE>_t srcstep, SLC<ITYPE>_t count);

/*!
\brief swap multiple elements in two arrays
\param var0 [in] pointer to an array
\param step0 [in] step of elements in var0
\param var1 [in] pointer to another array
\param step1 [in] step of elements in var1
\param count [in] numbers of elements to swap
*/
void SLC<VTYPE>_swap(SLC<VTYPE>_t* var0, SLC<ITYPE>_t step0, SLC<VTYPE>_t* var1, SLC<ITYPE>_t step1, SLC<ITYPE>_t count);

/*!
\brief special type of copy with destination step is 1
\param dst [in] destination array pointer
\param src [in] source array pointer
\param srcstep [in] step of elements in src
\param count [in] numbers of elements to copy
*/
void SLC<VTYPE>_gather(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src, SLC<ITYPE>_t srcstep, SLC<ITYPE>_t count);

/*!
\brief special type of copy with source step is 1
\param dst [in] destination array pointer
\param dststep [in] step of elements in dst
\param src [in] source array pointer
\param count [in] numbers of elements to copy
*/
void SLC<VTYPE>_scatter(SLC<VTYPE>_t* dst, SLC<ITYPE>_t dststep, const SLC<VTYPE>_t* src, SLC<ITYPE>_t count);
#pragma endregion <VALTYPE>_array_copy_functions
```
# Foot
```
#endif
```