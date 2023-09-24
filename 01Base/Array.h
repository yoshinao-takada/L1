#if !defined(_BASE01_ARRAY_H)
#define _BASE01_ARRAY_H
#include "SLC/Numbers.h"
typedef union {
    SLC4i16_t i16; // maybe this is the most frequently used configuration.
    SLCi64_t i64;
    SLC2i32_t i32;
    SLC8i8_t i8;
    SLCu64_t u64;
    SLC2u32_t u32;
    SLC4u16_t u16;
    SLC8u8_t u8;
} SLCArrayControl_t, *SLCPArrayControl_t;

typedef union {
    const void* cv;
    SLCptr_t ptr; // void*
    SLCptr_t* pptr; // void**
    SLCi8_t* i8;
    SLCi16_t* i16;
    SLCi32_t* i32;
    SLCi64_t* i64;
    SLCu8_t* u8;
    SLCu16_t* u16;
    SLCu32_t* u32;
    SLCu64_t* u64;
    SLCr32_t* r32;
    SLCr64_t* r64;
    SLCc64_t* c64;
    SLCc128_t* c128;
    SLCsize_t* size;
    SLCbool_t* bool_;
} SLCArrayData_t, *SLCPArrayData_t;

typedef struct {
    SLCArrayControl_t cont;
    SLCArrayData_t data;
} SLCArray_t, *SLCPArray_t;
typedef const SLCArray_t *SLCPCArray_t;

SLCPArray_t SLCArray_InitHeader(SLCPArray_t __ptr, SLCi16_t __nmemb, SLCi16_t __unit_size);
SLCPArray_t SLCArray_InitHeader2(SLCPArray_t __ptr, const SLC4i16_t __size);

// giving a unit count and a unit size, get from heap.
#define SLCArray_Calloc(__nmemb, __unitsize) SLCArray_InitHeader( \
    (SLCPArray_t)malloc(SLClatestallocated = SLCalign8(__nmemb * __unitsize + sizeof(SLCArray_t))), __nmemb, __unitsize)

// giving a unit count and a unit size, get from stack frame.
#define SLCArray_Calloca(__nmemb, __unitsize) SLCArray_InitHeader( \
    (SLCPArray_t)alloca(SLClatestallocated = SLCalign8(__nmemb * __unitsize + sizeof(SLCArray_t))), __nmemb, __unitsize)

// giving a multi-dimensional size([0]:unit size, [1]: 1st dimension, [2]: 2nd dimension, [3]: 3rd dimension), get from heap
#define SLCArray_Alloc(__size) SLCArray_InitHeader2( \
    (SLCPArray_t)malloc(SLClatestallocated = SLCalign8(SLCprod4(__size) + sizeof(SLCArray_t))), __size)

// giving a multi-dimensional size, get from stack frame.
#define SLCArray_Alloca(__size) SLCArray_InitHeader2( \
    (SLCPArray_t)alloca(SLClatestallocated = SLCalign8(SLCprod4(__size) + sizeof(SLCArray_t))), __size)

// return a pointer pointing the element indexed by __ix.
#define SLCArray_UnitSize(__a) ((__a)->cont.i16[0])
#define SLCArray_Index1D(__a, __ix) (SLCArray_UnitSize(__a) * (__ix))
#define SLCArray_Index2D(__a, __ix, __iy) (SLCArray_UnitSize(__a) * ((__ix) + (__iy) * (__a)->cont.i16[1]))
#define SLCArray_Index3D(__a, __ix, __iy, __iz) \
    (SLCArray_UnitSize(__a) * ((__ix) + (__a)->cont.i16[1] * ((__iy) + (__a)->cont.i16[2] * (__iz) )))
#define SLCArray_At1D(__a, __T, __ix) (__T)((__a)-> data.i8 + SLCArray_Index1D(__a, __ix))
#define SLCArray_At2D(__a, __T, __ix, __iy) (__T)((__a)-> data.i8 + SLCArray_Index2D(__a, __ix, __iy))
#define SLCArray_At3D(__a, __T, __ix, __iy, __iz) (__T)((__a)-> data.i8 + SLCArray_Index3D(__a, __ix, __iy, __iz))
#define SLCArray_SameSize2D(__a, __b) \
    ((__a)->cont.i16[0] == (__b)->cont.i16[0]) && \
    ((__a)->cont.i16[1] == (__b)->cont.i16[1]) && \
    ((__a)->cont.i16[2] == (__b)->cont.i16[2]) && \
    ((__a)->cont.i16[3] == 1) && \
    ((__b)->cont.i16[3] == 1)
#define SLCArray_TransposedSize2D(__a, __b) \
    ((__a)->cont.i16[0] == (__b)->cont.i16[0]) && \
    ((__a)->cont.i16[2] == (__b)->cont.i16[1]) && \
    ((__a)->cont.i16[1] == (__b)->cont.i16[2]) && \
    ((__a)->cont.i16[3] == 1) && \
    ((__b)->cont.i16[3] == 1)
#define SLCArray_ValidMatrixProduct(__prod, __left, __right) \
    ((__prod)->cont.i16[0] == (__left)->cont.i16[0]) && \
    ((__prod)->cont.i16[0] == (__right)->cont.i16[0]) && \
    ((__prod)->cont.i16[2] == (__left)->cont.i16[2]) && \
    ((__prod)->cont.i16[1] == (__right)->cont.i16[1]) && \
    ((__left)->cont.i16[1] == (__right)->cont.i16[2]) && \
    ((__left)->cont.i16[3] == 1) && \
    ((__right)->cont.i16[3] == 1) && \
    ((__prod)->cont.i16[3] == 1)
#define SLCArray_SameSquareMatrixSize(__a, __b) \
    ((__a)->cont.i16[0] == (__b)->cont.i16[0]) && \
    ((__a)->cont.i16[1] == (__b)->cont.i16[1]) && \
    ((__a)->cont.i16[1] == (__b)->cont.i16[2]) && \
    ((__a)->cont.i16[2] == (__b)->cont.i16[2])
#define SLCArray_InvWorkSize(__a, __inv) \
    ((__a)->cont.i16[0] == (__inv)->cont.i16[0]) && \
    ((2 * (__a)->cont.i16[1]) == (__inv)->cont.i16[1]) && \
    ((1 + (__a)->cont.i16[2]) == (__inv)->cont.i16[2])
#define SLCArray_MatRows(__m) (__m)->cont.i16[2]
#define SLCArray_MatColumns(__m) (__m)->cont.i16[1]
#define SLC_TransposedMatSize(__matsize) { __matsize[0], __matsize[2], __matsize[1], 1 }
#define SLCinvMatWorkSize(__matsize) { __matsize[0], 2 * __matsize[1], 1 + __matsize[2], 1 }
#define SLC_SolveWorkSize(__matLsize, __matRsize) { \
    __matLsize[0], __matLsize[1]+__matRsize[1], 1 + __matLsize[2], 1 }
#endif