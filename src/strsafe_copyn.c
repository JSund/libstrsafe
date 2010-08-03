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
HRESULT StringCchCopyNA(
        LPSTR pszDest,
        size_t cchDest,
        LPCSTR pszSrc,
        size_t cchSrc){
    return StringCchCopyNExA(pszDest, cchDest, pszSrc, cchSrc,
            NULL, NULL, 0);
}

HRESULT StringCchCopyNW(
        LPWSTR pszDest,
        size_t cchDest,
        LPCWSTR pszSrc,
        size_t cchSrc){
    return StringCchCopyNExW(pszDest, cchDest, pszSrc, cchSrc,
            NULL, NULL, 0);
}

HRESULT StringCchCopyNExA(
        LPSTR pszDest,
        size_t cchDest,
        LPCSTR pszSrc,
        size_t cchSrc,
        LPSTR *ppszDestEnd,
        size_t * pcchRemaining,
        DWORD dwFlags){
    if(pszDest != NULL){
        *pszDest = '\0';
    }
    return StringCchCatNExA(pszDest, cchDest, pszSrc, cchSrc,
            ppszDestEnd, pcchRemaining, dwFlags);
}

HRESULT StringCchCopyNExW(
        LPWSTR pszDest,
        size_t cchDest,
        LPCWSTR pszSrc,
        size_t cchSrc,
        LPWSTR * ppszDestEnd,
        size_t * pcchRemaining,
        DWORD dwFlags){
    if(pszDest != NULL){
        *pszDest = L'\0';
    }
    return StringCchCatNExW(pszDest, cchDest, pszSrc, cchSrc,
            ppszDestEnd, pcchRemaining, dwFlags);
}

HRESULT StringCbCopyNA(
        LPSTR pszDest,
        size_t cbDest,
        LPCSTR pszSrc,
        size_t cbSrc){
    return StringCbCopyNExA(pszDest, cbDest, pszSrc, cbSrc,
            NULL, NULL, 0);
}

HRESULT StringCbCopyNW(
        LPWSTR pszDest,
        size_t cbDest,
        LPCWSTR pszSrc,
        size_t cbSrc){
    return StringCbCopyNExW(pszDest, cbDest, pszSrc, cbSrc,
            NULL, NULL, 0);
}

HRESULT StringCbCopyNExA(
        LPSTR pszDest,
        size_t cbDest,
        LPCSTR pszSrc,
        size_t cbSrc,
        LPSTR *ppszDestEnd,
        size_t * pcbRemaining,
        DWORD dwFlags){
    if(pszDest != NULL){
        *pszDest = '\0';
    }
    return StringCbCatNExA(pszDest, cbDest, pszSrc, cbSrc,
            ppszDestEnd, pcbRemaining, dwFlags);
}

HRESULT StringCbCopyNExW(
        LPWSTR pszDest,
        size_t cbDest,
        LPCWSTR pszSrc,
        size_t cbSrc,
        LPWSTR *ppszDestEnd,
        size_t * pcbRemaining,
        DWORD dwFlags){
    if(pszDest != NULL){
        *pszDest = L'\0';
    }
    return StringCbCatNExW(pszDest, cbDest, pszSrc, cbSrc,
            ppszDestEnd, pcbRemaining, dwFlags);
}
