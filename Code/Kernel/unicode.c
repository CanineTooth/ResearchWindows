#include "unicode.h"

#if defined(ALLOC_PRAGMA)
#pragma alloc_text(PAGE, KrCompareUnicodeString)
#endif

VOID KrInitUnicodeString(
    OUT PUNICODE_STRING DestinationString, 
    IN PCWSTR SourceString OPTIONAL)
{
    USHORT length = 0;
    DestinationString->Length = 0;
    DestinationString->Buffer = (PWSTR)SourceString;
    if (ARGUMENT_PRESENT(SourceString))
    {
        while (*SourceString++)
        {
            length += sizeof(*SourceString);
        }
        DestinationString->Length = length;
        DestinationString->MaximumLength = length + (USHORT)sizeof(UNICODE_NULL);
    }
    else
    {
        DestinationString->MaximumLength = 0;
    }
}

LONG KrCompareUnicodeString(
	IN PCUNICODE_STRING String1,
	IN PCUNICODE_STRING String2,
	IN BOOLEAN CaseInSensitive
)
{
	PAGED_CODE();
    NT_ASSERT(String1);
    NT_ASSERT(String2);
	PCWSTR s1, s2, limit;
	LONG n1, n2;
	WCHAR c1, c2;
	s1 = String1->Buffer;
	s2 = String2->Buffer;
	n1 = String1->Length;
	n2 = String2->Length;

    NT_ASSERT((n1 & 1) == 0);
    NT_ASSERT((n2 & 1) == 0);
    NT_ASSERT(!(((((ULONG_PTR)s1 & 1) != 0) || (((ULONG_PTR)s2 & 1) != 0)) && (n1 != 0) && (n2 != 0)));

	limit = (PWCHAR)((PCHAR)s1 + (n1 <= n2 ? n1 : n2));
    if (CaseInSensitive) 
    {
        while (s1 < limit)
        {
            c1 = *s1++;
            c2 = *s2++;
            if (c1 != c2) 
            {
                c1 = upcase(c1);
                c2 = upcase(c2);
                if (c1 != c2) 
                {
                    return (LONG)(c1)-(LONG)(c2);
                }
            }
        }

    }
    else
    {
        while (s1 < limit)
        {
            c1 = *s1++;
            c2 = *s2++;
            if (c1 != c2) 
            {
                return (LONG)(c1)-(LONG)(c2);
            }
        }
    }

    return n1 - n2;
}