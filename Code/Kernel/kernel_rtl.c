#include "kernel_rtl.h"
EXTERN_C_START
#if defined(ALLOC_PRAGMA)
#pragma alloc_text(INIT, KernelRuntimeInitialization)
#pragma alloc_text(PAGE, KernelRuntimeTermination)
#endif

ULONG64 ntoskrnl_base = 0;

NTSTATUS KernelRuntimeInitialization(PLIST_ENTRY DriverSection)
{
	NTSTATUS status = STATUS_SUCCESS;
	UNICODE_STRING ntos_name;
	KrInitUnicodeString(&ntos_name, L"ntoskrnl.exe");
	PLIST_ENTRY next = DriverSection->Flink;
	while (next != DriverSection)
	{
		//_KLDR_DATA_TABLE_ENTRY+0x58 BaseDllName
		if (KrCompareUnicodeString(&ntos_name, (PUNICODE_STRING)((PUCHAR)(next) + 0x58), TRUE) == 0)
		{
			//_KLDR_DATA_TABLE_ENTRY+0x30 DllBase
			ntoskrnl_base = *(PULONG64)((PUCHAR)(next)+0x30);
			break;
		}
		next = next->Flink;
	}
	if (!ntoskrnl_base)
	{
		status = STATUS_NOT_FOUND;
	}
	return status;
}

void KernelRuntimeTermination()
{

}
EXTERN_C_END