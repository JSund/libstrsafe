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

HRESULT StringCchCopyA(
        LPSTR pszDest,
        size_t cchDest,
        LPCSTR pszSrc){
    return StringCchCopyNA(pszDest, cchDest, pszSrc, cchDest);
}

HRESULT StringCchCopyW(
        LPWSTR pszDest,
        size_t cchDest,
        LPCWSTR pszSrc){
    return StringCchCopyNW(pszDest, cchDest, pszSrc, cchDest);
}

HRESULT StringCchCopyExA(
        LPSTR pszDest,
        size_t cchDest,
        LPCSTR pszSrc,
        LPSTR *ppszDestEnd,
        size_t * pcchRemaining,
        DWORD dwFlags){
    return StringCchCopyNExA(pszDest, cchDest, pszSrc, cchDest,
            ppszDestEnd, pcchRemaining, dwFlags);
}

HRESULT StringCchCopyExW(
        LPWSTR pszDest,
        size_t cchDest,
        LPCWSTR pszSrc,
        LPWSTR *ppszDestEnd,
        size_t * pcchRemaining,
        DWORD dwFlags){
    return StringCchCopyNExW(pszDest, cchDest, pszSrc, cchDest,
            ppszDestEnd, pcchRemaining, dwFlags);
}

HRESULT StringCbCopyA(
        LPSTR pszDest,
        size_t cbDest,
        LPCSTR pszSrc){
    return StringCbCopyNA(pszDest, cbDest, pszSrc, cbDest);
}

HRESULT StringCbCopyW(
        LPWSTR pszDest,
        size_t cbDest,
        LPCWSTR pszSrc){
    return StringCbCopyNW(pszDest, cbDest, pszSrc, cbDest);
}

HRESULT StringCbCopyExA(
        LPSTR pszDest,
        size_t cbDest,
        LPCSTR pszSrc,
        LPSTR *ppszDestEnd,
        size_t * pcbRemaining,
        DWORD dwFlags){
    return StringCbCopyNExA(pszDest, cbDest, pszSrc, cbDest,
            ppszDestEnd, pcbRemaining, dwFlags);
}

HRESULT StringCbCopyExW(
        LPWSTR pszDest,
        size_t cbDest,
        LPCWSTR pszSrc,
        LPWSTR * ppszDestEnd,
        size_t * pcbRemaining,
        DWORD dwFlags){
    return StringCbCopyNExW(pszDest, cbDest, pszSrc, cbDest,
            ppszDestEnd, pcbRemaining, dwFlags);
}
