#include "../src/strsafe.h"
#include "tap/basic.h"

int main(void){
	plan(9);

	wchar_t dest[11];

	ok(SUCCEEDED(StringCbPrintfW(dest, 11 * sizeof(wchar_t), L"")),
			"Print empty string.");
	is_wstring(L"", dest,
			"Result of printing empty string.");

	ok(SUCCEEDED(StringCbPrintfW(dest, 11 * sizeof(wchar_t), L"test")),
			"Print without format parameters.");
	is_wstring(L"test", dest,
			"Result of printing without format parameters.");

	ok(SUCCEEDED(StringCbPrintfW(dest, 11 * sizeof(wchar_t), L"%d", 17)),
			"Print integer to string.");
	is_wstring(L"17", dest,
			"Result of printing integer.");

	ok(SUCCEEDED(StringCbPrintfW(dest, 11 * sizeof(wchar_t), L"%%")),
			"Print percent sign to string.");
	is_wstring(L"%", dest,
			"Result of printing percent sign.");

	ok(StringCbPrintfW(dest, 0 * sizeof(wchar_t), L"") ==
			STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if destination capacity is zero.");

	return 0;
}
