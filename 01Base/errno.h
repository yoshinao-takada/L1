#if !defined(_01BASE_ERRNO_H)
#define _01BASE_ERRNO_H
#include "SLC/Numbers.h"
typedef SLCi32_t SLCerrno_t;
#define SLC_ESINGULAR   0x10000 /* matrix is near singular */
#define SLC_ENOCONV     0x10001 /* not converged within iteration limit */
#define SLC_EMATSIZE    0x10002 /* Matrix size mismatch */
#define SLC_EINVAL      0x10003 /* Invalid operation (usually in objective function or Jacobian) */
#endif