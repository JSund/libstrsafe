#include "../src/strsafe.h"
#include "tap/basic.h"

int main(void){
	plan(7);

	wchar_t dest[11];
	
	ok(SUCCEEDED(StringCbCopyW(dest, 11 * sizeof(wchar_t), L"test")),
			"Copy short string.");
	is_wstring(L"test", dest,
			"Result of copying short string.");

	ok(SUCCEEDED(StringCbCopyW(dest, 11 * sizeof(wchar_t), L"")),
			"Copy empty string.");
	is_wstring(L"", dest,
			"Result of copying empty string.");
	
	ok(StringCbCopyW(dest, 11 * sizeof(wchar_t), L"longer string") ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Copy a string that is too long.");
	is_wstring(L"longer str", dest,
			"Result of copying a string that is too long.");

	ok(StringCbCopyW(dest, 0 * sizeof(wchar_t), L"test") ==
			STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if cchDest is zero.");

	return 0;
}
