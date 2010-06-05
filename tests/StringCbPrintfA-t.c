#include "../src/strsafe.h"
#include "tap/basic.h"

int main(void){
	plan(9);

	char dest[11];

	ok(SUCCEEDED(StringCbPrintfA(dest, 11, "")),
			"Print empty string.");
	is_string("", dest,
			"Result of printing empty string.");

	ok(SUCCEEDED(StringCbPrintfA(dest, 11, "test")),
			"Print without format parameters.");
	is_string("test", dest,
			"Result of printing without format parameters.");

	ok(SUCCEEDED(StringCbPrintfA(dest, 11, "%d", 17)),
			"Print integer to string.");
	is_string("17", dest,
			"Result of printing integer.");

	ok(SUCCEEDED(StringCbPrintfA(dest, 11, "%%")),
			"Print percent sign to string.");
	is_string("%", dest,
			"Result of printing percent sign.");

	ok(StringCbPrintfA(dest, 0, "") ==
			STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if destination capacity is zero.");

	return 0;
}
