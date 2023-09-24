#define _01BASE_NUMBERS_C
#include <SLC/Numbers.h>
#include <SLC/Array.h>

SLCi8_t SLCi8_units[3] = { 0, 1, -1 };
SLCi16_t SLCi16_units[3] = { 0, 1, -1 };
SLCi32_t SLCi32_units[3] = { 0, 1, -1 };
SLCi64_t SLCi64_units[3] = { 0, 1, -1 };
SLCu8_t SLCu8_units[2] = { 0, 1 };
SLCu16_t SLCu16_units[2] = { 0, 1 };
SLCu32_t SLCu32_units[2] = { 0, 1 };
SLCu64_t SLCu64_units[2] = { 0, 1 };
SLCr32_t SLCr32_units[3] = { 0, 1.0f, -1.0f };
SLCr64_t SLCr64_units[3] = { 0, 1, -1 };
SLCc64_t SLCc64_units[5] = { CMPLXF(0.0f,0.0f), CMPLXF(1.0f,0.0f), CMPLXF(-1.0f,0.0f), CMPLXF(0.0f,1.0f), CMPLXF(0.0f,-1.0f) };
SLCc128_t SLCc128_units[5] = { 0, CMPLX(1,0), CMPLX(-1,0), CMPLX(0,1), CMPLX(0,1) };
SLCbool_t SLCbool_units[2] = { false, true };
SLCsize_t SLCunitsizes[] = SLCUNITSIZES;
SLCsize_t SLClatestallocated = 0;

SLCPArray_t SLCArray_InitHeader(SLCPArray_t __ptr, SLCi16_t __nmemb, SLCi16_t __unit_size)
{
    __ptr->cont.i16[0] = __unit_size;
    __ptr->cont.i16[1] = __nmemb;
    __ptr->cont.i16[2] = __ptr->cont.i16[3] = 1;
    __ptr->data.cv = (__ptr + 1);
    return __ptr;
}

SLCPArray_t SLCArray_InitHeader2(SLCPArray_t __ptr, const SLC4i16_t __size)
{
    SLCcopy4(__ptr->cont.i16, __size);
    __ptr->data.cv = (__ptr + 1);
    return __ptr;
}
