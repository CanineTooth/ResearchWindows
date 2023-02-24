#include <ntifs.h>
#undef _HAS_EXCEPTIONS
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-macros"
#define _HAS_EXCEPTIONS false
#include <exception>
#pragma clang diagnostic pop

static const ULONG kstl_pool_tag = 'LTSK';
using pExFreePoolWithTag = VOID(*)(PVOID P, ULONG Tag);
using pExAllocatePoolWithTag = PVOID(*)(POOL_TYPE PoolType, SIZE_T NumberOfBytes, ULONG Tag);
using pKeBugCheck = VOID(*)(ULONG BugCheckCode);
EXTERN_C pExAllocatePoolWithTag ExAllocatePoolWithTag_base;
EXTERN_C pExFreePoolWithTag ExFreePoolWithTag_base;
EXTERN_C pKeBugCheck KeBugCheck_base;

DECLSPEC_NORETURN
static void KernelStlpRaiseException(_In_ ULONG bug_check_code)
{
#pragma warning(push)
#pragma warning(disable : 28159)
	KeBugCheck_base(bug_check_code);
#pragma warning(pop)
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-prototypes"

DECLSPEC_NORETURN
void __cdecl _invalid_parameter_noinfo_noreturn()
{
	KernelStlpRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
}

DECLSPEC_NORETURN
void __cdecl _invoke_watson(
	_In_opt_z_ wchar_t const* expression,
	_In_opt_z_ wchar_t const* function_name,
	_In_opt_z_ wchar_t const* file_name,
	_In_ unsigned int const   line_number,
	_In_ uintptr_t const      reserved)
{
	(expression);
	(function_name);
	(file_name);
	(line_number);
	(reserved);
	KernelStlpRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
}

using _STDEXT exception;

using _Prhand = void(__cdecl*)(const exception&);

namespace std
{
	_CRTIMP2_PURE_IMPORT _Prhand _Raise_handler;

	DECLSPEC_NORETURN void __cdecl _Xbad_alloc()
	{
		KernelStlpRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
	}
	DECLSPEC_NORETURN void __cdecl _Xinvalid_argument(_In_z_ const char*)
	{
		KernelStlpRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
	}
	DECLSPEC_NORETURN void __cdecl _Xlength_error(_In_z_ const char*)
	{
		KernelStlpRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
	}
	DECLSPEC_NORETURN void __cdecl _Xout_of_range(_In_z_ const char*)
	{
		KernelStlpRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
	}
	DECLSPEC_NORETURN void __cdecl _Xoverflow_error(_In_z_ const char*)
	{
		KernelStlpRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
	}
	DECLSPEC_NORETURN void __cdecl _Xruntime_error(_In_z_ const char*)
	{
		KernelStlpRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
	}
	DECLSPEC_NORETURN void __cdecl _Xbad_function_call()
	{
		KernelStlpRaiseException(KMODE_EXCEPTION_NOT_HANDLED);
	}
}  // namespace std

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) void* __cdecl operator new(size_t size)
{
	auto p = ExAllocatePoolWithTag_base((POOL_TYPE)(NonPagedPool | POOL_ZERO_ALLOCATION), size == 0 ? 1 : size, kstl_pool_tag);
	if (!p)
		KernelStlpRaiseException(MUST_SUCCEED_POOL_EMPTY);
	return p;
}

void __cdecl operator delete(void* p)
{
	if (p)
	{
		ExFreePoolWithTag_base(p, kstl_pool_tag);
	}
}

void __cdecl operator delete(void* p, size_t size)
{
	size;
	if (p)
	{
		ExFreePoolWithTag_base(p, kstl_pool_tag);
	}
}

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) void* __cdecl operator new[](size_t size)
{
	auto p = ExAllocatePoolWithTag_base((POOL_TYPE)(NonPagedPool | POOL_ZERO_ALLOCATION), size == 0 ? 1 : size, kstl_pool_tag);
	if (!p)
		KernelStlpRaiseException(MUST_SUCCEED_POOL_EMPTY);
	return p;
}

void __cdecl operator delete[](void* p)
{
	if (p)
	{
		ExFreePoolWithTag_base(p, kstl_pool_tag);
	}
}

void __cdecl operator delete[](void* p, size_t size)
{
	size;
	if (p)
	{
		ExFreePoolWithTag_base(p, kstl_pool_tag);
	}
}
#pragma clang diagnostic pop