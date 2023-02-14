#pragma once
#include <ntifs.h>
EXTERN_C_START

//
// Macros for Upper Casing a Unicode Code Point.
//
#define upcase(C) (WCHAR )(((C) >= 'a' && (C) <= 'z' ? (C) - ('a' - 'A') : (C)))

VOID KrInitUnicodeString(OUT PUNICODE_STRING DestinationString, IN PCWSTR SourceString OPTIONAL);
LONG KrCompareUnicodeString(IN PCUNICODE_STRING String1, IN PCUNICODE_STRING String2, IN BOOLEAN CaseInSensitive);

EXTERN_C_END