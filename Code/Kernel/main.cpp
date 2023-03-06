#include "main.h"
#include "global_object.h"
#include "kernel_rtl.h"
#include "debug_log.hpp"
#include "dispatch.h"
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
	status = KernelRuntimeInitialization(reinterpret_cast<PLIST_ENTRY>(DriverObject->DriverSection));
	if (!NT_SUCCESS(status))
	{
		return status;
	}
	status = GlobalObjectInitialization();
	if (!NT_SUCCESS(status))
	{
		return status;
	}

	UNICODE_STRING device_name{};
	UNICODE_STRING dos_device_name{};
	UNICODE_STRING sddl{};
	PDEVICE_OBJECT pdevice_object{};

	RtlInitUnicodeString(&device_name, DEVICE_NAME);
	RtlInitUnicodeString(&sddl, SDDL_DEVOBJ_SYS_ALL_ADM_ALL_AU_RWX);
	status = IoCreateDeviceSecure(DriverObject,
		0,
		&device_name,
		FILE_DEVICE_UNKNOWN,
		FILE_DEVICE_SECURE_OPEN,
		FALSE,
		&sddl,
		NULL,
		&pdevice_object);
	if (!NT_SUCCESS(status))
	{
		util::dbglog::DbgLog("IoCreateDeviceSecure failed with status 0x%X\n", status);
		return status;
	}

	RtlInitUnicodeString(&dos_device_name, DOS_DEVICE_NAME);
	status = IoCreateSymbolicLink(&dos_device_name, &device_name);
	if (!NT_SUCCESS(status))
	{
		util::dbglog::DbgLog("IoCreateSymbolicLink failed with status 0x%X\n", status);
		IoDeleteDevice(pdevice_object);
		return status;
	}

	DriverObject->MajorFunction[IRP_MJ_CREATE] = DispatchCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = DispatchClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DeviceIoControl;

	return status;
}

VOID DriverUnload(
	_In_ struct _DRIVER_OBJECT* DriverObject)
{
	PAGED_CODE();
	UNICODE_STRING dos_device_name{};
	RtlInitUnicodeString(&dos_device_name, DOS_DEVICE_NAME);
	IoDeleteSymbolicLink(&dos_device_name);
	IoDeleteDevice(DriverObject->DeviceObject);
	GlobalObjectTermination();
	KernelRuntimeTermination();
}