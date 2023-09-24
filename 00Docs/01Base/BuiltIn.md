# Built-in type redefinitions
Generic programming in upper layers require type agnostic uniform definitions of
type names and their related elementary functions and macros.
For example generic programming using `float`, `double`, `float complex`, and `double complex` require `cosine` and `sine` functions which are recognized by a common part and variable type name. Concretely describing the example, the function prototypes are defined like
```
#include <math.h>
#include <complex.h>

typedef float SLCr32_t;
typedef double SLCr64_t;
typedef float complex SLCc64_t;
typedef double complex SLCc128_t;
#define SLCr32_cos(__x)     cosf(__x)
#define SLCr64_cos(__x)     cos(__x)
#define SLCc64_cos(__x)     ccosf(__x)
#define SLCc128_cos(__x)    ccos(__x)
#define SLCr32_sin(__x)     sinf(__x)
#define SLCr64_sin(__x)     sin(__x)
#define SLCc64_sin(__x)     csinf(__x)
#define SLCc128_sin(__x)    csin(__x)
#define SLCr32_atan2(__x, __y)  atan2f(__x, __y)
#define SLCr64_atan2(__x, __y)  atan2(__x, __y)
```

Definitions of built-in types
```
#pragma region builtin_type_redefinitions
typedef enum {
    SLCi8 = 0,
    SLCi16,
    SLCi32,
    SLCi64,
    SLCu8,
    SLCu16,
    SLCu32,
    SLCu64,
    SLCr32,
    SLCr64,
    SLCc64,
    SLCc128,
    SLCbool,
    SLCptr,
} SLCtypes_t;
#pragma region single_element_types
typedef int8_t      SLCi8_t;
typedef int16_t     SLCi16_t;
typedef int32_t     SLCi32_t;
typedef int64_t     SLCi64_t;
typedef uint8_t     SLCu8_t;
typedef uint16_t    SLCu16_t;
typedef uint32_t    SLCu32_t;
typedef uint64_t    SLCu64_t;
typedef float       SLCr32_t;
typedef double      SLCr64_t;
typedef float complex   SLCc64_t;
typedef double complex  SLCc128_t;
typedef bool        SLCbool_t;
typedef void*       SLCptr_t;
#pragma endregion single_element_types

#define SLCUNITSIZES   { \
    sizeof(SLCi8_t), sizeof(SLCi16_t), sizeof(SLCi32_t), sizeof(SLCi64_t), \
    sizeof(SLCu8_t), sizeof(SLCu16_t), sizeof(SLCu32_t), sizeof(SLCu64_t), \
    sizeof(SLCr32_t), sizeof(SLCr64_t), sizeof(SLCc64_t), sizeof(SLCc128_t), \
    sizeof(SLCbool_t), sizeof(SLCptr_t) }
typedef uint16_t    SLCssize_t;
typedef uint32_t    SLCsize_t;
typedef uint64_t    SLClsize_t;

extern SLCssize_t   SLCunitsizes[]; // = SLCUNITSIZES;

#pragma region two_element_types
typedef int8_t      SLC2i8_t[2];
typedef int16_t     SLC2i16_t[2];
typedef int32_t     SLC2i32_t[2];
typedef int64_t     SLC2i64_t[2];
typedef uint8_t     SLC2u8_t[2];
typedef uint16_t    SLC2u16_t[2];
typedef uint32_t    SLC2u32_t[2];
typedef uint64_t    SLC2u64_t[2];
typedef float       SLC2r32_t[2];
typedef double      SLC2r64_t[2];
typedef float complex   SLC2c64_t[2];
typedef double complex  SLC2c128_t[2];
typedef bool        SLC2bool_t[2];
typedef void*       SLC2ptr_t[2];
#pragma endregion two_element_types

#pragma region three_element_types
typedef int8_t      SLC3i8_t[3];
typedef int16_t     SLC3i16_t[3];
typedef int32_t     SLC3i32_t[3];
typedef int64_t     SLC3i64_t[3];
typedef uint8_t     SLC3u8_t[3];
typedef uint16_t    SLC3u16_t[3];
typedef uint32_t    SLC3u32_t[3];
typedef uint64_t    SLC3u64_t[3];
typedef float       SLC3r32_t[3];
typedef double      SLC3r64_t[3];
typedef float complex   SLC3c64_t[3];
typedef double complex  SLC3c128_t[3];
typedef bool        SLC3bool_t[3];
typedef void*       SLC3ptr_t[3];
#pragma endregion three_element_types

#pragma region four_element_types
typedef int8_t      SLC4i8_t[4];
typedef int16_t     SLC4i16_t[4];
typedef int32_t     SLC4i32_t[4];
typedef int64_t     SLC4i64_t[4];
typedef uint8_t     SLC4u8_t[4];
typedef uint16_t    SLC4u16_t[4];
typedef uint32_t    SLC4u32_t[4];
typedef uint64_t    SLC4u64_t[4];
typedef float       SLC4r32_t[4];
typedef double      SLC4r64_t[4];
typedef float complex   SLC4c64_t[4];
typedef double complex  SLC4c128_t[4];
typedef bool        SLC4bool_t[4];
typedef void*       SLC4ptr_t[4];
#pragma endregion four_element_types

#pragma region eight_element_types
typedef int8_t      SLC8i8_t[8];
typedef int16_t     SLC8i16_t[8];
typedef int32_t     SLC8i32_t[8];
typedef int64_t     SLC8i64_t[8];
typedef uint8_t     SLC8u8_t[8];
typedef uint16_t    SLC8u16_t[8];
typedef uint32_t    SLC8u32_t[8];
typedef uint64_t    SLC8u64_t[8];
typedef float       SLC8r32_t[8];
typedef double      SLC8r64_t[8];
typedef float complex   SLC8c64_t[8];
typedef double complex  SLC8c128_t[8];
typedef bool        SLC8bool_t[8];
typedef void*       SLC8ptr_t[8];
#pragma endregion eight_element_types

#pragma region sixteen_element_types
typedef int8_t      SLC16i8_t[16];
typedef int16_t     SLC16i16_t[16];
typedef int32_t     SLC16i32_t[16];
typedef int64_t     SLC16i64_t[16];
typedef uint8_t     SLC16u8_t[16];
typedef uint16_t    SLC16u16_t[16];
typedef uint32_t    SLC16u32_t[16];
typedef uint64_t    SLC16u64_t[16];
typedef float       SLC16r32_t[16];
typedef double      SLC16r64_t[16];
typedef float complex   SLC16c64_t[16];
typedef double complex  SLC16c128_t[16];
typedef bool        SLC16bool_t[16];
typedef void*       SLC16ptr_t[16];
#pragma endregion sixteen_element_types
#pragma endregion builtin_type_redefinitions
```

