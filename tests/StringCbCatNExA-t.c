#include <string.h>
#define STRSAFE_NO_DEPRECATE
#include <strsafe.h>
#include "tap/basic.h"

void testDestEnd(){
	char dest[11];
	char * destEnd;

	diag("Test calculation of destEnd.");

	strcpy(dest, "foo");
	ok(SUCCEEDED(StringCbCatNExA(dest, 11, "Data", 5, &destEnd, NULL, 0)),
			"Test calculation of destEnd "
			"while concatenating short strings.");
	is_string("fooData", dest,
			"Result of concatenating short strings.");
	ok(destEnd == &dest[7],
			"Value of destEnd after concatenating short strings.");

	ok(SUCCEEDED(StringCbCatNExA(dest, 11, "", 1, &destEnd, NULL, 0)),
			"Test calculation of destEnd "
			"while appending an empty string.");
	is_string("fooData", dest,
			"Result of appending an empty string.");
	ok(destEnd == &dest[7],
			"Value of destEnd after appending an empty string.");

	strcpy(dest, "");
	ok(SUCCEEDED(StringCbCatNExA(dest, 11, "", 1, &destEnd, NULL, 0)),
			"Test calculation of destEnd "
			"while concatenating two empty strings.");
	is_string("", dest,
			"Result of concatenating two emlpty strings.");
	ok(destEnd == dest,
			"Value of destEnd after concatenating two empty strings.");

	strcpy(dest, "TEST: ");
	ok(StringCbCatNExA(dest, 11, "longer string", 14, &destEnd, NULL, 0) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Test calculation of destEnd "
			"while appending a too long string.");
	is_string("TEST: long", dest,
			"Result of appending a too long string.");
	ok(destEnd == &dest[10],
			"Value of destEnd after appending a too long string.");

	strcpy(dest, "Test: ");
	ok(SUCCEEDED(StringCbCatNExA(dest, 11, "okay", 2, &destEnd, NULL, 0)),
			"Test calculation of destEnd "
			"while appending part of a string.");
	is_string("Test: ok", dest,
			"Result of appending part of a string.");
	ok(destEnd == &dest[8],
			"Value of destEnd after appending part of a string.");
}

void testRemaining(){
	char dest[11];
	size_t remaining;

	diag("Test calculation of remaining space.");

	strcpy(dest, "Str");
	ok(SUCCEEDED(StringCbCatNExA(dest, 11, "Safe", 5, NULL, &remaining, 0)),
			"Test calculation of remaining space "
			"while concatenating short strings.");
	is_string("StrSafe", dest,
			"Result of concatenating short strings.");
	is_int(4, remaining,
			"Number of remaining characters "
			"after concatenating short strings.");

	ok(SUCCEEDED(StringCbCatNExA(dest, 11, "", 1, NULL, &remaining, 0)),
			"Test calculation of remaining space "
			"while appending an empty string.");
	is_string("StrSafe", dest,
			"Result of appending an empty string.");
	is_int(4, remaining,
			"Number of remaining characters "
			"after appending an empty string.");

	strcpy(dest, "");
	ok(SUCCEEDED(StringCbCatNExA(dest, 11, "", 1, NULL, &remaining, 0)),
			"Test calculation of remaining space "
			"while concatenating empty strings.");
	is_string("", dest,
			"Result of concatenating empty strings.");
	is_int(11, remaining,
			"Number of remaining characters "
			"after concatenating empty strings.");

	strcpy(dest, "TEST: ");
	ok(StringCbCatNExA(dest, 11, "too long string", 16, NULL, &remaining, 0) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Test calculation of remaining space "
			"while appending a too long string.");
	is_string("TEST: too ", dest,
			"Result of appending a too long string.");
	is_int(1, remaining,
			"Number of remaining characters after appending "
			"a too long string.");

	strcpy(dest, "Foo ");
	ok(SUCCEEDED(StringCbCatNExA(dest, 11, "bar baz", 3,
					NULL, &remaining, 0)),
			"Test calculation of remaining space "
			"while appending part of a string.");
	is_string("Foo bar", dest,
			"Result of appending part of a string.");
	is_int(4, remaining,
			"Number of remaining characters after appending part of a string.");
}

void testFlags(){
	char dest[11];

	diag("Test the STRSAFE_IGNORE_NULLS flag.");

	strcpy(dest, "test");
	ok(SUCCEEDED(StringCbCatNExA(dest, 11, NULL, 10, NULL, NULL,
					STRSAFE_IGNORE_NULLS)),
			"Test appending a NULL string.");
	is_string("test", dest,
			"Result of appending a NULL string.");

	diag("Test the STRSAFE_FILL_BEHIND_NULL flag.");

	strcpy(dest, "test");
	ok(SUCCEEDED(StringCbCatNExA(dest, 11, "ingenious", 3, NULL, NULL,
					STRSAFE_FILL_BEHIND_NULL | '@')),
			"Test filling with '@' behind null termination.");
	is_string("testing", dest,
			"Result of concatenating and filling behind null termination.");
	ok(memcmp(&dest[8], "@@@", 3) == 0,
			"Correct data filled after null termination.");

	diag("Test the STRSAFE_FILL_ON_FAILURE flag.");

	strcpy(dest, "TEST: ");
	ok(FAILED(StringCbCatNExA(dest, 11, "too much data", 14, NULL, NULL,
					STRSAFE_FILL_ON_FAILURE | '@')),
			"Test filling with '@' on failure.");
	is_string("@@@@@@@@@@", dest,
			"Result of filling with '@' on failure.");

	diag("Test the STRSAFE_NULL_ON_FAILURE flag.");

	strcpy(dest, "data");
	ok(FAILED(StringCbCatNExA(dest, 11, "Also too much", 14, NULL, NULL,
					STRSAFE_NULL_ON_FAILURE)),
			"Test nulling string on failure.");
	is_string("", dest,
			"Result when nulling string on failure.");

	diag("Test the STRSAFE_NO_TRUNCATION flag.");

	strcpy(dest, "data");
	ok(FAILED(StringCbCatNExA(dest, 11, "Won't fit in dest", 18, NULL, NULL,
					STRSAFE_NO_TRUNCATION)),
			"Test copying with truncating disabled.");
	is_string("data", dest,
			"Result after copying with truncating disabled.");
}

int main(void){
	char dest[11] = "TEST";
	
	plan(43);

	ok(SUCCEEDED(StringCbCatNExA(dest, 11, "testing", 4, NULL, NULL, 0)),
			"Concatenate short strings without any extended functionality.");
	is_string("TESTtest", dest,
			"Result of concatenation of short strings.");

	testDestEnd();
	testRemaining();
	testFlags();

	return 0;
}
