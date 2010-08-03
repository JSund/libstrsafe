#include <stdlib.h>
#include <string.h>
#define STRSAFE_NO_DEPRECATE
#include <strsafe.h>
#include "tap/wide.h"

void testDestEnd(){
    wchar_t dest[11];
    wchar_t * destEnd;

    diag("Test calculation of destEnd.");

    wcscpy(dest, L"foo");
    ok(SUCCEEDED(StringCchCatNExW(dest, 11, L"Data", 5, &destEnd, NULL, 0)),
            "Test calculation of destEnd "
            "while concatenating short strings.");
    is_wstring(L"fooData", dest,
            "Result of concatenating short strings.");
    ok(destEnd == &dest[7],
            "Value of destEnd after concatenating short strings.");

    ok(SUCCEEDED(StringCchCatNExW(dest, 11, L"", 1, &destEnd, NULL, 0)),
            "Test calculation of destEnd "
            "while appending an empty string.");
    is_wstring(L"fooData", dest,
            "Result of appending an empty string.");
    ok(destEnd == &dest[7],
            "Value of destEnd after appending an empty string.");

    wcscpy(dest, L"");
    ok(SUCCEEDED(StringCchCatNExW(dest, 11, L"", 1, &destEnd, NULL, 0)),
            "Test calculation of destEnd "
            "while concatenating two empty strings.");
    is_wstring(L"", dest,
            "Result of concatenating two emlpty strings.");
    ok(destEnd == dest,
            "Value of destEnd after concatenating two empty strings.");

    wcscpy(dest, L"TEST: ");
    ok(StringCchCatNExW(dest, 11, L"longer string", 14, &destEnd, NULL, 0) ==
            STRSAFE_E_INSUFFICIENT_BUFFER,
            "Test calculation of destEnd "
            "while appending a too long string.");
    is_wstring(L"TEST: long", dest,
            "Result of appending a too long string.");
    ok(destEnd == &dest[10],
            "Value of destEnd after appending a too long string.");

    wcscpy(dest, L"Test: ");
    ok(SUCCEEDED(StringCchCatNExW(dest, 11, L"okay", 2, &destEnd, NULL, 0)),
            "Test calculation of destEnd "
            "while appending part of a string.");
    is_wstring(L"Test: ok", dest,
            "Result of appending part of a string.");
    ok(destEnd == &dest[8],
            "Value of destEnd after appending part of a string.");
}

void testRemaining(){
    wchar_t dest[11];
    size_t remaining;

    diag("Test calculation of remaining space.");

    wcscpy(dest, L"Str");
    ok(SUCCEEDED(StringCchCatNExW(dest, 11, L"Safe", 5, NULL, &remaining, 0)),
            "Test calculation of remaining space "
            "while concatenating short strings.");
    is_wstring(L"StrSafe", dest,
            "Result of concatenating short strings.");
    is_int(4, remaining,
            "Number of remaining characters "
            "after concatenating short strings.");

    ok(SUCCEEDED(StringCchCatNExW(dest, 11, L"", 1, NULL, &remaining, 0)),
            "Test calculation of remaining space "
            "while appending an empty string.");
    is_wstring(L"StrSafe", dest,
            "Result of appending an empty string.");
    is_int(4, remaining,
            "Number of remaining characters "
            "after appending an empty string.");

    wcscpy(dest, L"");
    ok(SUCCEEDED(StringCchCatNExW(dest, 11, L"", 1, NULL, &remaining, 0)),
            "Test calculation of remaining space "
            "while concatenating empty strings.");
    is_wstring(L"", dest,
            "Result of concatenating empty strings.");
    is_int(11, remaining,
            "Number of remaining characters "
            "after concatenating empty strings.");

    wcscpy(dest, L"TEST: ");
    ok(StringCchCatNExW(dest, 11, L"too long string", 16,
                NULL, &remaining, 0) ==
            STRSAFE_E_INSUFFICIENT_BUFFER,
            "Test calculation of remaining space "
            "while appending a too long string.");
    is_wstring(L"TEST: too ", dest,
            "Result of appending a too long string.");
    is_int(1, remaining,
            "Number of remaining characters after appending "
            "a too long string.");

    wcscpy(dest, L"Foo ");
    ok(SUCCEEDED(StringCchCatNExW(dest, 11, L"bar baz", 3,
                    NULL, &remaining, 0)),
            "Test calculation of remaining space "
            "while appending part of a string.");
    is_wstring(L"Foo bar", dest,
            "Result of appending part of a string.");
    is_int(4, remaining,
            "Number of remaining characters after appending part of a string.");
}

