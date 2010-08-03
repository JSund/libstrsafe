#include <strsafe.h>
#include <wchar.h>
#include "tap/basic.h"

int main(void){
    wchar_t dest[11] = L"test";
    wchar_t empty[10] = L"";

    plan(12);

    ok(SUCCEEDED(StringCchCatW(dest, 11, L"TEST")),
            "Concatenate two short strings.");
    is_wstring(L"testTEST", dest,
            "Result of concatenating short strings.");

    dest[4] = '\0'; /* Reset dest to "test". */

    ok(SUCCEEDED(StringCchCatW(dest, 11, L"")),
            "Concatenate with empty source.");
    is_wstring(L"test", dest,
            "Result of concatenating with empty source.");

    ok(SUCCEEDED(StringCchCatW(empty, 10, L"test")),
            "Concatenate with empty destination.");
    is_wstring(L"test", empty,
            "Result of concatenating with empty destination.");

    ok(StringCchCatW(dest, 11, L"longer string") ==
            STRSAFE_E_INSUFFICIENT_BUFFER,
            "Concatenate two strings that are too long.");
    is_wstring(L"testlonger", dest,
            "Result of concatenating two strings that are too long.");
    
    ok(StringCchCatW(dest, 11, L"test") ==
            STRSAFE_E_INSUFFICIENT_BUFFER,
            "Concatenate to already full destination.");
    is_wstring(L"testlonger", dest,
            "Make sure destination was not modified.");
    
    ok(StringCchCatW(dest, 0, L"test") ==
            STRSAFE_E_INVALID_PARAMETER,
            "Make sure error is thrown if cchDest is zero.");
    is_wstring(L"testlonger", dest,
            "Make sure destination was not modified.");

    return 0;
}
