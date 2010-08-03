/*
 * Copyright (c) 2010, Jonas Sundberg <jsund@jsund.com>
 *
 * This software has been released under the terms of the ISC license. For
 * details, see the LICENSE file.
 */

#include "strsafe.h"
#include "../config.h"
#ifdef HAVE_STDIO_H
    #include <stdio.h>
#endif
#ifdef HAVE_STRING_H
    #include <string.h>
#endif
#ifdef HAVE_WCHAR_H
    #include <wchar.h>
#endif

HRESULT StringCchGetsA(
        LPSTR pszDest,
        size_t cchDest){
    return StringCchGetsExA(pszDest, cchDest, NULL, NULL, 0);
}

HRESULT StringCchGetsW(
        LPWSTR pszDest,
        size_t cchDest){
    return StringCchGetsExW(pszDest, cchDest, NULL, NULL, 0);
}

HRESULT StringCchGetsExA(
        LPSTR pszDest,
        size_t cchDest,
        LPSTR * ppszDestEnd,
        size_t * pcchRemaining,
        DWORD dwFlags){
    /* This function has a generic implementation in
     * strsafe_gets_generic.h. */
    #define STRSAFE_GENERIC_WIDE_CHAR 0
    #include "strsafe_gets_generic.h"
    #undef STRSAFE_GENERIC_WIDE_CHAR
}

HRESULT StringCchGetsExW(
        LPWSTR pszDest,
        size_t cchDest,
        LPWSTR * ppszDestEnd,
        size_t * pcchRemaining,
        DWORD dwFlags){
    /* This function has a generic implementation in
     * strsafe_gets_generic.h. */
    #define STRSAFE_GENERIC_WIDE_CHAR 1
    #include "strsafe_gets_generic.h"
    #undef STRSAFE_GENERIC_WIDE_CHAR
}

HRESULT StringCbGetsA(
        LPSTR pszDest,
        size_t cbDest){
    return StringCbGetsExA(pszDest, cbDest, NULL, NULL, 0);
}

HRESULT StringCbGetsW(
        LPWSTR pszDest,
        size_t cbDest){
    return StringCbGetsExW(pszDest, cbDest, NULL, NULL, 0);
}

HRESULT StringCbGetsExA(
        LPSTR pszDest,
        size_t cbDest,
        LPSTR * ppszDestEnd,
        size_t * pcbRemaining,
        DWORD dwFlags){
    return StringCchGetsExA(pszDest, cbDest,
            ppszDestEnd, pcbRemaining, dwFlags);
}

HRESULT StringCbGetsExW(
        LPWSTR pszDest,
        size_t cbDest,
        LPWSTR * ppszDestEnd,
        size_t * pcbRemaining,
        DWORD dwFlags){
    HRESULT result = StringCchGetsExW(pszDest, cbDest / sizeof(wchar_t),
            ppszDestEnd, pcbRemaining, dwFlags);
    if(pcbRemaining != NULL){
        *pcbRemaining *= sizeof(wchar_t);
    }
    return result;
}
