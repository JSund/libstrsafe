#include <stdlib.h>
#include <check.h>
#include "tests/tap/basic.h"

int main(void){
	plan(1);
	size_t length;
	assert(SUCCESSFUL(StringCchLengthA("", 1, &length)));
	is_int(0, length, "Length of empty string.");

	return 0;
}
