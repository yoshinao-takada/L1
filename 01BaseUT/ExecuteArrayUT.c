#include "SLC/Array.h"
#include "SLC/Log.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
extern SLCsize_t SLClatestallocated;

int ExecuteArrayUT()
{
    int err = EXIT_SUCCESS;
    do {
        // giving a unit count and a unit size, get an object from heap
        {
            SLCPArray_t pa = NULL;
            pa = SLCArray_Calloc(3, 16);
            assert(SLClatestallocated == (3 * 16 + sizeof(SLCArray_t)));
            assert(16 == SLCArray_UnitSize(pa));
            free(pa);
            pa = NULL;
        }

        // giving a unit count and a unit size, get an object from stack frame
        {
            SLCPArray_t pa = NULL;
            pa = SLCArray_Calloca(4 /* __nmemb */, 8 /* __unitsize */);
            assert(SLClatestallocated == (4 * 8 + sizeof(SLCArray_t)));
            assert(8 == SLCArray_UnitSize(pa));
        }

        // giving a multi-dimensional size, get an object from heap
        {
            SLCPArray_t pa = NULL;
            SLC4i16_t size = { 4, 3, 3, 1 };
            pa = SLCArray_Alloc(size);
            assert(SLClatestallocated == SLCalign8(36 + sizeof(SLCArray_t)));
            assert(4 == SLCArray_UnitSize(pa));
            free(pa);            
            pa = NULL;
        }

        // giving a multi-dimensional size, get an object from stack frame
        {
            SLCPArray_t pa = NULL;
            SLC4i16_t size = { 4, 3, 3, 1 };
            pa = SLCArray_Alloca(size);
            assert(4 == SLCArray_UnitSize(pa));
            assert(SLClatestallocated == SLCalign8(36 + sizeof(SLCArray_t)));
        }
    } while (0);
    SLC_testend(err, __FUNCTION__, __LINE__);
    return err;
}