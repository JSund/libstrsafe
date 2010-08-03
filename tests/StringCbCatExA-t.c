#include <string.h>
#define STRSAFE_NO_DEPRECATE
#include <strsafe.h>
#include "tap/basic.h"

void testDestEnd(){
    char dest[11];
    char * destEnd;

    diag("Test calculation of destEnd.");

    strcpy(dest, "foo");
    ok(SUCCEEDED(StringCbCatExA(dest, 11, "Data", &destEnd, NULL, 0)),
            "Test calculation of destEnd "
            "while concatenating short strings.");
    is_string("fooData", dest,
            "Result of concatenating short strings.");
    ok(destEnd == &dest[7],
            "Value of destEnd after concatenating short strings.");

    ok(SUCCEEDED(StringCbCatExA(dest, 11, "", &destEnd, NULL, 0)),
            "Test calculation of destEnd "
            "while appending an empty string.");
    is_string("fooData", dest,
            "Result of appending an empty string.");
    ok(destEnd == &dest[7],
            "Value of destEnd after appending an empty string.");

    strcpy(dest, "");
    ok(SUCCEEDED(StringCbCatExA(dest, 11, "", &destEnd, NULL, 0)),
            "Test calculation of destEnd "
            "while concatenating two empty strings.");
    is_string("", dest,
            "Result of concatenating two emlpty strings.");
    ok(destEnd == dest,
            "Value of destEnd after concatenating two empty strings.");

    strcpy(dest, "TEST: ");
    ok(StringCbCatExA(dest, 11, "longer string", &destEnd, NULL, 0) ==
            STRSAFE_E_INSUFFICIENT_BUFFER,
            "Test calculation of destEnd "
            "while appending a too long string.");
    is_string("TEST: long", dest,
            "Result of appending a too long string.");
    ok(destEnd == &dest[10],
            "Value of destEnd after appending a too long string.");
}

void testRemaining(){
    char dest[11];
    size_t remaining;

    diag("Test calculation of remaining space.");

    strcpy(dest, "Str");
    ok(SUCCEEDED(StringCbCatExA(dest, 11, "Safe", NULL, &remaining, 0)),
            "Test calculation of remaining space "
            "while concatenating short strings.");
    is_string("StrSafe", dest,
            "Result of concatenating short strings.");
    is_int(4, remaining,
            "Number of remaining characters "
            "after concatenating short strings.");

    ok(SUCCEEDED(StringCbCatExA(dest, 11, "", NULL, &remaining, 0)),
            "Test calculation of remaining space "
            "while appending an empty string.");
    is_string("StrSafe", dest,
            "Result of appending an empty string.");
    is_int(4, remaining,
            "Number of remaining characters "
            "after appending an empty string.");

    strcpy(dest, "");
    ok(SUCCEEDED(StringCbCatExA(dest, 11, "", NULL, &remaining, 0)),
            "Test calculation of remaining space "
            "while concatenating empty strings.");
    is_string("", dest,
            "Result of concatenating empty strings.");
    is_int(11, remaining,
            "Number of remaining characters "
            "after concatenating empty strings.");

    strcpy(dest, "TEST: ");
    ok(StringCbCatExA(dest, 11, "too long string", NULL, &remaining, 0) ==
            STRSAFE_E_INSUFFICIENT_BUFFER,
            "Test calculation of remaining space "
            "while appending a too long string.");
    is_string("TEST: too ", dest,
            "Result of appending a too long string.");
    is_int(1, remaining,
            "Number of remaining characters after appending "
            "a too long string.");
}

void testFlags(){
    char dest[11];

    diag("Test the STRSAFE_IGNORE_NULLS flag.");

    strcpy(dest, "test");
    ok(SUCCEEDED(StringCbCatExA(dest, 11, NULL, NULL, NULL,
                    STRSAFE_IGNORE_NULLS)),
            "Test appending a NULL string.");
    is_string("test", dest,
            "Result of appending a NULL string.");

    diag("Test the STRSAFE_FILL_BEHIND_NULL flag.");

    strcpy(dest, "test");
    ok(SUCCEEDED(StringCbCatExA(dest, 11, "ing", NULL, NULL,
                    STRSAFE_FILL_BEHIND_NULL | '@')),
            "Test filling with '@' behind null termination.");
    is_string("testing", dest,
            "Result of concatenating and filling behind null termination.");
    ok(memcmp(&dest[8], "@@@", 3) == 0,
            "Correct data filled after null termination.");

    diag("Test the STRSAFE_FILL_ON_FAILURE flag.");

    strcpy(dest, "TEST: ");
    ok(FAILED(StringCbCatExA(dest, 11, "too much data", NULL, NULL,
                    STRSAFE_FILL_ON_FAILURE | '@')),
            "Test filling with '@' on failure.");
    is_string("@@@@@@@@@@", dest,
            "Result of filling with '@' on failure.");

    diag("Test the STRSAFE_NULL_ON_FAILURE flag.");

    strcpy(dest, "data");
    ok(FAILED(StringCbCatExA(dest, 11, "Also too much", NULL, NULL,
                    STRSAFE_NULL_ON_FAILURE)),
            "Test nulling string on failure.");
    is_string("", dest,
            "Result when nulling string on failure.");

    diag("Test the STRSAFE_NO_TRUNCATION flag.");

    strcpy(dest, "data");
    ok(FAILED(StringCbCatExA(dest, 11, "Won't fit in dest", NULL, NULL,
                    STRSAFE_NO_TRUNCATION)),
            "Test copying with truncating disabled.");
    is_string("data", dest,
            "Result after copying with truncating disabled.");
}

int main(void){
    char dest[11] = "TEST";
    
    plan(37);

    ok(SUCCEEDED(StringCbCatExA(dest, 11, "test", NULL, NULL, 0)),
            "Concatenate short strings without any extended functionality.");
    is_string("TESTtest", dest,
            "Result of concatenation of short strings.");

    testDestEnd();
    testRemaining();
    testFlags();

    return 0;
}
