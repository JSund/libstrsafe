#include <stdlib.h>
#include <check.h>
#include <assert.h>
#include "../src/strsafe.h"
#include "tap/basic.h"

int main(void){
	plan(4);

	size_t length;
	ok(SUCCEEDED(StringCchLengthA("", 1, &length)), "Calculate length of empty string.");
	is_int(0, length, "Value for length of empty string.");
	ok(SUCCEEDED(StringCchLengthA("test\0test", 10, &length)), "Calculate length of string with embedded null character.");
	is_int(4, length, "Value for length of string with embedded null character.");

	return 0;
}
