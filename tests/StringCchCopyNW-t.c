#include "../src/strsafe.h"
#include "tap/basic.h"

int main(void){
	plan(9);

	wchar_t dest[11];
	wchar_t dest2[11];
	
	ok(SUCCEEDED(StringCchCopyNW(dest, 11, L"test", 4)),
			"Copy entire string.");
	is_wstring(L"test", dest,
			"Result of copying entire string.");

	ok(SUCCEEDED(StringCchCopyNW(dest2, 11, dest, 11)),
			"Copy from buffer with additional capacity.");
	is_wstring(L"test", dest2,
			"Result of copying from buffer with additional capacity.");

	ok(SUCCEEDED(StringCchCopyNW(dest, 11, L"", 1)),
			"Copy empty string.");
	is_wstring(L"", dest,
			"Result of copying empty string.");
	
	ok(StringCchCopyNW(dest, 11, L"longer string", 12) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Copy a string that is too long.");
	is_wstring(L"longer str", dest,
			"Result of copying a string that is too long.");
	
	ok(StringCchCopyNW(dest, 0, L"test", 4) ==
			STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if cchDest is zero.");

	return 0;
}
