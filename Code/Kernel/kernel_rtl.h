#ifndef KERNEL_RUNTIME_RTL_
#define KERNEL_RUNTIME_RTL_
#include <ntifs.h>
#include "unicode.h"
EXTERN_C_START
NTSTATUS KernelRuntimeInitialization(PLIST_ENTRY DriverSection);
void KernelRuntimeTermination();
PVOID KrFindExportedRoutineByName(PVOID DllBase, const char* RoutineName);
EXTERN_C_END
#endif // !KERNEL_RUNTIME_RTL_