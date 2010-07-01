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

HRESULT StringCchVPrintfA(
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszFormat,
		__in	va_list argList){
	return StringCchVPrintfExA(pszDest, cchDest, NULL, NULL, 0,
			pszFormat, argList);
}

HRESULT StringCchVPrintfW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszFormat,
		__in	va_list argList){
	return StringCchVPrintfExW(pszDest, cchDest, NULL, NULL, 0,
			pszFormat, argList);
}

HRESULT StringCchVPrintfExA(
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__out	LPSTR * ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags,
		__in	LPCSTR pszFormat,
		__in	va_list argList){
 	/* This function has a generic implementation in
	 * strsafe_vprintf_generic.h. */
	#define STRSAFE_GENERIC_WIDE_CHAR 0
	#include "strsafe_vprintf_generic.h"
	#undef STRSAFE_GENERIC_WIDE_CHAR
}

HRESULT StringCchVPrintfExW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__out	LPWSTR * ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags,
		__in	LPCWSTR pszFormat,
		__in	va_list argList){
	/* This function has a generic implementation in
	 * strsafe_vprintf_generic.h. */
	#define STRSAFE_GENERIC_WIDE_CHAR 1
	#include "strsafe_vprintf_generic.h"
	#undef STRSAFE_GENERIC_WIDE_CHAR
}

HRESULT StringCbVPrintfA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszFormat,
		__in	va_list argList){
	return StringCbVPrintfExA(pszDest, cbDest, NULL, NULL, 0,
			pszFormat, argList);
}

HRESULT StringCbVPrintfW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszFormat,
		__in	va_list argList){
	return StringCbVPrintfExW(pszDest, cbDest, NULL, NULL, 0,
			pszFormat, argList);
}

HRESULT StringCbVPrintfExA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__out	LPSTR * ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags,
		__in	LPCSTR pszFormat,
		__in	va_list argList){
	return StringCchVPrintfExA(pszDest, cbDest, ppszDestEnd,
			pcbRemaining, dwFlags, pszFormat, argList);
}

HRESULT StringCbVPrintfExW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest,
		__out	LPWSTR * ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags,
		__in	LPCWSTR pszFormat,
		__in	va_list argList){
	HRESULT result = StringCchVPrintfExW(pszDest, cbDest / sizeof(wchar_t),
			ppszDestEnd, pcbRemaining, dwFlags, pszFormat, argList);
	if(pcbRemaining != NULL){
		*pcbRemaining *= sizeof(wchar_t);
	}
	return result;
}
