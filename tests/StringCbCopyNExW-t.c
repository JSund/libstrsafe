#include <stdlib.h>
#include <string.h>
#include <strsafe.h>
#include "tap/wide.h"

void testDestEnd(){
	wchar_t dest[11];
	wchar_t * destEnd;

	diag("Test calculation of destEnd.");

	ok(SUCCEEDED(StringCbCopyNExW(dest, 11 * sizeof(wchar_t),
					L"Data", 5 * sizeof(wchar_t), &destEnd, NULL, 0)),
			"Test calculation of destEnd "
			"while copying short string.");
	is_wstring(L"Data", dest,
			"Result of copying short string.");
	ok(destEnd == &dest[4],
			"Value of destEnd after copying short string.");

	ok(SUCCEEDED(StringCbCopyNExW(dest, 11 * sizeof(wchar_t),
					L"", 1 * sizeof(wchar_t), &destEnd, NULL, 0)),
			"Test calculation of destEnd "
			"while copying empty string.");
	is_wstring(L"", dest,
			"Result of copying empty string.");
	ok(destEnd == &dest[0],
			"Value of destEnd after copying empty string.");

	ok(StringCbCopyNExW(dest, 11 * sizeof(wchar_t),
				L"longer string", 14 * sizeof(wchar_t), &destEnd, NULL, 0) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Test calculation of destEnd "
			"while copying a too long string.");
	is_wstring(L"longer str", dest,
			"Result of copying a too long string.");
	ok(destEnd == &dest[10],
			"Value of destEnd after copying a too long string.");

	ok(SUCCEEDED(StringCbCopyNExW(dest, 11 * sizeof(wchar_t),
					L"Another long string", 7 * sizeof(wchar_t),
					&destEnd, NULL, 0)),
			"Test calculation of destEnd "
			"while copying part of a string.");
	is_wstring(L"Another", dest,
			"Result of copying part of a string.");
	ok(destEnd == &dest[7],
			"Value of destEnd after copying part of a string.");
}

void testRemaining(){
	wchar_t dest[11];
	size_t remaining;

	diag("Test calculation of remaining space.");

	ok(SUCCEEDED(StringCbCopyNExW(dest, 11 * sizeof(wchar_t),
					L"STR", 4 * sizeof(wchar_t), NULL, &remaining, 0)),
			"Test calculation of remaining space "
			"while copying short string.");
	is_wstring(L"STR", dest,
			"Result of copying short string.");
	is_int(8 * sizeof(wchar_t), remaining,
			"Number of remaining characters after copying short string.");

	ok(SUCCEEDED(StringCbCopyNExW(dest, 11 * sizeof(wchar_t),
					L"", 1 * sizeof(wchar_t), NULL, &remaining, 0)),
			"Test calculation of remaining space "
			"while copying empty string.");
	is_wstring(L"", dest,
			"Result of copying empty string.");
	is_int(11 * sizeof(wchar_t), remaining,
			"Number of remaining characters after copying empty string.");

	ok(StringCbCopyNExW(dest, 11 * sizeof(wchar_t),
				L"too long string", 16 * sizeof(wchar_t),
				NULL, &remaining, 0) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Test calculation of remaining space "
			"while copying a too long string.");
	is_wstring(L"too long s", dest,
			"Result of copying a too long string.");
	is_int(1 * sizeof(wchar_t), remaining,
			"Number of remaining characters after copying "
			"a too long string.");

	ok(SUCCEEDED(StringCbCopyNExW(dest, 11 * sizeof(wchar_t),
					L"Foo bar baz", 7 * sizeof(wchar_t),
					NULL, &remaining, 0)),
			"Test calculation of remaining space "
			"while copying part of a string.");
	is_wstring(L"Foo bar", dest,
			"Result of copying part of a string.");
	is_int(4 * sizeof(wchar_t), remaining,
			"Number of remaining characters after copying part of a string.");
}

void testFlags(){
	wchar_t dest[11];
	wchar_t * wanted;

	diag("Test the STRSAFE_IGNORE_NULLS flag.");

	ok(SUCCEEDED(StringCbCopyNExW(dest, 11 * sizeof(wchar_t),
					NULL, 0 * sizeof(wchar_t), NULL, NULL,
					STRSAFE_IGNORE_NULLS)),
			"Test copying a NULL string.");
	is_wstring(L"", dest,
			"Result of copying a NULL string.");

	diag("Test the STRSAFE_FILL_BEHIND_NULL flag.");

	ok(SUCCEEDED(StringCbCopyNExW(dest, 11 * sizeof(wchar_t),
					L"testing", 4 * sizeof(wchar_t), NULL, NULL,
					STRSAFE_FILL_BEHIND_NULL | '@')),
			"Test filling with '@' behind null termination.");
	is_wstring(L"test", dest,
			"Result of copying and filling behind null termination.");

	wanted = malloc(6 * sizeof(wchar_t));
	if(wanted == NULL){
		bail("Memory allocation failed.");
	}
	memset(wanted, '@', 6 * sizeof(wchar_t));

	ok(memcmp(&dest[5], wanted, 6) == 0,
			"Correct data filled after null termination.");

	free(wanted);

	diag("Test the STRSAFE_FILL_ON_FAILURE flag.");

	ok(FAILED(StringCbCopyNExW(dest, 11 * sizeof(wchar_t),
					L"too much data", 14 * sizeof(wchar_t), NULL, NULL,
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

	ok(FAILED(StringCbCopyNExW(dest, 11 * sizeof(wchar_t),
					L"Also too much", 14 * sizeof(wchar_t), NULL, NULL,
					STRSAFE_NULL_ON_FAILURE)),
			"Test nulling string on failure.");
	is_wstring(L"", dest,
			"Result when nulling string on failure.");

	diag("Test the STRSAFE_NO_TRUNCATION flag.");

	ok(FAILED(StringCbCopyNExW(dest, 11 * sizeof(wchar_t),
					L"Won't fit in dest", 18 * sizeof(wchar_t), NULL, NULL,
					STRSAFE_NO_TRUNCATION)),
			"Test copying with truncating disabled.");
	is_wstring(L"", dest,
			"Result after copying with truncating disabled.");
}

int main(void){
	wchar_t dest[11];
	
	plan(38);

	ok(SUCCEEDED(StringCbCopyNExW(dest, 11 * sizeof(wchar_t),
					L"test", 3 * sizeof(wchar_t), NULL, NULL, 0)),
			"Copy short string without any extended functionality.");
	is_wstring(L"tes", dest,
			"Result of copying short string.");

	testDestEnd();
	testRemaining();
	testFlags();

	return 0;
}
