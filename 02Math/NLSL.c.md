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
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
```
# Generic
## Full Definition of Gauss-Newton solver struct
struct full definition and memory management functions.
```
#pragma region <VTYPE>_functions
// debug-trace function type
typedef void (*NLSLGNSolverTrace<VTYPE>)(SLCPCNLSLGNSolver<VTYPE>_t solver);

// full definition of Gauss-Newton solver struct
struct SLCNLSLGNSolver<VTYPE> {
    // configuration parameters
    SLCNLSLGNConf<VTYPE>_t conf;

    // working matrices
    SLCPArray_t
        x_new, // renewed x
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
};
```
## Trace functions
```
static void <VTYPE>TraceXY(SLCPCNLSLGNSolver<VTYPE>_t solver)
{
    fprintf(solver->conf.base.traceout, "x = {");
    for (SLC<ITYPE>_t i = 0; i < solver->conf.base.cx; i++)
    {
        const char* fmtdesc = (i == 0) ? "%f" : ", %f";
        fprintf(solver->conf.base.traceout, fmtdesc,
            solver->x->data.<VTYPE>[i]);
    }
    fprintf(solver->conf.base.traceout, "}\ny = {");
    for (SLC<ITYPE>_t i = 0; i < solver->conf.base.cx; i++)
    {
        const char* fmtdesc = (i == 0) ? "%f" : ", %f";
        fprintf(solver->conf.base.traceout, fmtdesc,
            solver->y->data.<VTYPE>[i]);
    }
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
## Memory management
```
// free all internal buffers in solver.
static void FreeAllArrays<VTYPE>(SLCPNLSLGNSolver<VTYPE>_t solver)
{
    SLCArray_SafeFree(solver->x_new);
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
    solver->x_new = SLCArray_Alloc(size_x);
    solver->x = SLCArray_Alloc(size_x);
    solver->delta_x = SLCArray_Alloc(size_x);
    solver->y = SLCArray_Alloc(size_y);
    solver->negy = SLCArray_Alloc(size_y);
    solver->jcolbuf = SLCArray_Alloc(size_y);
    solver->j = SLCArray_Alloc(size_j);
    SLCMat_InitSolveODWorkMatSet(solver->j, solver->delta_x, &solver->wkset);
}

// create a new instance
SLCPNLSLGNSolver<VTYPE>_t SLCNLSLGNSolver<VTYPE>_New(
    SLC<ITYPE>_t cx, SLC<ITYPE>_t cy, SLC<ITYPE>_t cc
) {
    SLC<ITYPE>_t headSize = SLCalign8(sizeof(SLCNLSLGNSolver<VTYPE>_t));
    SLC<ITYPE>_t xInitialSize = SLCalign8(sizeof(SLC<VTYPE>_t) * cx);
    SLC<ITYPE>_t cParamsSize = SLCalign8(sizeof(SLC<VTYPE>_t) * cc);
    SLC<ITYPE>_t allocSize = headSize + xInitialSize + cParamsSize;
    SLCPNLSLGNSolver<VTYPE>_t pobj = (SLCPNLSLGNSolver<VTYPE>_t)malloc(allocSize);
    pobj->conf.base.xInitial = (SLC<VTYPE>_t*)(((SLCu8_t*)pobj) + headSize);
    pobj->conf.base.cParams = (SLC<VTYPE>_t*)(((SLCu8_t*)pobj) + headSize + xInitialSize);
    SLC<VTYPE>_copy(pobj->conf.base.xInitial, 1, SLC<VTYPE>_units, 0, cx);
    SLC<VTYPE>_copy(pobj->conf.base.cParams, 1, SLC<VTYPE>_units, 0, cc);
    pobj->conf.base.cx = cx;
    pobj->conf.base.cy = cy;
    pobj->conf.base.cc = cc;
    pobj->conf.base.objective = NULL;

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
    for (solver->iter = 0; solver->iter < solver->conf.base.maxIter; solver->iter++)
    {
        // calc y
        err = solver->conf.base.objective(
            solver->y->data.<VTYPE>, solver->conf.base.cy,
            solver->x->data.<VTYPE>, solver->conf.base.cx,
            solver->conf.base.cParams, solver->conf.base.cc,
            solver->conf.base.context
        );
        if (err) break;
        for (SLC<ITYPE>_t i = 0; i < solver->conf.base.cy; i++)
        {
            solver->negy->data.<VTYPE>[i] = -solver->y->data.<VTYPE>[i];
        }

        // calc Jacobian
        if (EXIT_SUCCESS != (err = <VTYPE>CalcJ(solver))) break;        

        // calc delta_x
        err = SLCMat<VTYPE>_SolveOD(solver->delta_x, solver->j, solver->negy, &solver->wkset);
        if (EXIT_SUCCESS != err) break;

        // calc x_new
        SLCMat<VTYPE>_Add(solver->x_new, solver->x, solver->delta_x);

        // calc normDX, normY
        solver->normDX = SLCBLAS<VTYPE>_AbsSum(solver->delta_x->data.<VTYPE>, solver->conf.base.cx);
        solver->normY = SLCBLAS<VTYPE>_AbsSum(solver->y->data.<VTYPE>, solver->conf.base.cy);

        // check convergence normDxMax, normYMax
        if ((solver->normDX < solver->conf.base.normDxMax) ||
            (solver->normY < solver->conf.base.normYMax))
        {
            solver->state = NLSLState_converged;
            break;
        }
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
