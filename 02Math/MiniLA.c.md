# Control
```
{
    "out": "MiniLA.c",
    "vtypes": ["r32", "r64", "c64", "c128"],
    "rtypes": ["r32", "r64", "r32", "r64"],
    "itype": "i32",
    "stype": "u32"
}
```
# Head
```
#include "SLC/MiniLA.h"
#include "SLC/NumbersCopy.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
```
# Generic
## matrix-matrix addition
```
#pragma region <VTYPE>_functions
#pragma region <VTYPE>_basic_matrix_operations
void SLCMat<VTYPE>_Add(SLCPArray_t dst, SLCPCArray_t src0, SLCPCArray_t src1)
{
    const SLC<ITYPE>_t src0_rows = SLCArray_MatRows(src0);
    const SLC<ITYPE>_t src0_columns = SLCArray_MatColumns(src0);
    const SLC<ITYPE>_t src1_rows = SLCArray_MatRows(src1);
    const SLC<ITYPE>_t src1_columns = SLCArray_MatColumns(src1);
    const SLC<ITYPE>_t dst_rows = SLCArray_MatRows(dst);
    const SLC<ITYPE>_t dst_columns = SLCArray_MatColumns(dst);
    assert(src0_rows == dst_rows);
    assert(src0_columns == dst_columns);
    assert(src1_rows == dst_rows);
    assert(src1_columns == dst_columns);
    const SLC<VTYPE>_t* src0_elements = src0-> data.<VTYPE>;
    const SLC<VTYPE>_t* src1_elements = src1-> data.<VTYPE>;
    SLC<VTYPE>_t* dst_elements = dst-> data.<VTYPE>;
    SLCBLAS<VTYPE>_Add(dst_elements, src0_elements, src1_elements, dst_rows * dst_columns);
}
```
## matrix-matrix addition with each scaling factors
```
void SLCMat<VTYPE>_ScaleAdd(SLCPArray_t dst, SLCPCArray_t src0, const SLC<VTYPE>_t* scale0,
    SLCPCArray_t src1, const SLC<VTYPE>_t* scale1
) {
    const SLC<ITYPE>_t src0_rows = SLCArray_MatRows(src0);
    const SLC<ITYPE>_t src0_columns = SLCArray_MatColumns(src0);
    const SLC<ITYPE>_t src1_rows = SLCArray_MatRows(src1);
    const SLC<ITYPE>_t src1_columns = SLCArray_MatColumns(src1);
    const SLC<ITYPE>_t dst_rows = SLCArray_MatRows(dst);
    const SLC<ITYPE>_t dst_columns = SLCArray_MatColumns(dst);
    assert(src0_rows == dst_rows);
    assert(src0_columns == dst_columns);
    assert(src1_rows == dst_rows);
    assert(src1_columns == dst_columns);
    const SLC<VTYPE>_t* src0_elements = src0-> data.<VTYPE>;
    const SLC<VTYPE>_t* src1_elements = src1-> data.<VTYPE>;
    SLC<VTYPE>_t* dst_elements = dst-> data.<VTYPE>;
    SLCBLAS<VTYPE>_ScaleAdd(dst_elements,
        src0_elements, scale0,
        src1_elements, scale1,
        dst_rows * dst_columns);
}
```
## matrix-scalar scaling
```
void SLCMat<VTYPE>_Scale(SLCPArray_t dst, SLCPCArray_t src, const SLC<VTYPE>_t* scale)
{
    const SLC<ITYPE>_t dst_rows = SLCArray_MatRows(dst);
    const SLC<ITYPE>_t dst_columns = SLCArray_MatColumns(dst);
    const SLC<ITYPE>_t src_rows = SLCArray_MatRows(src);
    const SLC<ITYPE>_t src_columns = SLCArray_MatColumns(src);
    assert(dst_rows == src_rows);
    assert(dst_columns == src_columns);
    SLC<VTYPE>_t* dst_elements = dst-> data.<VTYPE>;
    const SLC<VTYPE>_t* src_elements = src-> data.<VTYPE>;
    SLCBLAS<VTYPE>_Scale(dst_elements, src_elements, scale, dst_rows * dst_columns);
}
```
## matrix-matrix multiplication, transpose, and transpose-conjugate
```
void SLCMat<VTYPE>_Multiply(SLCPArray_t dst, SLCPCArray_t src0, SLCPCArray_t src1, SLCPArray_t work)
{
    const SLC<ITYPE>_t dst_rows = SLCArray_MatRows(dst);
    const SLC<ITYPE>_t dst_columns = SLCArray_MatColumns(dst);
    const SLC<ITYPE>_t src0_rows = SLCArray_MatRows(src0);
    const SLC<ITYPE>_t src0_columns = SLCArray_MatColumns(src0);
    const SLC<ITYPE>_t src1_rows = SLCArray_MatRows(src1);
    const SLC<ITYPE>_t src1_columns = SLCArray_MatColumns(src1);
    assert(dst_rows == src0_rows);
    assert(dst_columns == src1_columns);
    assert(src0_columns == src1_rows);
    SLCMat<VTYPE>_Transpose(work, src1);
    const SLC<VTYPE>_t* src0_elements = src0-> data.<VTYPE>;
    SLC<VTYPE>_t* dst_elements = dst-> data.<VTYPE>;
    for (SLC<ITYPE>_t row = 0; row < dst_rows; row++)
    {
        const SLC<VTYPE>_t* work_elements = work-> data.<VTYPE>;
        for (SLC<ITYPE>_t column = 0; column < dst_columns; column++)
        {
            *dst_elements++ = SLCBLAS<VTYPE>_ProductSum(src0_elements, work_elements, src0_columns);
            work_elements += src1_rows;
        }
        src0_elements += src0_columns;
    }
}

void SLCMat<VTYPE>_Transpose(SLCPArray_t dst, SLCPCArray_t src)
{
    const SLC<ITYPE>_t src_rows = SLCArray_MatRows(src);
    const SLC<ITYPE>_t src_columns = SLCArray_MatColumns(src);
    const SLC<ITYPE>_t dst_rows = SLCArray_MatRows(dst);
    const SLC<ITYPE>_t dst_columns = SLCArray_MatColumns(dst);
    assert(src_rows == dst_columns);
    assert(src_columns == dst_rows);
    SLC<VTYPE>_t* dst_elements = dst-> data.<VTYPE>;
    const SLC<VTYPE>_t* src_elements = src-> data.<VTYPE>;
    for (SLC<ITYPE>_t  src_row = 0; src_row < src_rows; src_row++)
    {
        SLC<VTYPE>_scatter(dst_elements, dst_columns, src_elements, src_columns);
        dst_elements++;
        src_elements += src_columns;
    }
}

void SLCMat<VTYPE>_TransConj(SLCPArray_t dst, SLCPCArray_t src)
{
    const SLC<ITYPE>_t src_rows = SLCArray_MatRows(src);
    const SLC<ITYPE>_t src_columns = SLCArray_MatColumns(src);
    const SLC<ITYPE>_t dst_rows = SLCArray_MatRows(dst);
    const SLC<ITYPE>_t dst_columns = SLCArray_MatColumns(dst);
    assert(src_rows == dst_columns);
    assert(src_columns == dst_rows);
    const SLC<VTYPE>_t* src_elements = src-> data.<VTYPE>;
    for (SLC<ITYPE>_t  src_row = 0; src_row < src_rows; src_row++)
    {
        SLC<VTYPE>_t* dst_elements = dst-> data.<VTYPE> + src_row;
        for (SLC<ITYPE>_t src_column = 0; src_column < src_columns; src_column++)
        {
            *dst_elements = SLC<VTYPE>_conj(src_elements[src_column]);
            dst_elements += dst_columns;
        }
    }
}
```
## matrix inversion utility functions
```
static void <VTYPE>_CopyToLeftSquare(SLC<VTYPE>_t* dst, SLC<ITYPE>_t dst_stride,
    const SLC<VTYPE>_t* src, SLC<ITYPE>_t rows    
) {
    for (SLC<ITYPE>_t row = 0; row < rows; row++)
    {
        SLC<VTYPE>_copy(dst, 1, src, 1, rows);
        dst += dst_stride;
        src += rows;
    }
}

static void <VTYPE>_PrepareRightHalf(SLC<VTYPE>_t* dst, SLC<ITYPE>_t rows, SLC<ITYPE>_t dst_stride)
{
    dst += rows;
    SLC<ITYPE>_t columns = dst_stride - rows;
    for (SLC<ITYPE>_t row = 0; row < rows; row++)
    {
        SLC<VTYPE>_copy(dst, 1, SLC<VTYPE>_units, 0, columns);
        dst[row] = SLC<VTYPE>_units[1];
        dst += dst_stride;
    }
}

static void <VTYPE>_CopyFromRightHalf(SLC<VTYPE>_t* dst, SLC<ITYPE>_t dst_rows,
    const SLC<VTYPE>_t* src, SLC<ITYPE>_t src_stride
) {
    src+= dst_rows; // point the beginning of the right half of the work matrix
    for (SLC<ITYPE>_t row = 0; row < dst_rows; row++)
    {
        SLC<VTYPE>_copy(dst, 1, src, 1, dst_rows);
        src += dst_rows;
        dst += src_stride;
    }
}

SLC<ITYPE>_t <VTYPE>_BestPivot(SLC<VTYPE>_t* work_row_head, SLC<ITYPE>_t work_row_length,
    SLC<ITYPE>_t row, SLC<ITYPE>_t work_rows, SLC<ITYPE>_t work_columns
) {
    SLC<RTYPE>_t pv_rel_mag = SLC<RTYPE>_units[2]; // assign -1
    SLC<ITYPE>_t pv_candidate_index = -1, left_part_remaining = work_row_length - work_rows;
    for (; row < work_rows; row++, work_row_head += work_columns)
    {
        SLC<RTYPE>_t pv_mag = SLC<VTYPE>_abs(*work_row_head);
        SLC<RTYPE>_t row_mag = SLCBLAS<VTYPE>_AbsSum(work_row_head, left_part_remaining);
        SLC<RTYPE>_t pv_rel_mag2 = pv_mag / row_mag;
        if ((pv_rel_mag2 < SLC<RTYPE>_stdtol) || // pv_rel_mag2 is too small to accept
            (pv_rel_mag2 <= pv_rel_mag)) // pv_rel_mag2 is NOT better than the current best
            continue;
        pv_rel_mag = pv_rel_mag2;
        pv_candidate_index = row;
    }
    return pv_candidate_index;
}
```

