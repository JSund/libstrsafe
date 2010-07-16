/*
 * Wide character string support for the C TAP Harness by Russ Allbery.
 *
 * Copyright 2010 Jonas Sundberg <jsund@jsund.com>
 */

#include "wide.h"

/*
 * Takes a wide character string and what the string should be, and assumes
 * the test passes if those strings match (using wcscmp).
 */
void
is_wstring(const wchar_t *wanted, const wchar_t *seen, const char *format, ...)
{
	va_list argList;
	va_start(argList, format);
    if (wanted == NULL)
        wanted = L"(null)";
    if (seen == NULL)
        seen = L"(null)";
	if(wcscmp(wanted, seen) != 0){
		printf("# wanted: %ls\n", wanted);
		printf("#   seen: %ls\n", seen);
	}
	okv(wcscmp(wanted, seen) == 0, format, argList);
	va_end(argList);
}
