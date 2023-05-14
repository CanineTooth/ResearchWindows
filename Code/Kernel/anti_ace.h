#pragma once
#include <ntifs.h>

EXTERN_C_START
NTKERNELAPI
UCHAR* PsGetProcessImageFileName(__in PEPROCESS Process);
EXTERN_C_END

bool install_hook();
bool uninstall_hook();