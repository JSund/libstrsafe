#include <strsafe.h>
#include "tap/basic.h"

void testDestEnd(){
    char dest[11];
    char * destEnd;

    diag("Test calculation of destEnd.");

    ok(SUCCEEDED(StringCbCopyNExA(dest, 11, "Data", 5, &destEnd, NULL, 0)),
            "Test calculation of destEnd "
            "while copying short string.");
    is_string("Data", dest,
            "Result of copying short string.");
    ok(destEnd == &dest[4],
            "Value of destEnd after copying short string.");

    ok(SUCCEEDED(StringCbCopyNExA(dest, 11, "", 1, &destEnd, NULL, 0)),
            "Test calculation of destEnd "
            "while copying empty string.");
    is_string("", dest,
            "Result of copying empty string.");
    ok(destEnd == &dest[0],
            "Value of destEnd after copying empty string.");

    ok(StringCbCopyNExA(dest, 11, "longer string", 14, &destEnd, NULL, 0) ==
            STRSAFE_E_INSUFFICIENT_BUFFER,
            "Test calculation of destEnd "
            "while copying a too long string.");
    is_string("longer str", dest,
            "Result of copying a too long string.");
    ok(destEnd == &dest[10],
            "Value of destEnd after copying a too long string.");

    ok(SUCCEEDED(StringCbCopyNExA(dest, 11, "Another long string", 7,
                    &destEnd, NULL, 0)),
            "Test calculation of destEnd "
            "while copying part of a string.");
    is_string("Another", dest,
            "Result of copying part of a string.");
    ok(destEnd == &dest[7],
            "Value of destEnd after copying part of a string.");
}

void testRemaining(){
    char dest[11];
    size_t remaining;

    diag("Test calculation of remaining space.");

    ok(SUCCEEDED(StringCbCopyNExA(dest, 11, "STR", 4, NULL, &remaining, 0)),
            "Test calculation of remaining space "
            "while copying short string.");
    is_string("STR", dest,
            "Result of copying short string.");
    is_int(8, remaining,
            "Number of remaining characters after copying short string.");

    ok(SUCCEEDED(StringCbCopyNExA(dest, 11, "", 1, NULL, &remaining, 0)),
            "Test calculation of remaining space "
            "while copying empty string.");
    is_string("", dest,
            "Result of copying empty string.");
    is_int(11, remaining,
            "Number of remaining characters after copying empty string.");

    ok(StringCbCopyNExA(dest, 11, "too long string", 16,
                NULL, &remaining, 0) ==
            STRSAFE_E_INSUFFICIENT_BUFFER,
            "Test calculation of remaining space "
            "while copying a too long string.");
    is_string("too long s", dest,
            "Result of copying a too long string.");
    is_int(1, remaining,
            "Number of remaining characters after copying "
            "a too long string.");

    ok(SUCCEEDED(StringCbCopyNExA(dest, 11, "Foo bar baz", 7,
                    NULL, &remaining, 0)),
            "Test calculation of remaining space "
            "while copying part of a string.");
    is_string("Foo bar", dest,
            "Result of copying part of a string.");
    is_int(4, remaining,
            "Number of remaining characters after copying part of a string.");
}

void testFlags(){
    char dest[11];

    diag("Test the STRSAFE_IGNORE_NULLS flag.");

    ok(SUCCEEDED(StringCbCopyNExA(dest, 11, NULL, 0, NULL, NULL,
                    STRSAFE_IGNORE_NULLS)),
            "Test copying a NULL string.");
    is_string("", dest,
            "Result of copying a NULL string.");

    diag("Test the STRSAFE_FILL_BEHIND_NULL flag.");

    ok(SUCCEEDED(StringCbCopyNExA(dest, 11, "testing", 4, NULL, NULL,
                    STRSAFE_FILL_BEHIND_NULL | '@')),
            "Test filling with '@' behind null termination.");
    is_string("test", dest,
            "Result of copying and filling behind null termination.");
    ok(memcmp(&dest[5], "@@@@@@", 6) == 0,
            "Correct data filled after null termination.");

    diag("Test the STRSAFE_FILL_ON_FAILURE flag.");

    ok(FAILED(StringCbCopyNExA(dest, 11, "too much data", 14, NULL, NULL,
                    STRSAFE_FILL_ON_FAILURE | '@')),
            "Test filling with '@' on failure.");
    is_string("@@@@@@@@@@", dest,
            "Result of filling with '@' on failure.");

    diag("Test the STRSAFE_NULL_ON_FAILURE flag.");

    ok(FAILED(StringCbCopyNExA(dest, 11, "Also too much", 14, NULL, NULL,
                    STRSAFE_NULL_ON_FAILURE)),
            "Test nulling string on failure.");
    is_string("", dest,
            "Result when nulling string on failure.");

    diag("Test the STRSAFE_NO_TRUNCATION flag.");

    ok(FAILED(StringCbCopyNExA(dest, 11, "Won't fit in dest", 18, NULL, NULL,
                    STRSAFE_NO_TRUNCATION)),
            "Test copying with truncating disabled.");
    is_string("", dest,
            "Result after copying with truncating disabled.");
}

int main(void){
    char dest[11];
    
    plan(37);

    ok(SUCCEEDED(StringCbCopyNExA(dest, 11, "test", 3, NULL, NULL, 0)),
            "Copy short string without any extended functionality.");
    is_string("tes", dest,
            "Result of copying short string.");

    testDestEnd();
    testRemaining();
    testFlags();

    return 0;
}
