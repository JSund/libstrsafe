#include <strsafe.h>
#include <wchar.h>
#include "tap/basic.h"

int main(void){
    size_t length;

    plan(7);

    ok(SUCCEEDED(StringCbLengthW(L"", 1 * sizeof(wchar_t), &length)),
            "Calculate length of empty string.");
    is_int(0 * sizeof(wchar_t), length,
            "Value for length of empty string.");

    ok(SUCCEEDED(StringCbLengthW(L"test", 5 * sizeof(wchar_t), &length)),
            "Calculate length of short string.");
    is_int(4 * sizeof(wchar_t), length,
            "Value for length of short string.");
    
    ok(SUCCEEDED(StringCbLengthW(L"test\0test", 10 * sizeof(wchar_t), &length)),
            "Calculate length of string with embedded null character.");
    is_int(4 * sizeof(wchar_t), length,
            "Value for length of string with embedded null character.");
    
    ok(StringCbLengthW(L"too long", 8 * sizeof(wchar_t), &length) ==
            STRSAFE_E_INVALID_PARAMETER,
            "Make sure error is thrown if null termination is not found.");

    return 0;
}
