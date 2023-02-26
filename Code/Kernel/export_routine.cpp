#include "export_routine.h"
#include <ntifs.h>
#include <ntimage.h>

extern "C" unsigned long long ntoskrnl_base;

call::export_routine::~export_routine()
{
	m_routine_map.clear();
}

void call::export_routine::init_map()
{
	PIMAGE_EXPORT_DIRECTORY export_directory{};
	PULONG name_table_base{};
	PUSHORT name_ordinal_table_base{};
	PULONG function_table_base{};
	export_directory = (PIMAGE_EXPORT_DIRECTORY)(ntoskrnl_base +
		((PIMAGE_NT_HEADERS)(ntoskrnl_base +
			((PIMAGE_DOS_HEADER)(ntoskrnl_base))->e_lfanew))->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	name_table_base = (PULONG)((PCHAR)ntoskrnl_base + export_directory->AddressOfNames);
	name_ordinal_table_base = (PUSHORT)((PCHAR)ntoskrnl_base + export_directory->AddressOfNameOrdinals);
	function_table_base = (PULONG)((PCHAR)ntoskrnl_base + export_directory->AddressOfFunctions);

	ULONG i = export_directory->NumberOfNames;
	while (i--)
	{
		m_routine_map.insert(std::make_pair(
			std::hash<std::string>{}(reinterpret_cast<char*>(ntoskrnl_base) + name_table_base[i]),
			ntoskrnl_base + function_table_base[name_ordinal_table_base[i]]));
	}
}
