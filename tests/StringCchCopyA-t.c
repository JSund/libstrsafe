#include "../src/strsafe.h"
#include "tap/basic.h"

int main(void){
	plan(7);

	char dest[11];
	
	ok(SUCCEEDED(StringCchCopyA(dest, 11, "test")),
			"Copy short string.");
	is_string("test", dest,
			"Result of copying short string.");

	ok(SUCCEEDED(StringCchCopyA(dest, 11, "")),
			"Copy empty string.");
	is_string("", dest,
			"Result of copying empty string.");
	
	ok(StringCchCopyA(dest, 11, "longer string") ==
			STRSAFE_E_INSUFFICIENT_BUFFER,
			"Copy a string that is too long.");
	is_string("longer str", dest,
			"Result of copying a string that is too long.");

	ok(StringCchCopyA(dest, 0, "test") ==
			STRSAFE_E_INVALID_PARAMETER,
			"Make sure error is thrown if cchDest is zero.");

	return 0;
}
