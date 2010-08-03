#include <strsafe.h>
#include "tap/basic.h"

void testDestEnd(){
    char dest[11];
    char * destEnd;

    diag("Test calculation of destEnd.");

    ok(SUCCEEDED(StringCchPrintfExA(dest, 11, &destEnd, NULL, 0, "Data")),
            "Test calculation of destEnd "
            "while printing short string.");
    is_string("Data", dest,
            "Result of printing short string.");
    ok(destEnd == &dest[4],
            "Value of destEnd after printing short string.");

    ok(SUCCEEDED(StringCchPrintfExA(dest, 11, &destEnd, NULL, 0, "")),
            "Test calculation of destEnd "
            "while printing empty string.");
    is_string("", dest,
            "Result of printing empty string.");
    ok(destEnd == &dest[0],
            "Value of destEnd after printing empty string.");

    ok(StringCchPrintfExA(dest, 11, &destEnd, NULL, 0, "longer %s",
                "string") ==
            STRSAFE_E_INSUFFICIENT_BUFFER,
            "Test calculation of destEnd "
            "while printing a too long string.");
    is_string("longer str", dest,
            "Result of printing a too long string.");
    ok(destEnd == &dest[10],
            "Value of destEnd after printing a too long string.");
}

void testRemaining(){
    char dest[11];
    size_t remaining;

    diag("Test calculation of remaining space.");

    ok(SUCCEEDED(StringCchPrintfExA(dest, 11, NULL, &remaining, 0, "STR")),
            "Test calculation of remaining space "
            "while printing short string.");
    is_string("STR", dest,
            "Result of printing short string.");
    is_int(8, remaining,
            "Number of remaining characters after printing short string.");

    ok(SUCCEEDED(StringCchPrintfExA(dest, 11, NULL, &remaining, 0, "")),
            "Test calculation of remaining space "
            "while printing empty string.");
    is_string("", dest,
            "Result of printing empty string.");
    is_int(11, remaining,
            "Number of remaining characters after printing empty string.");

    ok(StringCchPrintfExA(dest, 11, NULL, &remaining, 0, "too long string")
            == STRSAFE_E_INSUFFICIENT_BUFFER,
            "Test calculation of remaining space "
            "while printing a too long string.");
    is_string("too long s", dest,
            "Result of printing a too long string.");
    is_int(1, remaining,
            "Number of remaining characters after printing "
            "a too long string.");
}

void testFlags(){
    char dest[11];

    diag("Test the STRSAFE_IGNORE_NULLS flag.");

    ok(SUCCEEDED(StringCchPrintfExA(dest, 11, NULL, NULL,
                    STRSAFE_IGNORE_NULLS, NULL)),
            "Test printing a NULL string.");
    is_string("", dest,
            "Result of printing a NULL string.");

    diag("Test the STRSAFE_FILL_BEHIND_NULL flag.");

    ok(SUCCEEDED(StringCchPrintfExA(dest, 11, NULL, NULL,
                    STRSAFE_FILL_BEHIND_NULL | '@', "testing")),
            "Test filling with '@' behind null termination.");
    is_string("testing", dest,
            "Result of printing and filling behind null termination.");
    if(memcmp(&dest[8], "@@@", 3)){
        diag("wanted: \"@@@\"");
        diag("  seen: \"%c%c%c\"", dest[8], dest[9], dest[10]);
    }
    ok(memcmp(&dest[8], "@@@", 3) == 0,
            "Correct data filled after null termination.");

    diag("Test the STRSAFE_FILL_ON_FAILURE flag.");

    ok(FAILED(StringCchPrintfExA(dest, 11, NULL, NULL,
                    STRSAFE_FILL_ON_FAILURE | '@', "too much data")),
            "Test filling with '@' on failure.");
    is_string("@@@@@@@@@@", dest,
            "Result of filling with '@' on failure.");

    diag("Test the STRSAFE_NULL_ON_FAILURE flag.");

    ok(FAILED(StringCchPrintfExA(dest, 11, NULL, NULL,
                    STRSAFE_NULL_ON_FAILURE, "Also too much")),
            "Test nulling string on failure.");
    is_string("", dest,
            "Result when nulling string on failure.");

    diag("Test the STRSAFE_NO_TRUNCATION flag.");

    ok(FAILED(StringCchPrintfExA(dest, 11, NULL, NULL,
                    STRSAFE_NO_TRUNCATION, "Won't fit in dest")),
            "Test printing with truncating disabled.");
    is_string("", dest,
            "Result after printing with truncating disabled.");
}

int main(void){
    char dest[11];
    
    plan(31);

    ok(SUCCEEDED(StringCchPrintfExA(dest, 11, NULL, NULL, 0, "test")),
            "Print short string without any extended functionality.");
    is_string("test", dest,
            "Result of printing short string.");

    testDestEnd();
    testRemaining();
    testFlags();

    return 0;
}
