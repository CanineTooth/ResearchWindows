#include "kernel_rtl.h"
#include <ntimage.h>
EXTERN_C_START
#if defined(ALLOC_PRAGMA)
#pragma alloc_text(INIT, KernelRuntimeInitialization)
#pragma alloc_text(PAGE, KernelRuntimeTermination)
#endif

ULONG_PTR ntoskrnl_base = 0;
ULONG_PTR ExAllocatePoolWithTag_base = 0;
ULONG_PTR ExFreePoolWithTag_base = 0;
ULONG_PTR KeBugCheck_base = 0;

ULONG_PTR KrFindExportedRoutineByName(const char* RoutineName);

NTSTATUS KernelRuntimeInitialization(PLIST_ENTRY DriverSection)
{
	PAGED_CODE();
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
			ntoskrnl_base = *(PULONG_PTR)((PUCHAR)(next)+0x30);
			break;
		}
		next = next->Flink;
	}
	if (!ntoskrnl_base)
	{
		status = STATUS_NOT_FOUND;
	}
	else
	{
		ExAllocatePoolWithTag_base = KrFindExportedRoutineByName("ExAllocatePoolWithTag");
		ExFreePoolWithTag_base = KrFindExportedRoutineByName("ExFreePoolWithTag");
		KeBugCheck_base = KrFindExportedRoutineByName("KeBugCheck");
		if (!ExAllocatePoolWithTag_base || !ExFreePoolWithTag_base || !KeBugCheck_base)
		{
			status = STATUS_NOT_FOUND;
		}
	}
	return status;
}

void KernelRuntimeTermination()
{
	PAGED_CODE();
}

__forceinline LONG KrStringLenth(const char* String)
{
	LONG result = 0;
	while (*String != '\0')
	{
		String++;
		result++;
	}
	return result;
}

__forceinline LONG KrCompareString(const char* String1, const char* String2)
{
	PCSTR limit;
	LONG n1, n2;
	CHAR c1, c2;
	n1 = KrStringLenth(String1);
	n2 = KrStringLenth(String2);
	limit = (PCHAR)((PCHAR)String1 + (n1 <= n2 ? n1 : n2));
	while (String1 < limit)
	{
		c1 = *String1++;
		c2 = *String2++;
		if (c1 != c2)
		{
			return (LONG)(c1)-(LONG)(c2);
		}
	}
	return n1 - n2;
}

ULONG_PTR KrFindExportedRoutineByName(const char* RoutineName)
{
	PIMAGE_EXPORT_DIRECTORY export_directory = NULL;
	USHORT ordinal_number = 0;
	PULONG name_table_base = NULL;
	PUSHORT name_ordinal_table_base = NULL;

	export_directory = (PIMAGE_EXPORT_DIRECTORY)(ntoskrnl_base +
		((PIMAGE_NT_HEADERS)(ntoskrnl_base +
			((PIMAGE_DOS_HEADER)(ntoskrnl_base))->e_lfanew))->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	
	//
	// Initialize the pointer to the array of RVA-based ansi export strings.
	//

	name_table_base = (PULONG)((PCHAR)ntoskrnl_base + export_directory->AddressOfNames);

	//
	// Initialize the pointer to the array of USHORT ordinal numbers.
	//

	name_ordinal_table_base = (PUSHORT)((PCHAR)ntoskrnl_base + export_directory->AddressOfNameOrdinals);

	//
	// Lookup the desired name in the name table using a binary search.
	//

	LONG result = 0;
	ULONG low = 0;
	ULONG middle = 0;
	ULONG high = export_directory->NumberOfNames - 1;

	while (high >= low)
	{
		//
		// Compute the next probe index and compare the import name with the export name entry.
		//

		middle = (low + high) >> 1;
		result = KrCompareString(RoutineName, (PCHAR)ntoskrnl_base + name_table_base[middle]);
		if (result < 0) 
		{
			high = middle - 1;
		}
		else if (result > 0) 
		{
			low = middle + 1;
		}
		else 
		{
			break;
		}
	}

	//
	// If the high index is less than the low index, then a matching
	// table entry was not found. Otherwise, get the ordinal number
	// from the ordinal table.
	//

	if (high < low) 
	{
		return NULL;
	}

	ordinal_number = name_ordinal_table_base[middle];

	//
	// If the OrdinalNumber is not within the Export Address Table,
	// then this image does not implement the function.  Return not found.
	//

	if ((ULONG)ordinal_number >= export_directory->NumberOfFunctions) 
	{
		return NULL;
	}

	//
	// Index into the array of RVA export addresses by ordinal number.
	//

	PULONG addr;
	ULONG_PTR function_address;
	addr = (PULONG)((PCHAR)ntoskrnl_base + export_directory->AddressOfFunctions);
	function_address = (ULONG_PTR)((PCHAR)ntoskrnl_base + addr[ordinal_number]);
	return function_address;
}

EXTERN_C_END