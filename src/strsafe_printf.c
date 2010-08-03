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

HRESULT StringCchPrintfA(
        LPSTR pszDest,
        size_t cchDest,
        LPCSTR pszFormat,
        ...){
    va_list argList;
    HRESULT result;
    
    va_start(argList, pszFormat);
    result = StringCchVPrintfA(pszDest, cchDest, pszFormat, argList);
    va_end(argList);

    return result;
}

HRESULT StringCchPrintfW(
        LPWSTR pszDest,
        size_t cchDest,
        LPCWSTR pszFormat,
        ...){
    va_list argList;
    HRESULT result;

    va_start(argList, pszFormat);
    result = StringCchVPrintfW(pszDest, cchDest, pszFormat, argList);
    va_end(argList);

    return result;
}

HRESULT StringCchPrintfExA(
        LPSTR pszDest,
        size_t cchDest,
        LPSTR * ppszDestEnd,
        size_t * pcchRemaining,
        DWORD dwFlags,
        LPCSTR pszFormat,
        ...){
    va_list argList;
    HRESULT result;

    va_start(argList, pszFormat);
    result = StringCchVPrintfExA(pszDest, cchDest, ppszDestEnd,
            pcchRemaining, dwFlags, pszFormat, argList);
    va_end(argList);

    return result;
}


HRESULT StringCchPrintfExW(
        LPWSTR pszDest,
        size_t cchDest,
        LPWSTR * ppszDestEnd,
        size_t * pcchRemaining,
        DWORD dwFlags,
        LPCWSTR pszFormat,
        ...){
    va_list argList;
    HRESULT result;

    va_start(argList, pszFormat);
    result = StringCchVPrintfExW(pszDest, cchDest, ppszDestEnd,
            pcchRemaining, dwFlags, pszFormat, argList);
    va_end(argList);

    return result;
}

HRESULT StringCbPrintfA(
        LPSTR pszDest,
        size_t cbDest,
        LPCSTR pszFormat,
        ...){
    va_list argList;
    HRESULT result;
    
    va_start(argList, pszFormat);
    result = StringCbVPrintfA(pszDest, cbDest, pszFormat, argList);
    va_end(argList);

    return result;
}

HRESULT StringCbPrintfW(
        LPWSTR pszDest,
        size_t cbDest,
        LPCWSTR pszFormat,
        ...){
    va_list argList;
    HRESULT result;

    va_start(argList, pszFormat);
    result = StringCbVPrintfW(pszDest, cbDest, pszFormat, argList);
    va_end(argList);

    return result;
}

HRESULT StringCbPrintfExA(
        LPSTR pszDest,
        size_t cbDest,
        LPSTR * ppszDestEnd,
        size_t * pcbRemaining,
        DWORD dwFlags,
        LPCSTR pszFormat,
        ...){
    va_list argList;
    HRESULT result;

    va_start(argList, pszFormat);
    result = StringCbVPrintfExA(pszDest, cbDest, ppszDestEnd,
            pcbRemaining, dwFlags, pszFormat, argList);
    va_end(argList);

    return result;
}

HRESULT StringCbPrintfExW(
        LPWSTR pszDest,
        size_t cbDest,
        LPWSTR * ppszDestEnd,
        size_t * pcbRemaining,
        DWORD dwFlags,
        LPCWSTR pszFormat,
        ...){
    va_list argList;
    HRESULT result;

    va_start(argList, pszFormat);
    result = StringCbVPrintfExW(pszDest, cbDest, ppszDestEnd,
            pcbRemaining, dwFlags, pszFormat, argList);
    va_end(argList);

    return result;
}
