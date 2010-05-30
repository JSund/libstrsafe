#include "../src/strsafe.h"
#include "tap/basic.h"

int main(void){
	plan(8);

	char dest[11] = "test";
	ok(SUCCEEDED(StringCchCatA(dest, 11, "test")),
			"Concatenate two short strings.");
	is_string("testtest", dest,
			"Result of concatenating short strings.");

	dest[4] = '\0'; /* Reset dest to "test". */
	
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
