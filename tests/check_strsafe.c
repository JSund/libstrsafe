#include <stdlib.h>
#include <check.h>
#include "../src/strsafe.h"

/*
 * Simple test to test the Check framework.
 * More tests will be added later.
 */
START_TEST(test_strsafe){
	char * empty = "";
	char dest[20];
	fail_unless(SUCCEEDED(StringCchCopy(dest, 20, empty)));
	fail_if(strcmp(dest, ""));
}END_TEST

Suite * strsafe_suite(void){
	Suite * s = suite_create("StrSafe");

	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_strsafe);
	suite_add_tcase(s, tc_core);

	return s;
}

int main(void){
	int tests_failed;
	Suite * s = strsafe_suite();
	SRunner * sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	tests_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (tests_failed ? EXIT_FAILURE : EXIT_SUCCESS);
}
