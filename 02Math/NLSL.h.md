# Control
```
{
    "out": "../include/SLC/NLSL.h",
    "vtypes": ["r32", "r64", "c64", "c128"],
    "rtypes": ["r32", "r64", "r32", "r64"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
## Overview
Two types of NLSL are defined.
* Gauss-Newton method: applicable only to differentiable functions.
* Nelder-Mead method: applicable to any continuous functions including spline functions like broken-line.

## Gauss-Newton Method
I thought that the most understandable formulation is presented in a topic,
**"_k_ variables, _k_ functions"** and
**"_k_ variables, _m_ equations, with _m_&nbsp;&gt;&nbsp;_k_"** in
[a Wikipedia article](https://en.wikipedia.org/wiki/Newton%27s_method).

Mathematical details are described in [NLSL.c.md](NLSL.c.md).

## Beginning of source code of `NLSL.h`
```
#if !defined(_02MATH_NLSL_H)
#define _02MATH_NLSL_H
#include "SLC/Numbers.h"
#include "SLC/errno.h"
#include <stdio.h>
// The nonlinear solvers are very simple statemachine controlled by
// a state variable.
typedef enum {
    NLSLState_created, // created but not initialized
    NLSLState_initialized, // just after initialized
    NLSLState_running, // running execution
    NLSLState_iterlimit, // stopped by iteration limit
    NLSLState_converged, // stopped by convergence
    NLSLState_errabort, // stopped by error in objective or Jacobian
} SLCNLSLState_t;
```
# Generic
## Generic Parts of Nonlinear Solvers
Generic Nonlinear solvers have objective functions as defined below.
Configuration parameters depend on algorithms. But many of the parameters are common to most algorithms.
The common parts of the parameter and objective function signature are also defined below.
```
#pragma region <VTYPE>_functions
// declare function pointer of objective functions and column functions of Jacobian.
// The functions must be generalized vector-vector function with multiple
// constant parameters.
typedef SLCerrno_t (*SLCGVVF<VTYPE>)(
    SLC<VTYPE>_t* y, SLC<ITYPE>_t cy, /* depedent variables */
    const SLC<VTYPE>_t* x, SLC<ITYPE>_t cx, /* dependent variables */
    const SLC<VTYPE>_t* c, SLC<ITYPE>_t cc /* constants */);

// declare configuration struct of a nonlinear solver.
typedef struct {
    FILE* traceout;
    SLC<ITYPE>_t cx, cy, cc; /* element counts of x, y, c */
    SLC<ITYPE>_t maxIter; /* maximum iteration limit */
    SLC<VTYPE>_t *xInitial; /* initial x vector */
    SLC<VTYPE>_t *cParams; /* constant parameters */
    SLC<RTYPE>_t normDxMax, normYMax; /* Convergence criterions; L1 norm of delta-x and y */
    SLCGVVF<VTYPE> objective; /* objective function */
} SLCNLSLConf<VTYPE>_t, *SLCPNLSLConf<VTYPE>_t;

typedef const SLCNLSLConf<VTYPE>_t *SLCPCNLSLConf<VTYPE>_t;
```
* `tracout` : output stream to trace program execution,
* `cx` : dimension of independent variable __x__,
* `cy` : dimension of objective function dependent varialble, __y__,
* `cc` : count of constants,
* `maxIter` : it limits iteration of Gauss-Newton method iterative operation,
* `normDxMax` : convergence criteria of deviation of __x__ in (_i_ + 1)th iteration and _i_th iteration.
The criteria is evaluated as an L1-norm (absolute some of the deviation).
* `normYMax` : convergence criteria of __y__ which is evaluated if the deviation of __x__ satisfies its criteria.
* `objective` : function pointer to an objective function.
, where "&lt;VTYPE&gt;" is one of "r32", "r64", "c64", and "c128". "&lt;RTYPE&gt;" is one of "r32" or "r64".
The identifiers represent number types as listed below.

Table. Number type identifiers
Identifier | SLC number type | std-C number type
-----------|-----------------|------------------
r32        | SLCr32_t       | float
r64        | SLCr64_t       | double
c64        | SLCc64_t       | float complex
c128       | SLCc128_t      | double complex
<br/>
## Gauss-Newton Method Solver
Configuration struct for Gauss-Newton method is derived from the common configuration
`SLCNLSLConf<VTYPE>_t`.
```
typedef struct {
    SLCNLSLConf<VTYPE>_t base; // configuration common parts are regarded as a base class.
    SLCGVVF<VTYPE>* jacobian; // array of Jacobian column vector functions
} SLCNLSLGNConf<VTYPE>_t, *SLCPNLSLGNConf<VTYPE>_t;
typedef const SLCNLSLGNConf<VTYPE>_t *SLCPCNLSLGNConf<VTYPE>_t;
```
Main body of Gauss-Newton solver contains many matrices and complicated.
Therefore its details are hidden in its c source file and are not shown in the
header file. Only the type names are declared.
```
typedef struct SLCNLSLGNSolver<VTYPE> SLCNLSLGNSolver<VTYPE>_t;
typedef SLCNLSLGNSolver<VTYPE>_t *SLCPNLSLGNSolver<VTYPE>_t;
typedef const SLCNLSLGNSolver<VTYPE>_t *SLCPCNLSLGNSolver<VTYPE>_t;
```
Methods comprising the Gauss-Newton solver are declared as shown below.
```
// create a new instance of a Gauss-Newton solver
SLCPNLSLGNSolver<VTYPE>_t SLCNLSLGNSolver<VTYPE>_New(SLC<ITYPE>_t cx, SLC<ITYPE>_t cy, SLC<ITYPE>_t cc);

// delete an existing instance
void SLCNLSLGNSolver<VTYPE>_Delete(SLCPNLSLGNSolver<VTYPE>_t *ppsolver);

// retrieve a configuration struct
SLCPNLSLGNConf<VTYPE>_t SLCNLSLGNSolver<VTYPE>_Conf(SLCPNLSLGNSolver<VTYPE>_t solver);

// initalizer must be called after setting configuration parameters.
SLCerrno_t SLCNLSLGNSolver<VTYPE>_Init(SLCPNLSLGNSolver<VTYPE>_t solver);

// execute Gauss-Newton iterative operation
SLCerrno_t SLCNLSLGNSolver<VTYPE>_Execute(SLCPNLSLGNSolver<VTYPE>_t solver);

// retrieve x and y vector
const SLC<VTYPE>_t* SLCNLSLGNSolver<VTYPE>_X(SLCPNLSLGNSolver<VTYPE>_t solver);
const SLC<VTYPE>_t* SLCNLSLGNSolver<VTYPE>_Y(SLCPNLSLGNSolver<VTYPE>_t solver);

// retrieve L1 norm of dx and y vector
SLC<VTYPE>_t SLCNLSLGNSolver<VTYPE>_L1NormDX(SLCPNLSLGNSolver<VTYPE>_t solver);
SLC<VTYPE>_t SLCNLSLGNSolver<VTYPE>_L1NormY(SLCPNLSLGNSolver<VTYPE>_t solver);
#pragma endregion <VTYPE>_functions
```
# Foot
```
#endif
```
