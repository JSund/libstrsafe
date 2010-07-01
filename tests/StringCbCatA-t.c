#include <strsafe.h>
#include "tap/basic.h"

int main(void){
	char dest[11] = "test";
	char empty[10] = "";

	plan(12);

	ok(SUCCEEDED(StringCbCatA(dest, 11, "TEST")),
			"Concatenate two short strings.");
	is_string("testTEST", dest,
			"Result of concatenating short strings.");

	dest[4] = '\0'; /* Reset dest to "test". */

	ok(SUCCEEDED(StringCbCatA(dest, 11, "")),
			"Concatenate with empty source.");
	is_string("test", dest,
			"Result of concatenating with empty source.");

	ok(SUCCEEDED(StringCbCatA(empty, 10, "test")),
			"Concatenate with empty destination.");
	is_string("test", empty,
			"Result of concatenating with empty destination.");

	ok(StringCbCatA(dest, 11, "longer string") ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Concatenate two strings that are too long.");
	is_string("testlonger", dest,
			"Result of concatenating two strings that are too long.");
	
	ok(StringCbCatA(dest, 11, "test") ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Concatenate to already full destination.");
	is_string("testlonger", dest,
			"Make sure destination was not modified.");
	
	ok(StringCbCatA(dest, 0, "test") ==
			STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if cchDest is zero.");
	is_string("testlonger", dest,
			"Make sure destination was not modified.");

	return 0;
}
