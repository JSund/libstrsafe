#include <strsafe.h>
#include <wchar.h>
#include "tap/basic.h"

int main(void){
	wchar_t dest[11] = L"test";
	wchar_t dest2[11] = L"TEST";
	wchar_t empty[10] = L"";
	
	plan(16);

	ok(SUCCEEDED(StringCchCatNW(dest, 11, L"test", 4)),
			"Concatenate entire strings.");
	is_wstring(L"testtest", dest,
			"Result of concatenating entire strings.");

	dest[4] = '\0'; /* Reset dest to "test". */

	ok(SUCCEEDED(StringCchCatNW(dest, 11, L"", 1)),
			"Concatenate with empty source.");
	is_wstring(L"test", dest,
			"Result of concatenating with empty source.");

	ok(SUCCEEDED(StringCchCatNW(empty, 10, L"test", 4)),
			"Concatenate with empty destination.");
	is_wstring(L"test", empty,
			"Result of concatenating with empty destination.");

	ok(SUCCEEDED(StringCchCatNW(dest2, 11, dest, 11)),
			"Concatenate two buffers with additional capacity.");
	is_wstring(L"TESTtest", dest2,
			"Result of concatenating buffers with additional capacity.");
	
	ok(StringCchCatNW(dest, 11, L"longer string", 12) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Concatenate a string that is too long.");
	is_wstring(L"testlonger", dest,
			"Result of concatenating two strings that are too long.");

	ok(SUCCEEDED(StringCchCatNW(dest2, 11, dest, 2)),
			"Concatenate a few characters from a longer string.");
	is_wstring(L"TESTtestte", dest2,
			"Result of concatenating a few characters.");
	
	ok(StringCchCatNW(dest, 11, L"test", 4) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Concatenate to already full destination.");
	is_wstring(L"testlonger", dest,
			"Make sure destination was not modified.");

	ok(StringCchCatNW(dest, 0, L"test", 4) ==
			STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if cchDest is zero.");
	is_wstring(L"testlonger", dest,
			"Make sure destination was not modified.");

	return 0;
}
