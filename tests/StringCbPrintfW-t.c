#include <strsafe.h>
#include <wchar.h>
#include "tap/basic.h"

int main(void){
	wchar_t dest[11];

	plan(11);

	ok(SUCCEEDED(StringCbPrintfW(dest, 11 * sizeof(wchar_t), L"")),
			"Print empty string.");
	is_wstring(L"", dest,
			"Result of printing empty string.");

	ok(SUCCEEDED(StringCbPrintfW(dest, 11 * sizeof(wchar_t), L"test")),
			"Print without format parameters.");
	is_wstring(L"test", dest,
			"Result of printing without format parameters.");

	ok(StringCbPrintfW(dest, 11 * sizeof(wchar_t), L"longer string") ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Print too long string.");
	is_wstring(L"longer str", dest,
			"Result of printing a too long string.");

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
