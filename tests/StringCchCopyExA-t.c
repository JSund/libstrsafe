#include <strsafe.h>
#include "tap/basic.h"

int main(void){
	char dest[11];
	char * destEnd;
	size_t remaining;
	
	plan(14);

	ok(SUCCEEDED(StringCchCopyExA(dest, 11, "test", NULL, NULL, 0)),
			"Copy short string without any extended functionality.");
	is_string("test", dest,
			"Result of copying short string.");

	ok(SUCCEEDED(StringCchCopyExA(dest, 11, "Data", &destEnd, NULL, 0)),
			"Test calculation of destEnd while copying short string.");
	is_string("Data", dest,
			"Result of copying short string.");
	ok(destEnd == &dest[4],
			"Value of destEnd after copying short string.");

	ok(SUCCEEDED(StringCchCopyExA(dest, 11, "STR", NULL, &remaining, 0)),
			"Test calculation of remaining space "
			"while copying short string.");
	is_string("STR", dest,
			"Result of copying short string.");
	is_int(8, remaining,
			"Number of remaining characters after copying short string.");

	ok(SUCCEEDED(StringCchCopyExA(dest, 11, "", &destEnd, NULL, 0)),
			"Test calculation of destEnd "
			"while copying empty string.");
	is_string("", dest,
			"Result of copying empty string.");
	ok(destEnd == &dest[0],
			"Value of destEnd after copying empty string.");

	/* Put data in dest. */
	StringCchCopyExA(dest, 11, "data", NULL, NULL, 0);
	
	ok(SUCCEEDED(StringCchCopyExA(dest, 11, "", NULL, &remaining, 0)),
			"Test calculation of remaining space "
			"while copying empty string.");
	is_string("", dest,
			"Result of copying empty string.");
	is_int(11, remaining,
			"Number of remaining characters after copying empty string.");

	return 0;
}
