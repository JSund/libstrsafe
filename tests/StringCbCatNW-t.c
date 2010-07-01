#include <strsafe.h>
#include <wchar.h>
#include "tap/basic.h"

int main(void){
	wchar_t dest[11] = L"test";
	wchar_t dest2[11] = L"TEST";
	wchar_t empty[10] = L"";
	
	plan(16);

	ok(SUCCEEDED(StringCbCatNW(dest, 11 * sizeof(wchar_t), L"test", 4 * sizeof(wchar_t))),
			"Concatenate entire strings.");
	is_wstring(L"testtest", dest,
			"Result of concatenating entire strings.");

	dest[4] = '\0'; /* Reset dest to "test". */

	ok(SUCCEEDED(StringCbCatNW(dest, 11 * sizeof(wchar_t),
					L"", 1 * sizeof(wchar_t))),
			"Concatenate with empty source.");
	is_wstring(L"test", dest,
			"Result of concatenating with empty source.");

	ok(SUCCEEDED(StringCbCatNW(empty, 10 * sizeof(wchar_t),
					L"test", 4 * sizeof(wchar_t))),
			"Concatenate with empty destination.");
	is_wstring(L"test", empty,
			"Result of concatenating with empty destination.");

	ok(SUCCEEDED(StringCbCatNW(dest2, 11 * sizeof(wchar_t),
					dest, 11 * sizeof(wchar_t))),
			"Concatenate two buffers with additional capacity.");
	is_wstring(L"TESTtest", dest2,
			"Result of concatenating buffers with additional capacity.");
	
	ok(StringCbCatNW(dest, 11 * sizeof(wchar_t),
				L"longer string", 12 * sizeof(wchar_t)) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Concatenate a string that is too long.");
	is_wstring(L"testlonger", dest,
			"Result of concatenating two strings that are too long.");

	ok(SUCCEEDED(StringCbCatNW(dest2, 11 * sizeof(wchar_t),
					dest, 2 * sizeof(wchar_t))),
			"Concatenate a few characters from a longer string.");
	is_wstring(L"TESTtestte", dest2,
			"Result of concatenating a few characters.");
	
	ok(StringCbCatNW(dest, 11 * sizeof(wchar_t),
				L"test", 4 * sizeof(wchar_t)) ==
			STRSAFE_E_INVALID_PARAMETER,
			"Concatenate to already full destination.");
	is_wstring(L"testlonger", dest,
			"Make sure destination was not modified.");

	ok(StringCbCatNW(dest, 0 * sizeof(wchar_t),
				L"test", 4 * sizeof(wchar_t)) ==
			STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if cchDest is zero.");
	is_wstring(L"testlonger", dest,
			"Make sure destination was not modified.");

	return 0;
}
