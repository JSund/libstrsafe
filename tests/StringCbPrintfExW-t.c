#include <stdlib.h>
#include <string.h>
#include <strsafe.h>
#include "tap/wide.h"

void testDestEnd(){
	wchar_t dest[11];
	wchar_t * destEnd;

	diag("Test calculation of destEnd.");

	ok(SUCCEEDED(StringCbPrintfExW(dest, 11 * sizeof(wchar_t),
					&destEnd, NULL, 0, L"Data")),
			"Test calculation of destEnd "
			"while printing short string.");
	is_wstring(L"Data", dest,
			"Result of printing short string.");
	ok(destEnd == &dest[4],
			"Value of destEnd after printing short string.");

	ok(SUCCEEDED(StringCbPrintfExW(dest, 11 * sizeof(wchar_t),
					&destEnd, NULL, 0, L"")),
			"Test calculation of destEnd "
			"while printing empty string.");
	is_wstring(L"", dest,
			"Result of printing empty string.");
	ok(destEnd == &dest[0],
			"Value of destEnd after printing empty string.");

	ok(StringCbPrintfExW(dest, 11 * sizeof(wchar_t), &destEnd,
				NULL, 0, L"longer %ls", L"string") ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Test calculation of destEnd "
			"while printing a too long string.");
	is_wstring(L"longer str", dest,
			"Result of printing a too long string.");
	ok(destEnd == &dest[10],
			"Value of destEnd after printing a too long string.");
}

void testRemaining(){
	wchar_t dest[11];
	size_t remaining;

	diag("Test calculation of remaining space.");

	ok(SUCCEEDED(StringCbPrintfExW(dest, 11 * sizeof(wchar_t),
					NULL, &remaining, 0, L"STR")),
			"Test calculation of remaining space "
			"while printing short string.");
	is_wstring(L"STR", dest,
			"Result of printing short string.");
	is_int(8 * sizeof(wchar_t), remaining,
			"Number of remaining characters after printing short string.");

	ok(SUCCEEDED(StringCbPrintfExW(dest, 11 * sizeof(wchar_t),
					NULL, &remaining, 0, L"")),
			"Test calculation of remaining space "
			"while printing empty string.");
	is_wstring(L"", dest,
			"Result of printing empty string.");
	is_int(11 * sizeof(wchar_t), remaining,
			"Number of remaining characters after printing empty string.");

	ok(StringCbPrintfExW(dest, 11 * sizeof(wchar_t),
				NULL, &remaining, 0, L"too long string") ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Test calculation of remaining space "
			"while printing a too long string.");
	is_wstring(L"too long s", dest,
			"Result of printing a too long string.");
	is_int(1 * sizeof(wchar_t), remaining,
			"Number of remaining characters after printing "
			"a too long string.");
}

void testFlags(){
	wchar_t dest[11];
	wchar_t * wanted;

	diag("Test the STRSAFE_IGNORE_NULLS flag.");

	ok(SUCCEEDED(StringCbPrintfExW(dest, 11 * sizeof(wchar_t),
					NULL, NULL, STRSAFE_IGNORE_NULLS, NULL)),
			"Test printing a NULL string.");
	is_wstring(L"", dest,
			"Result of printing a NULL string.");

	diag("Test the STRSAFE_FILL_BEHIND_NULL flag.");

	ok(SUCCEEDED(StringCbPrintfExW(dest, 11 * sizeof(wchar_t),
					NULL, NULL, STRSAFE_FILL_BEHIND_NULL | '@',
					L"testing")),
			"Test filling with '@' behind null termination.");
	is_wstring(L"testing", dest,
			"Result of printing and filling behind null termination.");

	wanted = malloc(3 * sizeof(wchar_t));
	if(wanted == NULL){
		bail("Memory allocation failed.");
	}
	memset(wanted, '@', 3 * sizeof(wchar_t));

	ok(memcmp(&dest[8], wanted, 3 * sizeof(wchar_t)) == 0,
			"Correct data filled after null termination.");

	free(wanted);

	diag("Test the STRSAFE_FILL_ON_FAILURE flag.");

	ok(FAILED(StringCbPrintfExW(dest, 11 * sizeof(wchar_t), NULL, NULL,
					STRSAFE_FILL_ON_FAILURE | '@', L"too much data")),
			"Test filling with '@' on failure.");

	wanted = malloc(11 * sizeof(wchar_t));
	if(wanted == NULL){
		bail("Memory allocation failed.");
	}
	memset(wanted, '@', 10 * sizeof(wchar_t));
	wanted[10] = L'\0';

	ok(memcmp(dest, wanted, 11 * sizeof(wchar_t)) == 0,
			"Result of filling with '@' on failure.");

	free(wanted);

	diag("Test the STRSAFE_NULL_ON_FAILURE flag.");

	ok(FAILED(StringCbPrintfExW(dest, 11 * sizeof(wchar_t), NULL, NULL,
					STRSAFE_NULL_ON_FAILURE, L"Also too much")),
			"Test nulling string on failure.");
	is_wstring(L"", dest,
			"Result when nulling string on failure.");

	diag("Test the STRSAFE_NO_TRUNCATION flag.");

	ok(FAILED(StringCbPrintfExW(dest, 11 * sizeof(wchar_t), NULL, NULL,
					STRSAFE_NO_TRUNCATION, L"Won't fit in dest")),
			"Test printing with truncating disabled.");
	is_wstring(L"", dest,
			"Result after printing with truncating disabled.");
}

int main(void){
	wchar_t dest[11];
	
	plan(31);

	ok(SUCCEEDED(StringCbPrintfExW(dest, 11 * sizeof(wchar_t),
					NULL, NULL, 0, L"test")),
			"Print short string without any extended functionality.");
	is_wstring(L"test", dest,
			"Result of printing short string.");

	testDestEnd();
	testRemaining();
	testFlags();

	return 0;
}
