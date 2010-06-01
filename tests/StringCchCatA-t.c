#include "../src/strsafe.h"
#include "tap/basic.h"

int main(void){
	plan(12);

	char dest[11] = "test";
	char empty[10] = "";

	ok(SUCCEEDED(StringCchCatA(dest, 11, "TEST")),
			"Concatenate two short strings.");
	is_string("testTEST", dest,
			"Result of concatenating short strings.");

	dest[4] = '\0'; /* Reset dest to "test". */

	ok(SUCCEEDED(StringCchCatA(dest, 11, "")),
			"Concatenate with empty source.");
	is_string("test", dest,
			"Result of concatenating with empty source.");

	ok(SUCCEEDED(StringCchCatA(empty, 10, "test")),
			"Concatenate with empty destination.");
	is_string("test", empty,
			"Result of concatenating with empty destination.");

	ok(StringCchCatA(dest, 11, "longer string") ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Concatenate two strings that are too long.");
	is_string("testlonger", dest,
			"Result of concatenating two strings that are too long.");
	
	ok(StringCchCatA(dest, 11, "test") == STRSAFE_E_INVALID_PARAMETER,
			"Concatenate to already full destination.");
	is_string("testlonger", dest,
			"Make sure destination was not modified.");
	
	ok(StringCchCatA(dest, 0, "test") == STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if cchDest is zero.");
	is_string("testlonger", dest,
			"Make sure destination was not modified.");

	return 0;
}
