#include <strsafe.h>
#include "tap/basic.h"

int main(void){
	char dest[11] = "test";
	char dest2[11] = "TEST";
	char empty[10] = "";
	
	plan(16);

	ok(SUCCEEDED(StringCbCatNA(dest, 11, "test", 4)),
			"Concatenate entire strings.");
	is_string("testtest", dest,
			"Result of concatenating entire strings.");

	dest[4] = '\0'; /* Reset dest to "test". */

	ok(SUCCEEDED(StringCbCatNA(dest, 11, "", 1)),
			"Concatenate with empty source.");
	is_string("test", dest,
			"Result of concatenating with empty source.");

	ok(SUCCEEDED(StringCbCatNA(empty, 10, "test", 4)),
			"Concatenate with empty destination.");
	is_string("test", empty,
			"Result of concatenating with empty destination.");

	ok(SUCCEEDED(StringCbCatNA(dest2, 11, dest, 11)),
			"Concatenate two buffers with additional capacity.");
	is_string("TESTtest", dest2,
			"Result of concatenating buffers with additional capacity.");
	
	ok(StringCbCatNA(dest, 11, "longer string", 12) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Concatenate a string that is too long.");
	is_string("testlonger", dest,
			"Result of concatenating two strings that are too long.");

	ok(SUCCEEDED(StringCbCatNA(dest2, 11, dest, 2)),
			"Concatenate a few characters from a longer string.");
	is_string("TESTtestte", dest2,
			"Result of concatenating a few characters.");
	
	ok(StringCbCatNA(dest, 11, "test", 4) ==
			STRSAFE_E_INVALID_PARAMETER,
			"Concatenate to already full destination.");
	is_string("testlonger", dest,
			"Make sure destination was not modified.");

	ok(StringCbCatNA(dest, 0, "test", 4) ==
			STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if cchDest is zero.");
	is_string("testlonger", dest,
			"Make sure destination was not modified.");

	return 0;
}
