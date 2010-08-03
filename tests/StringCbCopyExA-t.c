#include <strsafe.h>
#include "tap/basic.h"

void testDestEnd(){
    char dest[11];
    char * destEnd;

    diag("Test calculation of destEnd.");

    ok(SUCCEEDED(StringCbCopyExA(dest, 11, "Data", &destEnd, NULL, 0)),
            "Test calculation of destEnd "
            "while copying short string.");
    is_string("Data", dest,
            "Result of copying short string.");
    ok(destEnd == &dest[4],
            "Value of destEnd after copying short string.");

    ok(SUCCEEDED(StringCbCopyExA(dest, 11, "", &destEnd, NULL, 0)),
            "Test calculation of destEnd "
            "while copying empty string.");
    is_string("", dest,
            "Result of copying empty string.");
    ok(destEnd == &dest[0],
            "Value of destEnd after copying empty string.");

    ok(StringCbCopyExA(dest, 11, "longer string", &destEnd, NULL, 0) ==
            STRSAFE_E_INSUFFICIENT_BUFFER,
            "Test calculation of destEnd "
            "while copying a too long string.");
    is_string("longer str", dest,
            "Result of copying a too long string.");
    ok(destEnd == &dest[10],
            "Value of destEnd after copying a too long string.");
}

void testRemaining(){
    char dest[11];
    size_t remaining;

    diag("Test calculation of remaining space.");

    ok(SUCCEEDED(StringCbCopyExA(dest, 11, "STR", NULL, &remaining, 0)),
            "Test calculation of remaining space "
            "while copying short string.");
    is_string("STR", dest,
            "Result of copying short string.");
    is_int(8, remaining,
            "Number of remaining characters after copying short string.");

    ok(SUCCEEDED(StringCbCopyExA(dest, 11, "", NULL, &remaining, 0)),
            "Test calculation of remaining space "
            "while copying empty string.");
    is_string("", dest,
            "Result of copying empty string.");
    is_int(11, remaining,
            "Number of remaining characters after copying empty string.");

    ok(StringCbCopyExA(dest, 11, "too long string", NULL, &remaining, 0) ==
            STRSAFE_E_INSUFFICIENT_BUFFER,
            "Test calculation of remaining space "
            "while copying a too long string.");
    is_string("too long s", dest,
            "Result of copying a too long string.");
    is_int(1, remaining,
            "Number of remaining characters after copying "
            "a too long string.");
}

void testFlags(){
    char dest[11];

    diag("Test the STRSAFE_IGNORE_NULLS flag.");

    ok(SUCCEEDED(StringCbCopyExA(dest, 11, NULL, NULL, NULL,
                    STRSAFE_IGNORE_NULLS)),
            "Test copying a NULL string.");
    is_string("", dest,
            "Result of copying a NULL string.");

    diag("Test the STRSAFE_FILL_BEHIND_NULL flag.");

    ok(SUCCEEDED(StringCbCopyExA(dest, 11, "testing", NULL, NULL,
                    STRSAFE_FILL_BEHIND_NULL | '@')),
            "Test filling with '@' behind null termination.");
    is_string("testing", dest,
            "Result of copying and filling behind null termination.");
    if(memcmp(&dest[8], "@@@", 3)){
        diag("wanted: \"@@@\"");
        diag("  seen: \"%c%c%c\"", dest[8], dest[9], dest[10]);
    }
    ok(memcmp(&dest[8], "@@@", 3) == 0,
            "Correct data filled after null termination.");

    diag("Test the STRSAFE_FILL_ON_FAILURE flag.");

    ok(FAILED(StringCbCopyExA(dest, 11, "too much data", NULL, NULL,
                    STRSAFE_FILL_ON_FAILURE | '@')),
            "Test filling with '@' on failure.");
    is_string("@@@@@@@@@@", dest,
            "Result of filling with '@' on failure.");

    diag("Test the STRSAFE_NULL_ON_FAILURE flag.");

    ok(FAILED(StringCbCopyExA(dest, 11, "Also too much", NULL, NULL,
                    STRSAFE_NULL_ON_FAILURE)),
            "Test nulling string on failure.");
    is_string("", dest,
            "Result when nulling string on failure.");

    diag("Test the STRSAFE_NO_TRUNCATION flag.");

    ok(FAILED(StringCbCopyExA(dest, 11, "Won't fit in dest", NULL, NULL,
                    STRSAFE_NO_TRUNCATION)),
            "Test copying with truncating disabled.");
    is_string("", dest,
            "Result after copying with truncating disabled.");
}

int main(void){
    char dest[11];
    
    plan(31);

    ok(SUCCEEDED(StringCbCopyExA(dest, 11, "test", NULL, NULL, 0)),
            "Copy short string without any extended functionality.");
    is_string("test", dest,
            "Result of copying short string.");

    testDestEnd();
    testRemaining();
    testFlags();

    return 0;
}
