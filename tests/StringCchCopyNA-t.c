#include <strsafe.h>
#include "tap/basic.h"

int main(void){
	char dest[11];
	char dest2[11];
	
	plan(7);

	ok(SUCCEEDED(StringCchCopyNA(dest, 11, "test", 4)),
			"Copy entire string.");
	is_string("test", dest,
			"Result of copying entire string.");

	ok(SUCCEEDED(StringCchCopyNA(dest2, 11, dest, 11)),
			"Copy from buffer with additional capacity.");
	is_string("test", dest2,
			"Result of copying from buffer with additional capacity.");
	
	ok(StringCchCopyNA(dest, 11, "longer string", 12) ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Copy a string that is too long.");
	is_string("longer str", dest,
			"Result of copying a string that is too long.");
	
	ok(StringCchCopyNA(dest, 0, "test", 4) == STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if cchDest is zero.");

	return 0;
}
