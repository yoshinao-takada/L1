# Control
```
{
    "out": "NLSL.c",
    "vtypes": ["r32", "r64", "c64", "c128"],
    "rtypes": ["r32", "r64", "r32", "r64"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
```
#include "SLC/NLSL.h"
#include "SLC/Log.h"
#include "SLC/NumbersCopy.h"
#include "SLC/MiniBLAS.h"
#include "SLC/MiniLA.h"
#include "SLC/errno.h"
#include "SLC/ExIO.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <errno.h>
```
# Generic
## Full Definition of Gauss-Newton solver struct
struct full definition and memory management functions.
```
#pragma region <VTYPE>_functions
// debug-trace function type
typedef void (*NLSLGNSolverTrace<VTYPE>)(SLCPCNLSLGNSolver<VTYPE>_t solver);

// convergence checker
typedef SLCNLSLState_t (*NLSLGNSolverIsConverged<VTYPE>)(SLCPCNLSLGNSolver<VTYPE>_t solver);

// full definition of Gauss-Newton solver struct
struct SLCNLSLGNSolver<VTYPE> {
    // configuration parameters
    SLCNLSLGNConf<VTYPE>_t conf;

    // working matrices
    SLCPArray_t
        x, // X column vector
        delta_x, // == x_new - x; i.e. x_new = x + delta_x.
        y, negy, // Y and -Y column vector
        jcolbuf, // Jacobian column buffer
        j; // Jacobian
    SLCMat_SolveODWorkMatSet_t wkset;

    // operating state
    SLCNLSLState_t state;
    // iteration counter
    SLC<ITYPE>_t iter;
    SLC<RTYPE>_t normDX, normY; // L1-norm of delta_x and y.

    // trace functions
    NLSLGNSolverTrace<VTYPE>
        trace_xy, // trace x and y
        trace_j, // trace Jacobian
        trace_norm_dxy; // trace delta_x and y
    NLSLGNSolverIsConverged<VTYPE> converged;
};
```
## Trace functions
```
static void <VTYPE>TraceXY(SLCPCNLSLGNSolver<VTYPE>_t solver)
{
    fprintf(solver->conf.base.traceout, "x = {");
    SLC<VTYPE>_printv(solver->conf.base.traceout, solver->x->data.<VTYPE>, solver->conf.base.cx);
    fprintf(solver->conf.base.traceout, "}\ny = {");
    SLC<VTYPE>_printv(solver->conf.base.traceout, solver->y->data.<VTYPE>, solver->conf.base.cy);
    fprintf(solver->conf.base.traceout, "}\n");
}

static void <VTYPE>TraceJ(SLCPCNLSLGNSolver<VTYPE>_t solver)
{
    SLCMat<VTYPE>_Print(solver->conf.base.traceout,
        "J = ", solver->j, "");
}

static void <VTYPE>TraceNormDxY(SLCPCNLSLGNSolver<VTYPE>_t solver)
{
    fprintf(solver->conf.base.traceout,
        "normDX = %e, normY = %e\n", solver->normDX, solver->normY);
}

// a dummy function does nothing.
static void <VTYPE>TraceNone(SLCPCNLSLGNSolver<VTYPE>_t solver) {}


// initialize trace function setups.
static void <VTYPE>InitTrace(SLCPNLSLGNSolver<VTYPE>_t solver)
{
    if (solver->conf.base.traceout)
    {
        solver->trace_xy = <VTYPE>TraceXY;
        solver->trace_j = <VTYPE>TraceJ;
        solver->trace_norm_dxy = <VTYPE>TraceNormDxY;
    }
    else
    { // traceout == NULL
        solver->trace_xy = 
        solver->trace_j =
        solver->trace_norm_dxy = <VTYPE>TraceNone;
    }
}
#pragma endregion <VTYPE>_functions
```
## Convergence checker
```
static SLCNLSLState_t <VTYPE>NLSLGN_DxConverged(SLCPCNLSLGNSolver<VTYPE>_t solver)
{
    return solver->normDX < solver->conf.base.normDxMax ? NLSLState_dx_converged : NLSLState_running;
}

static SLCNLSLState_t <VTYPE>NLSLGN_YConverged(SLCPCNLSLGNSolver<VTYPE>_t solver)
{
    return solver->normY < solver->conf.base.normYMax ? NLSLState_y_converged : NLSLState_running;
}

static SLCNLSLState_t <VTYPE>NLSLGN_BothConverged(SLCPCNLSLGNSolver<VTYPE>_t solver)
{
    return ((solver->normDX < solver->conf.base.normDxMax) &&
            (solver->normY < solver->conf.base.normYMax)) ? NLSLState_both_converged : NLSLState_running;
}

