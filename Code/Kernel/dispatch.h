#pragma once
#include <ntifs.h>
EXTERN_C_START
DRIVER_DISPATCH DispatchCreate;
DRIVER_DISPATCH DispatchClose;
DRIVER_DISPATCH DeviceIoControl;
EXTERN_C_END

#define DEVICE_NAME     L"\\Device\\CTRK"
#define DOS_DEVICE_NAME L"\\DosDevices\\CTRK"

// SDDL string for HAX device object
// [Access]              [SID]
// All                   System
// All                   Administrators
// Read/Write/Execute    Authenticated Users
#define SDDL_DEVOBJ_SYS_ALL_ADM_ALL_AU_RWX \
	L"D:P(A;;GA;;;SY)(A;;GA;;;BA)(A;;GRGWGX;;;AU)"