void testFlags(){
    wchar_t dest[11];
    wchar_t * wanted;

    diag("Test the STRSAFE_IGNORE_NULLS flag.");

    wcscpy(dest, L"test");
    ok(SUCCEEDED(StringCchCatNExW(dest, 11, NULL, 10, NULL, NULL,
                    STRSAFE_IGNORE_NULLS)),
            "Test appending a NULL string.");
    is_wstring(L"test", dest,
            "Result of appending a NULL string.");

    diag("Test the STRSAFE_FILL_BEHIND_NULL flag.");

    wcscpy(dest, L"test");
    ok(SUCCEEDED(StringCchCatNExW(dest, 11, L"ingenious", 3, NULL, NULL,
                    STRSAFE_FILL_BEHIND_NULL | '@')),
            "Test filling with '@' behind null termination.");
    is_wstring(L"testing", dest,
            "Result of concatenating and filling behind null termination.");

    wanted = malloc(3 * sizeof(wchar_t));
    if(wanted == NULL){
        bail("Memory allocation failed.");
    }
    memset(wanted, '@', 3 * sizeof(wchar_t));

    ok(memcmp(&dest[8], wanted, 3 * sizeof(wchar_t)) == 0,
            "Correct data filled after null termination.");

    free(wanted);

    diag("Test the STRSAFE_FILL_ON_FAILURE flag.");

    wcscpy(dest, L"TEST: ");
    ok(FAILED(StringCchCatNExW(dest, 11, L"too much data", 14, NULL, NULL,
                    STRSAFE_FILL_ON_FAILURE | '@')),
            "Test filling with '@' on failure.");

    wanted = malloc(10 * sizeof(wchar_t));
    if(wanted == NULL){
        bail("Memory allocation failed.");
    }
    memset(wanted, '@', 10 * sizeof(wchar_t));

    ok(memcmp(wanted, dest, 10 * sizeof(wchar_t)) == 0,
            "Result of filling with '@' on failure.");
    ok(dest[10] == L'\0',
            "Correct null termination at end of filled buffer.");

    free(wanted);

    diag("Test the STRSAFE_NULL_ON_FAILURE flag.");

    wcscpy(dest, L"data");
    ok(FAILED(StringCchCatNExW(dest, 11, L"Also too much", 14, NULL, NULL,
                    STRSAFE_NULL_ON_FAILURE)),
            "Test nulling string on failure.");
    is_wstring(L"", dest,
            "Result when nulling string on failure.");

    diag("Test the STRSAFE_NO_TRUNCATION flag.");

    wcscpy(dest, L"data");
    ok(FAILED(StringCchCatNExW(dest, 11, L"Won't fit in dest", 18, NULL, NULL,
                    STRSAFE_NO_TRUNCATION)),
            "Test copying with truncating disabled.");
    is_wstring(L"data", dest,
            "Result after copying with truncating disabled.");
}

int main(void){
    wchar_t dest[11] = L"TEST";
    
    plan(44);

    ok(SUCCEEDED(StringCchCatNExW(dest, 11, L"testing", 4, NULL, NULL, 0)),
            "Concatenate short strings without any extended functionality.");
    is_wstring(L"TESTtest", dest,
            "Result of concatenation of short strings.");

    testDestEnd();
    testRemaining();
    testFlags();

    return 0;
}
