#include <strsafe.h>
#include <wchar.h>
#include "tap/basic.h"

int main(void){
	wchar_t dest[11];

	plan(9);

	ok(SUCCEEDED(StringCchPrintfW(dest, 11, L"")),
			"Print empty string.");
	is_wstring(L"", dest,
			"Result of printing empty string.");

	ok(SUCCEEDED(StringCchPrintfW(dest, 11, L"test")),
			"Print without format parameters.");
	is_wstring(L"test", dest,
			"Result of printing without format parameters.");

	ok(SUCCEEDED(StringCchPrintfW(dest, 11, L"%d", 17)),
			"Print integer to string.");
	is_wstring(L"17", dest,
			"Result of printing integer.");

	ok(SUCCEEDED(StringCchPrintfW(dest, 11, L"%%")),
			"Print percent sign to string.");
	is_wstring(L"%", dest,
			"Result of printing percent sign.");

	ok(StringCchPrintfW(dest, 0, L"") ==
			STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if destination capacity is zero.");

	return 0;
}
