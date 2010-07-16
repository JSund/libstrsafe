#include <strsafe.h>
#include "tap/basic.h"

int main(void){
	char dest[11];

	plan(11);

	ok(SUCCEEDED(StringCchPrintfA(dest, 11, "")),
			"Print empty string.");
	is_string("", dest,
			"Result of printing empty string.");

	ok(SUCCEEDED(StringCchPrintfA(dest, 11, "test")),
			"Print without format parameters.");
	is_string("test", dest,
			"Result of printing without format parameters.");

	ok(StringCchPrintfA(dest, 11, "longer string") ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Print too long string.");
	is_string("longer str", dest,
			"Result of printing a too long string.");

	ok(SUCCEEDED(StringCchPrintfA(dest, 11, "%d", 17)),
			"Print integer to string.");
	is_string("17", dest,
			"Result of printing integer.");

	ok(SUCCEEDED(StringCchPrintfA(dest, 11, "%%")),
			"Print percent sign to string.");
	is_string("%", dest,
			"Result of printing percent sign.");

	ok(StringCchPrintfA(dest, 0, "") ==
			STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if destination capacity is zero.");

	return 0;
}