## Main body of SLCMat<VTYPE>_Inv()
```
SLCerrno_t SLCMat<VTYPE>_Inv(SLCPArray_t dst, SLCPCArray_t src, SLCPArray_t work)
{
    const SLC<ITYPE>_t src_rows = SLCArray_MatRows(src);
    const SLC<ITYPE>_t src_columns = SLCArray_MatColumns(src);
    const SLC<ITYPE>_t dst_rows = SLCArray_MatRows(dst);
    const SLC<ITYPE>_t dst_columns = SLCArray_MatColumns(dst);
    const SLC<ITYPE>_t work_rows = SLCArray_MatRows(work);
    const SLC<ITYPE>_t work_columns = SLCArray_MatColumns(work);
    assert(src_rows == src_columns);
    assert(src_rows == dst_rows);
    assert(src_rows == dst_columns);
    assert(src_rows == work_rows);
    assert((src_rows << 1) == work_columns);
    SLCerrno_t err = EXIT_SUCCESS;
    const SLC<VTYPE>_t* src_elements = src->data.<VTYPE>;
    SLC<VTYPE>_t* dst_elements = dst->data.<VTYPE>;
    SLC<VTYPE>_t* work_elements = work->data.<VTYPE>;
    do {
        // prepare working matrix
        <VTYPE>_CopyToLeftSquare(work_elements, work_columns, src_elements, src_rows);
        <VTYPE>_PrepareRightHalf(work_elements, work_rows, work_columns);

        // Gaussian elimination
        SLC<VTYPE>_t* work_row_head = work_elements; // the head element of the current pivot row
        SLC<ITYPE>_t work_row_length = work_columns;
        for (SLC<ITYPE>_t row = 0; row < src_rows; row++,
            work_row_head += (work_columns + 1), // move to next row
            work_row_length--)
        {
            // Select the best pivot row
            SLC<ITYPE>_t new_pv_row = 
                <VTYPE>_BestPivot(work_row_head, work_row_length, row, work_rows, work_columns);
            if (new_pv_row == -1)
            { // src matrix is singular.
                err = SLC_ESINGULAR;
                break;
            }
            if (new_pv_row != row)
            { // swap pivot row
                SLC<VTYPE>_t* row_head_to_swap = work_row_head + (new_pv_row - row) * work_columns;
                SLC<VTYPE>_swap(work_row_head, 1, row_head_to_swap, 1, work_row_length);
            }

            // Normalize pivot row
            SLC<VTYPE>_t scale = SLC<VTYPE>_units[1] / *work_row_head;
            SLCBLAS<VTYPE>_ScaleAss(work_row_head, &scale, work_row_length);

            // Eliminate pivot column elements other than the pivot element
            SLC<VTYPE>_t* row_head_to_eliminate = work_elements + row;
            for (SLC<ITYPE>_t row2 = 0; row2 < work_rows; row2++, row_head_to_eliminate += work_columns)
            {
                if (row == row2) continue; // skip eliminating
                scale = -(*row_head_to_eliminate);
                SLCBLAS<VTYPE>_ScaleAddAss(work_row_head, row_head_to_eliminate, &scale, work_row_length);
            }
        }

        if (err) continue; // src is singular
        // copy from work to dst
        <VTYPE>_CopyFromRightHalf(dst_elements, dst_rows, work_elements, work_columns);
    } while (0);
    return err;
}

```
## Useful constant matrices; i.e. zero matrix and identity matrix
```
// zero matrix
void SLCMat<VTYPE>_0(SLCPArray_t dst)
{
    assert(sizeof(SLC<VTYPE>_t) == SLCArray_UnitSize(dst));
    SLC<ITYPE>_t count = SLCArray_MatRows(dst) * SLCArray_MatColumns(dst);
    SLC<VTYPE>_t* dst_elements = dst->data.<VTYPE>;
    SLC<VTYPE>_copy(dst_elements, 1, SLC<VTYPE>_units, 0, count);
}

// identity matrix
void SLCMat<VTYPE>_I(SLCPArray_t dst)
{
    SLC<ITYPE>_t rows = SLCArray_MatRows(dst);
    SLC<ITYPE>_t columns = SLCArray_MatColumns(dst);
    assert(rows == columns);
    SLCMat<VTYPE>_0(dst);
    SLC<ITYPE>_t diagonal_step = columns + 1;
    SLC<VTYPE>_t* dst_elements = dst->data.<VTYPE>;
    SLC<VTYPE>_copy(dst_elements, diagonal_step, SLC<VTYPE>_units + 1, 0, rows);
}
#pragma endregion <VTYPE>_basic_matrix_operations
```
## Linear equation solvers
```
#pragma region <VTYPE>_linear_equation_solvers
static void <VTYPE>_CopyRHS(
    SLC<VTYPE>_t* dst, SLC<ITYPE>_t dst_stride,
    const SLC<VTYPE>_t* src, SLC<ITYPE>_t src_rows, SLC<ITYPE>_t src_columns
) {
    for (SLC<ITYPE>_t row = 0; row < src_rows; row++, src+= src_columns, dst += dst_stride)
    {
        SLC<VTYPE>_copy(dst, 1, src, 1, src_columns);
    }
}
```
## Backward assignment
Considering a upper trianglular matrix and a multicolumn right hand side matrix.
Consequently a solution is also a multicolumn matrix.

