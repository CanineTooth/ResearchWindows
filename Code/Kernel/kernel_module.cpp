#include "kernel_module.h"
#include <ntifs.h>
#include "export_routine.h"
#include "kernel_rtl.h"

std::pair<void*, unsigned long> system_info::kernel_module::get_module_info(const wchar_t* ModuleName)
{
    std::pair<void*, unsigned long> result{};
    UNICODE_STRING module_name{};
    KrInitUnicodeString(&module_name, ModuleName);

    CALL_NAME(KeEnterCriticalRegion)();
    CALL_NAME(ExAcquireResourceExclusiveLite)(DATA_NAME(PsLoadedModuleResource, PERESOURCE), TRUE);

    PLIST_ENTRY module_list = DATA_NAME(PsLoadedModuleList, PLIST_ENTRY);
    PLIST_ENTRY next = module_list->Flink;

    while (next != module_list)
    {
        //_KLDR_DATA_TABLE_ENTRY+0x58 BaseDllName
        if (KrCompareUnicodeString(&module_name, (PUNICODE_STRING)((PUCHAR)(next)+0x58), TRUE) == 0)
        {
            //_KLDR_DATA_TABLE_ENTRY+0x30 DllBase
            result.first = *(void**)((PUCHAR)(next)+0x30);
            //_KLDR_DATA_TABLE_ENTRY+0x40 SizeOfImage
            result.second = *(unsigned long*)((PUCHAR)(next)+0x40);
            break;
        }
        next = next->Flink;
    }

    CALL_NAME(ExReleaseResourceLite)(DATA_NAME(PsLoadedModuleResource, PERESOURCE));
    CALL_NAME(KeLeaveCriticalRegion)();

    return result;
}