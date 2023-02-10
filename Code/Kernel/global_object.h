#ifndef GLOBAL_OBJECT_H_
#define GLOBAL_OBJECT_H_
#include <ntifs.h>
EXTERN_C_START
/// Calls all constructors and register all destructor
/// @return STATUS_SUCCESS on success
_IRQL_requires_max_(PASSIVE_LEVEL) NTSTATUS GlobalObjectInitialization();

/// Calls all destructors
_IRQL_requires_max_(PASSIVE_LEVEL) void GlobalObjectTermination();
EXTERN_C_END
#endif  // GLOBAL_OBJECT_H_