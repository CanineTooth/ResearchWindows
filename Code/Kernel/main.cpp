#include "main.h"
#include "global_object.h"

#if defined(ALLOC_PRAGMA)
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, DriverUnload)
#endif

NTSTATUS
DriverEntry(
	_In_ struct _DRIVER_OBJECT* DriverObject,
	_In_ PUNICODE_STRING RegistryPath
)
{
	PAGED_CODE();
	UNREFERENCED_PARAMETER(RegistryPath);
	NTSTATUS status{};
	DriverObject->DriverUnload = DriverUnload;

	status = GlobalObjectInitialization();
	if (!NT_SUCCESS(status))
	{
		return status;
	}
	return status;
}

VOID DriverUnload(
	_In_ struct _DRIVER_OBJECT* DriverObject)
{
	PAGED_CODE();
	UNREFERENCED_PARAMETER(DriverObject);
	GlobalObjectTermination();
}