#pragma once
#include <ntifs.h>
#include <wdmsec.h>
EXTERN_C_START
DRIVER_INITIALIZE DriverEntry;
DRIVER_UNLOAD     DriverUnload;
EXTERN_C_END