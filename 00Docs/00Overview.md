# Overview of `SLC`
`SLC` is a general purpose framework for programming language C.
There are several features;
* Generic programming like template of C++ with more limited capability than C++,
* Linear algebraic library with a layered structure like BLAS and LAPACK
* Non-linear solver for continuous nonlinear problems with and without continuous first deriveratives,
* Unit test support functions
* Multi-threaded state machine

Table 1. Library groups
Deirectory | Description
-----------|------------
01Base     | Redefinitions of C built-in types and common functions and macros<br/>to support generic programming, Logging, JSON deserializer
02Container | 1-D, 2-D, 3-D arrays and linked lists of generic element types
03Math | Linear algebraic functions, 3D geometries, nonlinear simultaneous equations
04Control | Multithread capable state machine and a very simple scheduler

Table 2. Links to detailed documents
Group | Detailed item | Link
------|---------------|-------------------
01Base | Built-in type redefinitions | [01Base/BuiltIn](01Base/BuiltIn.md)
01Base | Logging, unit test, error handlig | [01Base/Diag](01Base/Diag.md)
01Base | JSON deserializer using JSMN | [01Base/JSON](01Base/JSON.md)
02Container | 1-D, 2-D, 3-D arrays | [02Container/Array](02Container/Array.md)
02Container | Linked list | [02Container/LinkedList](02Container/LinkedList.md)
03Math | Low level linear algebrarics with generic element type | [03Math/GenBLAS](03Math/GenBLAS.md)
03Math | Middle level linear algebraics with generic element type | [03Math/GenLA](03Math/GenLA.md)
03Math | Geometry library with generic element type | [03Math/GenGeom](03Math/GenGeom.md)
03Math | Signal processig with generic element type | [03Math/GenSigProc](03Math/GenSigProc.md)
04Control | Callable (several sets of function pointer types and void pointer) | [04Control/Callable](04Control/Callable.md)