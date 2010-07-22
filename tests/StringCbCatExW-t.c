#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#define STRSAFE_NO_DEPRECATE
#include <strsafe.h>
#include "tap/wide.h"

void testDestEnd(){
	wchar_t dest[11];
	wchar_t * destEnd;

	diag("Test calculation of destEnd.");

	wcscpy(dest, L"foo");
	ok(SUCCEEDED(StringCbCatExW(dest, 11 * sizeof(wchar_t),
					L"Data", &destEnd, NULL, 0)),
			"Test calculation of destEnd "
			"while concatenating short strings.");
	is_wstring(L"fooData", dest,
			"Result of concatenating short strings.");
	ok(destEnd == &dest[7],
			"Value of destEnd after concatenating short strings.");

	ok(SUCCEEDED(StringCbCatExW(dest, 11 * sizeof(wchar_t),
					L"", &destEnd, NULL, 0)),
			"Test calculation of destEnd "
			"while appending an empty string.");
	is_wstring(L"fooData", dest,
			"Result of appending an empty string.");
	ok(destEnd == &dest[7],
			"Value of destEnd after appending an empty string.");

	wcscpy(dest, L"");
	ok(SUCCEEDED(StringCbCatExW(dest, 11 * sizeof(wchar_t),
					L"", &destEnd, NULL, 0)),
			"Test calculation of destEnd "
			"while concatenating two empty strings.");
	is_wstring(L"", dest,
			"Result of concatenating two empty strings.");
	ok(destEnd == dest,
			"Value of destEnd after concatenating two empty strings.");

	wcscpy(dest, L"TEST: ");
	ok(StringCbCatExW(dest, 11 * sizeof(wchar_t),
				L"longer string", &destEnd, NULL, 0) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Test calculation of destEnd "
			"while appending a too long string.");
	is_wstring(L"TEST: long", dest,
			"Result of appending a too long string.");
	ok(destEnd == &dest[10],
			"Value of destEnd after appending a too long string.");
}

void testRemaining(){
	wchar_t dest[11];
	size_t remaining;

	diag("Test calculation of remaining space.");

	wcscpy(dest, L"Str");
	ok(SUCCEEDED(StringCbCatExW(dest, 11 * sizeof(wchar_t),
					L"Safe", NULL, &remaining, 0)),
			"Test calculation of remaining space "
			"while concatenating short strings.");
	is_wstring(L"StrSafe", dest,
			"Result of concatenating short strings.");
	is_int(4 * sizeof(wchar_t), remaining,
			"Number of remaining characters "
			"after concatenating short strings.");

	ok(SUCCEEDED(StringCbCatExW(dest, 11 * sizeof(wchar_t),
					L"", NULL, &remaining, 0)),
			"Test calculation of remaining space "
			"while appending an empty string.");
	is_wstring(L"StrSafe", dest,
			"Result of appending an empty string.");
	is_int(4 * sizeof(wchar_t), remaining,
			"Number of remaining characters "
			"after appending an empty string.");

	wcscpy(dest, L"");
	ok(SUCCEEDED(StringCbCatExW(dest, 11 * sizeof(wchar_t),
					L"", NULL, &remaining, 0)),
			"Test calculation of remaining space "
			"while concatenating empty strings.");
	is_wstring(L"", dest,
			"Result of concatenating empty strings.");
	is_int(11 * sizeof(wchar_t), remaining,
			"Number of remaining characters "
			"after concatenating empty strings.");

	wcscpy(dest, L"TEST: ");
	ok(StringCbCatExW(dest, 11 * sizeof(wchar_t),
				L"too long string", NULL, &remaining, 0) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Test calculation of remaining space "
			"while appending a too long string.");
	is_wstring(L"TEST: too ", dest,
			"Result of appending a too long string.");
	is_int(1 * sizeof(wchar_t), remaining,
			"Number of remaining characters after appending "
			"a too long string.");
}

void testFlags(){
	wchar_t dest[11];
	wchar_t * wanted;

	diag("Test the STRSAFE_IGNORE_NULLS flag.");

	wcscpy(dest, L"test");
	ok(SUCCEEDED(StringCbCatExW(dest, 11 * sizeof(wchar_t),
					NULL, NULL, NULL,
					STRSAFE_IGNORE_NULLS)),
			"Test appending a NULL string.");
	is_wstring(L"test", dest,
			"Result of appending a NULL string.");

	diag("Test the STRSAFE_FILL_BEHIND_NULL flag.");

	ok(SUCCEEDED(StringCbCatExW(dest, 11 * sizeof(wchar_t),
					L"ing", NULL, NULL,
					STRSAFE_FILL_BEHIND_NULL | '@')),
			"Test filling with '@' behind null termination.");
	is_wstring(L"testing", dest,
			"Result of concatenating and filling behind null termination.");

	wanted = malloc(3 * sizeof(wchar_t));
	if(wanted == NULL){
		bail("Memory allocation failed.");
	}
	memset(wanted, '@', 3 * sizeof(wchar_t));

	ok(memcmp(&dest[8], wanted, 3 * sizeof(wchar_t)) == 0,
			"Correct data filled after null termination.");

	free(wanted);

	diag("Test the STRSAFE_FILL_ON_FAILURE flag.");

	wcscpy(dest, L"TEST: ");
	ok(FAILED(StringCbCatExW(dest, 11 * sizeof(wchar_t),
					L"too much data", NULL, NULL,
					STRSAFE_FILL_ON_FAILURE | '@')),
			"Test filling with '@' on failure.");

	wanted = malloc(10 * sizeof(wchar_t));
	if(wanted == NULL){
		bail("Memory allocation failed.");
	}
	memset(wanted, '@', 10 * sizeof(wchar_t));

	ok(memcmp(dest, wanted, 10 * sizeof(wchar_t)) == 0,
			"Result of filling with '@' on failure.");
	ok(dest[10] == L'\0',
			"Check null termination at end of filled buffer.");

	free(wanted);

	diag("Test the STRSAFE_NULL_ON_FAILURE flag.");

	wcscpy(dest, L"data");
	ok(FAILED(StringCbCatExW(dest, 11 * sizeof(wchar_t),
					L"Also too much", NULL, NULL,
					STRSAFE_NULL_ON_FAILURE)),
			"Test nulling string on failure.");
	is_wstring(L"", dest,
			"Result when nulling string on failure.");

	diag("Test the STRSAFE_NO_TRUNCATION flag.");

	wcscpy(dest, L"data");
	ok(FAILED(StringCbCatExW(dest, 11 * sizeof(wchar_t),
					L"Won't fit in dest", NULL, NULL,
					STRSAFE_NO_TRUNCATION)),
			"Test copying with truncating disabled.");
	is_wstring(L"data", dest,
			"Result after copying with truncating disabled.");
}

int main(void){
	wchar_t dest[11] = L"TEST";
	
	plan(38);

	ok(SUCCEEDED(StringCbCatExW(dest, 11 * sizeof(wchar_t),
					L"test", NULL, NULL, 0)),
			"Concatenate short strings without any extended functionality.");
	is_wstring(L"TESTtest", dest,
			"Result of concatenation of short strings.");

	testDestEnd();
	testRemaining();
	testFlags();

	return 0;
}
