#include "../src/strsafe.h"
#include "tap/basic.h"

int main(void){
	plan(7);

	wchar_t dest[11];
	
	ok(SUCCEEDED(StringCchCopyW(dest, 11, L"test")),
			"Copy short string.");
	is_wstring(L"test", dest,
			"Result of copying short string.");

	ok(SUCCEEDED(StringCchCopyW(dest, 11, L"")),
			"Copy empty string.");
	is_wstring(L"", dest,
			"Result of copying empty string.");
	
	ok(StringCchCopyW(dest, 11, L"longer string") ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Copy a string that is too long.");
	is_wstring(L"longer str", dest,
			"Result of copying a string that is too long.");

	ok(StringCchCopyW(dest, 0, L"test") ==
			STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if cchDest is zero.");

	return 0;
}