$$\begin{equation}
\bold{\text{L}} = \begin{bmatrix}
1 & l_{12} & l_{13} & \cdots & l_{1N} \\
0 & 1 & l_{23} & \cdots & l_{2N} \\
\vdots & 0 & \ddots & & \vdots \\
0 & 0 & \cdots & 1 & l_{N-1,N}\\
0 & 0 & \cdots & 0 & 1
\end{bmatrix}\end{equation}$$

$$\begin{equation}\bold{\text{R}} = \begin{bmatrix}
r_{11} & r_{12} & \cdots & r_{1M} \\
r_{21} & r_{22} & \cdots & r_{2M} \\
\vdots & \vdots & \ddots & \vdots \\
r_{N-1,1} & r_{N-1,2} & \cdots & r_{N-1,M} \\
r_{N1} & r_{N2} & \cdots & r_{NM}
\end{bmatrix}
\end{equation}$$

The solution matrix $\bold{\text{X}}$ is
$$\begin{equation}
\bold{\text{X}} = \begin{bmatrix}
x_{11} & x_{12} & \cdots & x_{1M} \\
x_{21} & x_{22} & \cdots & x_{2M} \\
\vdots & \vdots & \ddots & \vdots \\
x_{N-1,1} & x_{N-1,2} & \cdots & x_{N-1,M} \\
x_{N1} & x_{N2} & \cdots & x_{NM}
\end{bmatrix}
\end{equation}$$
The fully determined linear equation is
$$\begin{equation}
\bold{\text{LX}} = \bold{\text{R}}
\end{equation}$$
Expanding the equation in line-by-line form and in backward order,
$$\begin{equation}\begin{matrix}
x_{N1} & = & r_{N1} \\
x_{N-1,1} + l_{N-1,N}x_{N1} & = & r_{N-1,1} \\
x_{N-2,1} + l_{N-2,N-1}x_{N-1,1} + l_{N-2,N}x_{N,1} &= & r_{N-2,1} \\
x_{N-3,1} + l_{N-3,N-2}x_{N-2,1} + l_{N-3,N-1}x_{N-1,1} + l_{N-3,N}x_{N1} & = & r_{N-3,1} \\
\cdots & = & \cdots \\
x_{21} + l_{23}x_{31} + l_{24}x_{41} + \cdots + l_{2,N-1}x_{N-1,1} + l_{2,N}x_{N1} &= & r_{21} \\
x_{11} + l_{12}x_{21} + l_{13}x_{31} + l_{14}x_{41} + \cdots + l_{1,N-1}x_{N-1,1} + l_{1N}x_{N1} &= & r_{11}
\end{matrix}\end{equation}$$
```
static void <VTYPE>_AssignBackward(SLCPArray_t dst, SLCPCArray_t work)
{
    SLC<ITYPE>_t dst_rows = SLCArray_MatRows(dst);
    SLC<ITYPE>_t dst_columns = SLCArray_MatColumns(dst);
    SLC<VTYPE>_t* dst_elements = dst->data.<VTYPE>;
    SLC<ITYPE>_t work_rows = SLCArray_MatRows(work);
    SLC<ITYPE>_t work_columns = SLCArray_MatColumns(work);
    const SLC<VTYPE>_t* work_elements = work->data.<VTYPE>;
    const SLC<VTYPE>_t* work_left_row_head = work_elements + (work_columns + 1) * (work_rows - 1);
    const SLC<VTYPE>_t* work_right_row_head = work_left_row_head + 1;
    SLC<VTYPE>_t* dst_row_head = dst_elements + dst_columns * (dst_rows - 1);
    for (SLC<ITYPE>_t backward_index = 0, work_row = work_rows;
        backward_index < work_rows;
        backward_index++,
        work_left_row_head -= (work_columns + 1),
        work_right_row_head -= work_columns,
        dst_row_head -= dst_columns)
    {
        // copy the most significant term
        SLC<VTYPE>_copy(dst_row_head, 1, work_right_row_head, 1, dst_columns);
        --work_row;
        for (SLC<ITYPE>_t left_column = work_row + 1; left_column < work_rows; left_column++)
        {
            for (SLC<ITYPE>_t dst_column = 0; dst_column < dst_columns; dst_column++)
            {
                dst_row_head[dst_column] -= 
                    work_left_row_head[left_column] * (dst_elements + left_column * dst_columns)[dst_column];
            }
        }
    }
}
```
## Solver main body
It consists of
* Assertion for matrix size matching
* Copying LHS and RHS to the working matrix
* Selecting best pivots
* Normalizing the pivot rows
* Gaussian elimination
* Backward assignment
```
SLCerrno_t SLCMat<VTYPE>_Solve(
    SLCPArray_t dst, SLCPCArray_t left, SLCPCArray_t right, SLCPArray_t work
) {
    SLC<ITYPE>_t dst_rows = SLCArray_MatRows(dst);
    SLC<ITYPE>_t dst_columns = SLCArray_MatColumns(dst);
    SLC<ITYPE>_t left_rows = SLCArray_MatRows(left);
    SLC<ITYPE>_t left_columns = SLCArray_MatColumns(left);
    SLC<ITYPE>_t right_rows = SLCArray_MatRows(right);
    SLC<ITYPE>_t right_columns = SLCArray_MatColumns(right);
    SLC<ITYPE>_t work_rows = SLCArray_MatRows(work);
    SLC<ITYPE>_t work_columns = SLCArray_MatColumns(work);
    assert(left_rows == left_columns); assert(dst_rows == left_columns);
    assert(dst_columns == right_columns); assert(left_rows == right_rows);
    assert(work_rows == left_rows); assert(work_columns == (left_columns + dst_columns));
    SLCerrno_t err = EXIT_SUCCESS;
    const SLC<VTYPE>_t* left_elements = left->data.<VTYPE>;
    const SLC<VTYPE>_t* right_elements = right->data.<VTYPE>;
    SLC<VTYPE>_t* work_elements = work->data.<VTYPE>;
    do {
        // copy to work matrix
        <VTYPE>_CopyToLeftSquare(work_elements, work_columns, left_elements, left_rows);
        <VTYPE>_CopyRHS(
            work_elements + left_columns, work_columns,
            right_elements, right_rows, right_columns);
        
        // Upper triangulation
        SLC<VTYPE>_t* work_row_head = work_elements;
        const SLC<VTYPE>_t _0 = SLC<VTYPE>_units[0], _1 = SLC<VTYPE>_units[1];
        for (SLC<ITYPE>_t row = 0, work_row_length = work_columns;
            row < work_rows;
            row++, work_row_length--, work_row_head += (work_columns + 1))
        {
            // select the best pivot row
            SLC<ITYPE>_t pv_row = <VTYPE>_BestPivot(
                work_row_head, work_row_length, row, work_rows, work_columns);
            if (pv_row == -1)
            {
                err = SLC_ESINGULAR;
                break;
            }
            if (pv_row != row)
            {
                SLC<VTYPE>_swap(work_row_head, 1,
                    work_row_head + (pv_row - row) * work_columns, 1, work_row_length);
            }

            // normalize the pivot row
            SLC<VTYPE>_t scale = _1 / *work_row_head;
            *work_row_head = _1;
            SLCBLAS<VTYPE>_ScaleAss(work_row_head + 1, &scale, work_row_length - 1);

            // eliminate pivot column elements beneath the pivot row
            if ((row + 1) == work_rows) continue;
            SLC<VTYPE>_t* row_head_to_eliminate = work_row_head + work_columns;
            for (SLC<ITYPE>_t row2 = row + 1; row2 < work_rows; row2++)
            {
                scale = -(*row_head_to_eliminate);
                *row_head_to_eliminate = _0;
                SLCBLAS<VTYPE>_ScaleAddAss(row_head_to_eliminate + 1, work_row_head + 1, &scale,
                    work_row_length - 1);
            }
        }

        if (err) continue; // left is singular.
        // backward assignment
        <VTYPE>_AssignBackward(dst, work);
    } while (0);
    return err;
}
```
## Overly determined equation
It is possible to solve overly determined linear simultaneous equations by
least-mean-square method.
```
void SLCMat<VTYPE>_InitSolveODWorkMatSet(
    SLCPCArray_t left, SLCPCArray_t right, SLCMat<VTYPE>_PSolveODWorkMatSet_t wkset
) {
    SLCi16_t unitsize = SLCArray_UnitSize(left);
    assert(SLCArray_UnitSize(right) == unitsize);
    SLCi16_t left_rows = SLCArray_MatRows(left);
    SLCi16_t right_rows = SLCArray_MatRows(right);

    const SLC4i16_t leftT_size = { unitsize, left->cont.i16[2], left->cont.i16[1], 1 };
    const SLC4i16_t leftTC_left_size = { unitsize, SLCArray_MatColumns(left), SLCArray_MatColumns(left), 1 };
    const SLC4i16_t rightT_size = { unitsize, right->cont.i16[2], right->cont.i16[1], 1 };
    const SLC4i16_t leftTC_right_size = 
        { unitsize, SLCArray_MatColumns(right), SLCArray_MatColumns(left), 1 };
    const SLC4i16_t work_size = 
        { unitsize, leftTC_left_size[1] + leftTC_right_size[1], leftTC_left_size[2], 1 };
    wkset->leftT = SLCArray_Alloc(leftT_size);
    wkset->leftTC_left = SLCArray_Alloc(leftTC_left_size);
    wkset->rightT = SLCArray_Alloc(rightT_size);
    wkset->leftTC_right = SLCArray_Alloc(leftTC_right_size);
    wkset->work = SLCArray_Alloc(work_size);
}

#define TEMP_SAFE_FREE(__pmat) if (__pmat) { free(__pmat);  __pmat = NULL; }
void SLCMat<VTYPE>_FreeSolveODWorkMatSet(SLCMat<VTYPE>_PSolveODWorkMatSet_t wkset)
{
    TEMP_SAFE_FREE(wkset->leftT);
    TEMP_SAFE_FREE(wkset->leftTC_left);
    TEMP_SAFE_FREE(wkset->rightT);
    TEMP_SAFE_FREE(wkset->leftTC_right);
    TEMP_SAFE_FREE(wkset->work);
}
#undef TEMP_SAFE_FREE

SLCerrno_t SLCMat<VTYPE>_EasySolveOD(SLCPArray_t dst, SLCPCArray_t left, SLCPCArray_t right)
{
    SLCMat<VTYPE>_SolveODWorkMatSet_t objwkset;
    SLCerrno_t err = SLCMat<VTYPE>_SolveOD(dst, left, right, &objwkset);
    SLCMat<VTYPE>_FreeSolveODWorkMatSet(&objwkset);
}

SLCerrno_t SLCMat<VTYPE>_SolveOD(SLCPArray_t dst, SLCPCArray_t left, SLCPCArray_t right,
    SLCMat<VTYPE>_PSolveODWorkMatSet_t wkset
) {
    SLCerrno_t err = EXIT_SUCCESS;
    SLC<ITYPE>_t dst_rows = SLCArray_MatRows(dst), dst_columns = SLCArray_MatColumns(dst);
    assert(SLCArray_UnitSize(dst) == SLCArray_UnitSize(left));
    assert(SLCArray_MatColumns(left) == dst_rows);
    assert(SLCArray_MatColumns(right) == dst_columns);
    SLCMat<VTYPE>_TransConj(wkset->leftTC, left);
    SLCMat<VTYPE>_Multiply(wkset->leftTC_left, wkset->leftTC, left, wkset->leftT);
    SLCMat<VTYPE>_Multiply(wkset->leftTC_right, wkset->leftTC, right, wkset->rightT);
    err = SLCMat<VTYPE>_Solve(dst, wkset->leftTC_left, wkset->leftTC_right, wkset->work);
    return err;
}
#pragma endregion <VTYPE>_linear_equation_solvers
```
```
#pragma region <VTYPE>_miscellaneous_operations
void SLCMat<VTYPE>_QRD(SLCPArray_t dst, SLCPArray_t src);

void SLCMat<VTYPE>_Print(FILE* out, const char* header, SLCPArray_t mat, const char* footer)
{
    fprintf(out, "%s",header);
    fprintf(out, "%d, %d\n", mat->cont.i16[1], mat->cont.i16[2]);
    const SLC<VTYPE>_t* ptr = mat->data.<VTYPE>;
    for (SLCi16_t row = 0; row < mat->cont.i16[2]; row++)
    {
        const char* delimiter = "";
        for (SLCi16_t column = 0; column < mat->cont.i16[1]; column++)
        {
            SLC<VTYPE>_print(out, delimiter, *ptr);
            ptr++;
            delimiter = ",";
        }
        fprintf(out, "\n");
    }
    fprintf(out, "%s",footer);
}
#pragma endregion <VTYPE>_miscellaneous_operations
#pragma endregion <VTYPE>_functions
```
# Foot
```
```
