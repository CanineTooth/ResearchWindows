#include "anti_ace.h"
#include "lazy_importer.hpp"
#include "detour.h"
extern "C" unsigned long long ntoskrnl_base;

typedef NTSTATUS(*PObpCallPreOperationCallbacks)(IN ULONG64 a1, IN ULONG64 a2, IN ULONG64 a3);

typedef bool(*PExEnumHandleTable)(IN PVOID HandleTable, IN PVOID EnumHandleProcedure, IN PVOID EnumParameter, OUT PHANDLE Handle);

PObpCallPreOperationCallbacks true_ObpCallPreOperationCallbacks = nullptr;
PExEnumHandleTable true_ExEnumHandleTable = nullptr;

NTSTATUS FakeObpCallPreOperationCallbacks(IN ULONG64 a1, IN ULONG64 a2, IN ULONG64 a3)
{
	if (!strcmp((const char*)(PsGetProcessImageFileName(PsGetCurrentProcess())), "ctd32.exe"))
	{
		return STATUS_SUCCESS;
	}
	return true_ObpCallPreOperationCallbacks(a1, a2, a3);
}

bool FakeExEnumHandleTable(IN PVOID HandleTable, IN PVOID EnumHandleProcedure, IN PVOID EnumParameter, OUT PHANDLE Handle)
{
	PEPROCESS Process = NULL;
	if (HandleTable)
	{
		Process = (PEPROCESS)(((PULONG64)HandleTable)[2]);
	}
	if (Process && PsGetCurrentProcess() != Process)
	{
		if (!strcmp((const char*)PsGetProcessImageFileName(Process), "ctd32.exe"))
		{
			return FALSE;
		}
	}
	return true_ExEnumHandleTable(HandleTable, EnumHandleProcedure, EnumParameter, Handle);
}

// hook ObpCallPreOperationCallbacks (PObpCallPreOperationCallbacks)(ntoskrnl_base + 0x5F0DA0);
// hook ExEnumHandleTable (PExEnumHandleTable)(ntoskrnl_base + 0x6B11E0);

// hook PsGetProcessDebugPort   0x328830   48 8B 81 78 05 00 00 -> 48 8B 81 00 20 00 00

bool install_hook()
{
	true_ObpCallPreOperationCallbacks = (PObpCallPreOperationCallbacks)(ntoskrnl_base + 0x5F0DA0);

	true_ExEnumHandleTable = (PExEnumHandleTable)(ntoskrnl_base + 0x6B11E0);

	//*(PUCHAR)(ntoskrnl_base + 0x328830 + 3) = 0;
	//*(PUCHAR)(ntoskrnl_base + 0x328830 + 4) = 0x20;

	DetourAttach((PVOID*)&true_ObpCallPreOperationCallbacks, FakeObpCallPreOperationCallbacks);
	DetourAttach((PVOID*)&true_ExEnumHandleTable, FakeExEnumHandleTable);
	DetourTransactionCommit();
	return true;
}


bool uninstall_hook()
{
	//*(PUCHAR)(ntoskrnl_base + 0x328830 + 3) = 0x78;
	//*(PUCHAR)(ntoskrnl_base + 0x328830 + 4) = 0x05;
	DetourDetach((PVOID*)&true_ObpCallPreOperationCallbacks, FakeObpCallPreOperationCallbacks);
	DetourDetach((PVOID*)&true_ExEnumHandleTable, FakeExEnumHandleTable);
	DetourTransactionCommit();
	return true;
}