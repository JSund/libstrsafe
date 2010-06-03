#include "../src/strsafe.h"
#include "tap/basic.h"

int main(void){
	plan(9);

	char dest[11];
	char dest2[11];
	
	ok(SUCCEEDED(StringCbCopyNA(dest, 11, "test", 4)),
			"Copy entire string.");
	is_string("test", dest,
			"Result of copying entire string.");

	ok(SUCCEEDED(StringCbCopyNA(dest2, 11, dest, 11)),
			"Copy from buffer with additional capacity.");
	is_string("test", dest2,
			"Result of copying from buffer with additional capacity.");

	ok(SUCCEEDED(StringCbCopyNA(dest, 11, "", 1)),
			"Copy empty string.");
	is_string("", dest,
			"Result of copying empty string.");
	
	ok(StringCbCopyNA(dest, 11, "longer string", 12) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Copy a string that is too long.");
	is_string("longer str", dest,
			"Result of copying a string that is too long.");
	
	ok(StringCbCopyNA(dest, 0, "test", 4) ==
			STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if cchDest is zero.");

	return 0;
}
