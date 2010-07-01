#include <strsafe.h>
#include <wchar.h>
#include "tap/basic.h"

int main(void){
	wchar_t dest[11];
	wchar_t dest2[11];
	
	plan(9);

	ok(SUCCEEDED(StringCbCopyNW(dest, 11 * sizeof(wchar_t),
					L"test", 4 * sizeof(wchar_t))),
			"Copy entire string.");
	is_wstring(L"test", dest,
			"Result of copying entire string.");

	ok(SUCCEEDED(StringCbCopyNW(dest2, 11 * sizeof(wchar_t),
					dest, 11 * sizeof(wchar_t))),
			"Copy from buffer with additional capacity.");
	is_wstring(L"test", dest2,
			"Result of copying from buffer with additional capacity.");

	ok(SUCCEEDED(StringCbCopyNW(dest, 11 * sizeof(wchar_t),
					L"", 1 * sizeof(wchar_t))),
			"Copy empty string.");
	is_wstring(L"", dest,
			"Result of copying empty string.");
	
	ok(StringCbCopyNW(dest, 11 * sizeof(wchar_t),
				L"longer string", 12 * sizeof(wchar_t)) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Copy a string that is too long.");
	is_wstring(L"longer str", dest,
			"Result of copying a string that is too long.");
	
	ok(StringCbCopyNW(dest, 0 * sizeof(wchar_t),
				L"test", 4 * sizeof(wchar_t)) ==
			STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if cchDest is zero.");

	return 0;
}