static void <VTYPE>InitConvergenceChecker(SLCPNLSLGNSolver<VTYPE>_t solver)
{
    switch (solver->conf.base.convergenceCondition)
    {
        case NLSLConverge_dx:
            solver->converged = <VTYPE>NLSLGN_DxConverged;
            break;
        case NLSLConverge_y:
            solver->converged = <VTYPE>NLSLGN_YConverged;
            break;
        case NLSLConverge_both:
            solver->converged = <VTYPE>NLSLGN_BothConverged;
    }
}
```
## Memory management
```
// free all internal buffers in solver.
static void FreeAllArrays<VTYPE>(SLCPNLSLGNSolver<VTYPE>_t solver)
{
    SLCArray_SafeFree(solver->x);
    SLCArray_SafeFree(solver->y);
    SLCArray_SafeFree(solver->negy);
    SLCArray_SafeFree(solver->jcolbuf);
    SLCArray_SafeFree(solver->j);
    SLCMat_DestroySolveODWorkMatSet(&solver->wkset);
}

static SLCerrno_t AllocAllArrays<VTYPE>(SLCPNLSLGNSolver<VTYPE>_t solver)
{
    SLCi16_t 
        cx = (SLCi16_t)solver->conf.base.cx,
        cy = (SLCi16_t)solver->conf.base.cy,
        unitsize = sizeof(SLC<VTYPE>_t);
    SLC4i16_t size_x = { unitsize, 1, cx, 1 };
    SLC4i16_t size_y = { unitsize, 1, cy, 1 };
    SLC4i16_t size_j = { unitsize, cx, cy, 1 };
    solver->x = SLCArray_Alloc(size_x);
    solver->delta_x = SLCArray_Alloc(size_x);
    solver->y = SLCArray_Alloc(size_y);
    solver->negy = SLCArray_Alloc(size_y);
    solver->jcolbuf = SLCArray_Alloc(size_y);
    solver->j = SLCArray_Alloc(size_j);
    SLCMat_InitSolveODWorkMatSet(solver->j, solver->y, &solver->wkset);
    SLCerrno_t err = (
        !solver->x || !solver->delta_x || !solver->y ||
        !solver->negy || !solver->jcolbuf || !solver->j ||
        !solver->wkset.leftT || !solver->wkset.leftTC ||
        !solver->wkset.leftTC_left || !solver->wkset.rightT ||
        !solver->wkset.leftTC_right || !solver->wkset.work) ? ENOMEM : EXIT_SUCCESS;
    return err;
}

// create a new instance
SLCPNLSLGNSolver<VTYPE>_t SLCNLSLGNSolver<VTYPE>_New(
    SLC<ITYPE>_t cx, SLC<ITYPE>_t cy, SLC<ITYPE>_t cc
) {
    SLC<ITYPE>_t headSize = SLCalign8(sizeof(SLCNLSLGNSolver<VTYPE>_t));
    SLC<ITYPE>_t xInitialSize = SLCalign8(sizeof(SLC<VTYPE>_t) * cx);
    SLC<ITYPE>_t cParamsSize = SLCalign8(sizeof(SLC<VTYPE>_t) * cc);
    SLC<ITYPE>_t JacobianSize = SLCalign8(sizeof(SLCGVVF<VTYPE>) * cx);
    SLC<ITYPE>_t allocSize = headSize + xInitialSize + cParamsSize + JacobianSize;
    SLCPNLSLGNSolver<VTYPE>_t pobj = (SLCPNLSLGNSolver<VTYPE>_t)malloc(allocSize);
    if (!pobj) return pobj;
    pobj->conf.base.xInitial = (SLC<VTYPE>_t*)(((SLCu8_t*)pobj) + headSize);
    pobj->conf.base.cParams = (SLC<VTYPE>_t*)(((SLCu8_t*)pobj) + headSize + xInitialSize);
    pobj->conf.jacobian = (SLCGVVF<VTYPE>*)(((SLCu8_t*)pobj) + headSize + xInitialSize + cParamsSize);
    SLC<VTYPE>_copy(pobj->conf.base.xInitial, 1, SLC<VTYPE>_units, 0, cx);
    SLC<VTYPE>_copy(pobj->conf.base.cParams, 1, SLC<VTYPE>_units, 0, cc);
    memset(pobj->conf.jacobian, 0, cx * sizeof(void*));
    pobj->conf.base.cx = cx;
    pobj->conf.base.cy = cy;
    pobj->conf.base.cc = cc;
    pobj->conf.base.maxIter = 10;
    pobj->conf.base.convergenceCondition = NLSLConverge_both;
    pobj->conf.base.normDxMax = pobj->conf.base.normYMax = SLC<VTYPE>_stdtol;
    pobj->conf.base.objective = NULL;
    pobj->conf.base.context = NULL;
    pobj->conf.base.traceout = stderr;

    if (EXIT_SUCCESS != AllocAllArrays<VTYPE>(pobj))
    {
        FreeAllArrays<VTYPE>(pobj);
        free(pobj);
        pobj = NULL;
    }
    else
    {
        pobj->state = NLSLState_created;
        pobj->iter = 0;
    }
    return pobj;
}