Redefinition elementary functions and macros
```

#define SLCr32_min(__number0, __number1) fminf(__number0, __number1)
#define SLCr64_min(__number0, __number1) fmin(__number0, __number1)
#define SLCr32_max(__number0, __number1) fmaxf(__number0, __number1)
#define SLCr64_max(__number0, __number1) fmax(__number0, __number1)
#define SLCr32_floor(__number) floorf(__number)
#define SLCr64_floor(__number) floor(__number)
#define SLCr32_ceil(__number) ceilf(__number)
#define SLCr64_ceil(__number) ceil(__number)
#define SLCr32_abs(__number)  fabsf(__number)
#define SLCr64_abs(__number)   fabs(__number)
#define SLCc64_abs(__number)   cabsf(__number)
#define SLCc128_abs(__number)  cabs(__number)
#define SLCr32_conj(__number)  (__number)
#define SLCr64_conj(__number)  (__number)
#define SLCc64_conj(__number)  conjf(__number)
#define SLCc128_conj(__number) conj(__number)
#define SLCr32_fromreal(__number)  (__number)
#define SLCr64_fromreal(__number)  (__number)
#define SLCc64_fromreal(__number)  CMPLXF(__number, 0.0f)
#define SLCc128_fromreal(__number) CMPLX(__number, 0.0f)
#define SLCr32_print(__out, __delimiter, __number) fprintf(__out, "%s%f", __delimiter, __number)
#define SLCr64_print(__out, __delimiter, __number) fprintf(__out, "%s%f", __delimiter, __number)
#define SLCc64_print(__out, __delimiter, __number) fprintf(__out, "%s(%f,%f)", __delimiter, crealf(__number), cimagf(__number))
#define SLCc128_print(__out, __delimiter, __number) fprintf(__out, "%s(%f,%f)", __delimiter, creal(__number), cimag(__number))
// uniform distribution [-1.0, +1.0] random number generators
#define SLCr32_rand    ((SLCr32_t)(rand()-0.5f*RAND_MAX)/(0.5f*RAND_MAX))
#define SLCr64_rand    ((SLCr64_t)(rand()-0.5*RAND_MAX)/(0.5*RAND_MAX ))
#define SLCc64_rand    CMPLXF(SLCr32_rand, SLCr32_rand)
#define SLCc128_rand   CMPLX(SLCr64_rand, SLCr64_rand)
// standard tolerances
#define SLCr32_stdtol  1.0e-5f
#define SLCr64_stdtol  1.0e-10
#define SLCc64_stdtol  SLCr32_stdtol
#define SLCc128_stdtol SLCr64_stdtol

#define SLCprod2(__a) (__a)[0]*(__a)[1]
#define SLCprod3(__a) (__a)[0]*(__a)[1]*(__a)[2]
#define SLCprod4(__a) (__a)[0]*(__a)[1]*(__a)[2]*(__a)[3]
#define SLCprod8(__a) (__a)[0]*(__a)[1]*(__a)[2]*(__a)[3]*(__a)[4]*(__a)[5]*(__a)[6]*(__a)[7]

#if !defined(_SLCNUMBERS_C)
extern SLCi8_t SLCi8_units[3]; // { 0, 1, -1 }
extern SLCi16_t SLCi16_units[3]; // { 0, 1, -1 }
extern SLCi32_t SLCi32_units[3]; // { 0, 1, -1 }
extern SLCi64_t SLCi64_units[3]; // { 0, 1, -1 }
extern SLCu8_t SLCu8_units[2]; // { 0, 1 }
extern SLCu16_t SLCu16_units[2]; // { 0, 1 }
extern SLCu32_t SLCu32_units[2]; // { 0, 1 }
extern SLCu64_t SLCu64_units[2]; // { 0, 1 }
extern SLCr32_t SLCr32_units[3]; // { 0, 1, -1 }
extern SLCr64_t SLCr64_units[3]; // { 0, 1, -1 }
extern SLCc64_t SLCc64_units[5]; // { 0, (1+0j), (-1+0j), (0+j), (0-j) }
extern SLCc128_t SLCc128_units[5]; // { 0, (1+0j), (-1+0j), (0+j), (0-j) }
extern SLCbool_t SLCbool_units[2]; // { false, true }
extern SLCsize_t SLCunitsizes[];
#endif

#define SLCalign4(__N) ((0 == (__N & 3)) ? __N : ((__N | 3) + 1))

#define SLCalign8(__N) ((0 == (__N & 7)) ? __N : ((__N | 7) + 1))

#define SLCarraysize(__A)  (sizeof(__A)/sizeof(__A[0]))

#define SLCcopy2(__DST, __SRC) (__DST)[0] = (__SRC)[0]; (__DST)[1] = (__SRC)[1];
#define SLCcopy3(__DST, __SRC) (__DST)[0] = (__SRC)[0]; (__DST)[1] = (__SRC)[1]; (__DST)[2] = (__SRC)[2];
#define SLCcopy4(__DST, __SRC) (__DST)[0] = (__SRC)[0]; (__DST)[1] = (__SRC)[1]; \
    (__DST)[2] = (__SRC)[2]; (__DST)[3] = (__SRC)[3];
#define SLCcopy8(__DST, __SRC) (__DST)[0] = (__SRC)[0]; (__DST)[1] = (__SRC)[1]; \
    (__DST)[2] = (__SRC)[2]; (__DST)[3] = (__SRC)[3]; (__DST)[4] = (__SRC)[4]; (__DST)[5] = (__SRC)[5]; \
    (__DST)[6] = (__SRC)[6]; (__DST)[7] = (__SRC)[7];
#define SLCcopy16(__DST, __SRC) (__DST)[0] = (__SRC)[0]; (__DST)[1] = (__SRC)[1]; \
    (__DST)[2] = (__SRC)[2]; (__DST)[3] = (__SRC)[3]; (__DST)[4] = (__SRC)[4]; (__DST)[5] = (__SRC)[5]; \
    (__DST)[6] = (__SRC)[6]; (__DST)[7] = (__SRC)[7]; (__DST)[8] = (__SRC)[8]; (__DST)[9] = (__SRC)[9]; \
    (__DST)[10] = (__SRC)[10]; (__DST)[11] = (__SRC)[11]; (__DST)[12] = (__SRC)[12]; (__DST)[13] = (__SRC)[13]; \
    (__DST)[14] = (__SRC)[14]; (__DST)[15] = (__SRC)[15];
#endif
```