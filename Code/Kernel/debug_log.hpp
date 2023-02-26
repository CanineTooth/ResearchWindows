#ifndef UTIL_DEBUG_LOG_HPP
#define UTIL_DEBUG_LOG_HPP
#include <ntifs.h>
#include <stdarg.h>
#include "lazy_importer.hpp"

namespace util
{
#define DEBUG_PREFIX "CT:  "
	class dbglog
	{
	public:
		static void DbgLog(PCCH Format, ...)
		{
			va_list arglist;
			va_start(arglist, Format);
			LI_FN(vDbgPrintExWithPrefix)(DEBUG_PREFIX,
				DPFLTR_IHVDRIVER_ID,
				DPFLTR_ERROR_LEVEL,
				Format,
				arglist);
		}
		static void DbgLogError(PCCH Format, ...)
		{
			va_list arglist;
			va_start(arglist, Format);
			LI_FN(vDbgPrintExWithPrefix)(DEBUG_PREFIX,
				DPFLTR_IHVDRIVER_ID,
				DPFLTR_ERROR_LEVEL,
				Format,
				arglist);
		}
		static void DbgLogWarning(PCCH Format, ...)
		{
			va_list arglist;
			va_start(arglist, Format);
			LI_FN(vDbgPrintExWithPrefix)(DEBUG_PREFIX,
				DPFLTR_IHVDRIVER_ID,
				DPFLTR_WARNING_LEVEL,
				Format,
				arglist);
		}
		static void DbgLogTrace(PCCH Format, ...)
		{
			va_list arglist;
			va_start(arglist, Format);
			LI_FN(vDbgPrintExWithPrefix)(DEBUG_PREFIX,
				DPFLTR_IHVDRIVER_ID,
				DPFLTR_TRACE_LEVEL,
				Format,
				arglist);
		}
		static void DbgLogInfo(PCCH Format, ...)
		{
			va_list arglist;
			va_start(arglist, Format);
			LI_FN(vDbgPrintExWithPrefix)(DEBUG_PREFIX,
				DPFLTR_IHVDRIVER_ID,
				DPFLTR_INFO_LEVEL,
				Format,
				arglist);
		}
	};
}
#endif // !UTIL_DEBUG_LOG_HPP