void SLCNLSLGNSolver<VTYPE>_Delete(SLCPNLSLGNSolver<VTYPE>_t *ppsolver)
{
    if (ppsolver)
    {
        SLCPNLSLGNSolver<VTYPE>_t solver = *ppsolver;
        FreeAllArrays<VTYPE>(solver);
        free(solver);
        *ppsolver = NULL;
    }
}
```
## Math APIs
```
SLCPNLSLGNConf<VTYPE>_t SLCNLSLGNSolver<VTYPE>_Conf(SLCPNLSLGNSolver<VTYPE>_t solver
) {
    return &(solver->conf);
}

// initalizer must be called after setting configuration parameters.
SLCerrno_t SLCNLSLGNSolver<VTYPE>_Init(SLCPNLSLGNSolver<VTYPE>_t solver)
{
    SLCerrno_t err = EXIT_SUCCESS;
    <VTYPE>InitTrace(solver);
    <VTYPE>InitConvergenceChecker(solver);
    SLC<VTYPE>_copy(
        solver->x->data.<VTYPE>, 1,
        solver->conf.base.xInitial, 1,
        solver->conf.base.cx);
    solver->state = NLSLState_initialized;
    return err;
}

// calculate Jacobian
static SLCerrno_t <VTYPE>CalcJ(SLCPNLSLGNSolver<VTYPE>_t solver)
{
    SLCerrno_t err = EXIT_SUCCESS;
    SLC<VTYPE>_t* j_elements = solver->j->data.<VTYPE>;
    SLC<ITYPE>_t
        rows = SLCArray_MatRows(solver->j),
        columns = SLCArray_MatColumns(solver->j);
    for (SLC<ITYPE>_t column = 0; column < columns; column++)
    {
        err = solver->conf.jacobian[column](
            solver->jcolbuf->data.<VTYPE>, rows,
            solver->x->data.<VTYPE>, columns,
            NULL, 0,
            solver->conf.base.context
        );
        if (err) break;
        SLC<VTYPE>_copy(
            j_elements + column, columns, solver->jcolbuf->data.<VTYPE>, 1, rows);
    }
    return err;
}

// execute Gauss-Newton iterative operation
SLCerrno_t SLCNLSLGNSolver<VTYPE>_Execute(SLCPNLSLGNSolver<VTYPE>_t solver)
{
    SLCerrno_t err = EXIT_SUCCESS;
    solver->state = NLSLState_running;
    for (solver->iter = 0; 
         (solver->iter < solver->conf.base.maxIter) && (solver->state == NLSLState_running);
         solver->iter++)
    {
        // calc y
        err = solver->conf.base.objective(
            solver->y->data.<VTYPE>, solver->conf.base.cy,
            solver->x->data.<VTYPE>, solver->conf.base.cx,
            solver->conf.base.cParams, solver->conf.base.cc,
            solver->conf.base.context
        );
        if (err) break;
        solver->trace_xy(solver);
        for (SLC<ITYPE>_t i = 0; i < solver->conf.base.cy; i++)
        {
            solver->negy->data.<VTYPE>[i] = -solver->y->data.<VTYPE>[i];
        }

        // calc Jacobian
        if (EXIT_SUCCESS != (err = <VTYPE>CalcJ(solver))) break;
        solver->trace_j(solver);

        // calc delta_x
        err = SLCMat<VTYPE>_SolveOD(solver->delta_x, solver->j, solver->negy, &solver->wkset);
        if (EXIT_SUCCESS != err) break;

        // calc normDX, normY
        solver->normDX = SLCBLAS<VTYPE>_AbsSum(solver->delta_x->data.<VTYPE>, solver->conf.base.cx);
        solver->normY = SLCBLAS<VTYPE>_AbsSum(solver->y->data.<VTYPE>, solver->conf.base.cy);
        solver->trace_norm_dxy(solver);

        // update x
        SLCBLAS<VTYPE>_AddAss(solver->x->data.<VTYPE>, solver->delta_x->data.<VTYPE>, solver->conf.base.cx);

        // check convergence normDxMax, normYMax
        solver->state = solver->converged(solver);
    }
    if (err)
    {
        solver->state = NLSLState_errabort;
    }
    else if (solver->iter == solver->conf.base.maxIter)
    {
        solver->state = NLSLState_iterlimit;
    }
    return err;
}

// retrieve x and y vector
const SLC<VTYPE>_t* SLCNLSLGNSolver<VTYPE>_X(SLCPNLSLGNSolver<VTYPE>_t solver)
{
    return solver->x->data.<VTYPE>;
}

const SLC<VTYPE>_t* SLCNLSLGNSolver<VTYPE>_Y(SLCPNLSLGNSolver<VTYPE>_t solver)
{
    return solver->y->data.<VTYPE>;
}

// retrieve L1 norm of dx and y vector
SLC<VTYPE>_t SLCNLSLGNSolver<VTYPE>_L1NormDX(SLCPNLSLGNSolver<VTYPE>_t solver)
{
    return solver->normDX;
}
SLC<VTYPE>_t SLCNLSLGNSolver<VTYPE>_L1NormY(SLCPNLSLGNSolver<VTYPE>_t solver)
{
    return solver->normY;
}
```
# Foot
```
```
