#include <strsafe.h>
#include "tap/basic.h"

int main(void){
	char dest[11];
	char * destEnd;
	size_t remaining;
	
	plan(20);

	ok(SUCCEEDED(StringCchCopyExA(dest, 11, "test", NULL, NULL, 0)),
			"Copy short string without any extended functionality.");
	is_string("test", dest,
			"Result of copying short string.");

	/*
	 * Test calculation of destEnd.
	 */

	ok(SUCCEEDED(StringCchCopyExA(dest, 11, "Data", &destEnd, NULL, 0)),
			"Test calculation of destEnd "
			"while copying short string.");
	is_string("Data", dest,
			"Result of copying short string.");
	ok(destEnd == &dest[4],
			"Value of destEnd after copying short string.");

	ok(SUCCEEDED(StringCchCopyExA(dest, 11, "", &destEnd, NULL, 0)),
			"Test calculation of destEnd "
			"while copying empty string.");
	is_string("", dest,
			"Result of copying empty string.");
	ok(destEnd == &dest[0],
			"Value of destEnd after copying empty string.");

	ok(StringCchCopyExA(dest, 11, "longer string", &destEnd, NULL, 0) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Test calculation of destEnd "
			"while copying a string that is too long.");
	is_string("longer str", dest,
			"Result of copying a string that is too long.");
	ok(destEnd == &dest[10],
			"Value of destEnd after copying a string that is too long.");

	/*
	 * Test calculation of remaining space.
	 */

	ok(SUCCEEDED(StringCchCopyExA(dest, 11, "STR", NULL, &remaining, 0)),
			"Test calculation of remaining space "
			"while copying short string.");
	is_string("STR", dest,
			"Result of copying short string.");
	is_int(8, remaining,
			"Number of remaining characters after copying short string.");

	ok(SUCCEEDED(StringCchCopyExA(dest, 11, "", NULL, &remaining, 0)),
			"Test calculation of remaining space "
			"while copying empty string.");
	is_string("", dest,
			"Result of copying empty string.");
	is_int(11, remaining,
			"Number of remaining characters after copying empty string.");

	ok(StringCchCopyExA(dest, 11, "too long string", NULL, &remaining, 0) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Test calculation of remaining space "
			"while copying a string that is too long.");
	is_string("too long s", dest,
			"Result of copying a string that is too long.");
	is_int(1, remaining,
			"Number of remaining characters after copying "
			"a string that is too long.");

	/*
	 * Test the various flags.
	 *
	 * @TODO Write tests for all applicable flags.
	 */

	return 0;
}
