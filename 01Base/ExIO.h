#if !defined(_EXIO_H)
#define _EXIO_H
#include <stdio.h>
#include <complex.h>

// scalar output
#define SLCr32_print(__out, __x) fprintf(__out, "%f", __x)
#define SLCr64_print(__out, __x) fprintf(__out, "%f", __x)
#define SLCc64_print(__out, __x) fprintf(__out, "%f, %f", crealf(__x), cimagf(__x))
#define SLCc128_print(__out, __x) fprintf(__out, "%f, %f", creal(__x), cimag(__x))
#define SLCnewline(__out) fprintf(__out, "\n")

// vector output
#define SLCr32_printv(__out, __x, __count) for (SLCi32_t __index = 0; __index < __count; __index++) { \
    fprintf(__out, (__index == 0) ? "" : ", "); SLCr32_print(__out, __x[__index]); \
}
#define SLCr64_printv(__out, __x, __count) for (SLCi32_t __index = 0; __index < __count; __index++) { \
    fprintf(__out, (__index == 0) ? "" : ", "); SLCr64_print(__out, __x[__index]); \
}
#define SLCc64_printv(__out, __x, __count) for (SLCi32_t __index = 0; __index < __count; __index++) { \
    fprintf(__out, (__index == 0) ? "" : ", "); SLCc64_print(__out, __x[__index]); \
}
#define SLCc128_printv(__out, __x, __count) for (SLCi32_t __index = 0; __index < __count; __index++) { \
    fprintf(__out, (__index == 0) ? "" : ", "); SLCc128_print(__out, __x[__index]); \
}

// vector output + newline
#define SLCr32_printvn(__out, __x, __count) for (SLCi32_t __index = 0; __index < __count; __index++) { \
    fprintf(__out, (__index == 0) ? "" : ", "); SLCr32_print(__out, __x[__index]); \
} SLCnewline(__out)
#define SLCr64_printvn(__out, __x, __count) for (SLCi32_t __index = 0; __index < __count; __index++) { \
    fprintf(__out, (__index == 0) ? "" : ", "); SLCr64_print(__out, __x[__index]); \
} SLCnewline(__out)
#define SLCc64_printvn(__out, __x, __count) for (SLCi32_t __index = 0; __index < __count; __index++) { \
    fprintf(__out, (__index == 0) ? "" : ", "); SLCc64_print(__out, __x[__index]); \
} SLCnewline(__out)
#define SLCc128_printvn(__out, __x, __count) for (SLCi32_t __index = 0; __index < __count; __index++) { \
    fprintf(__out, (__index == 0) ? "" : ", "); SLCc128_print(__out, __x[__index]); \
} SLCnewline(__out)


#endif