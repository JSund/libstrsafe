/*
 * Copyright (c) 2010, Jonas Sundberg <jsund@jsund.com>
 *
 * This software has been released under the terms of the ISC license. For
 * details, see the LICENSE file.
 */

#include "strsafe.h"
#include "../config.h"
#ifdef HAVE_STDARG_H
	#include <stdarg.h>
#endif
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
		LPSTR pszDest,
		size_t cchDest,
		LPCSTR pszFormat,
		va_list argList){
	return StringCchVPrintfExA(pszDest, cchDest, NULL, NULL, 0,
			pszFormat, argList);
}

HRESULT StringCchVPrintfW(
		LPWSTR pszDest,
		size_t cchDest,
		LPCWSTR pszFormat,
		va_list argList){
	return StringCchVPrintfExW(pszDest, cchDest, NULL, NULL, 0,
			pszFormat, argList);
}

HRESULT StringCchVPrintfExA(
		LPSTR pszDest,
		size_t cchDest,
		LPSTR * ppszDestEnd,
		size_t * pcchRemaining,
		DWORD dwFlags,
		LPCSTR pszFormat,
		va_list argList){
 	/* This function has a generic implementation in
	 * strsafe_vprintf_generic.h. */
	#define STRSAFE_GENERIC_WIDE_CHAR 0
	#include "strsafe_vprintf_generic.h"
	#undef STRSAFE_GENERIC_WIDE_CHAR
}

HRESULT StringCchVPrintfExW(
		LPWSTR pszDest,
		size_t cchDest,
		LPWSTR * ppszDestEnd,
		size_t * pcchRemaining,
		DWORD dwFlags,
		LPCWSTR pszFormat,
		va_list argList){
	/* This function has a generic implementation in
	 * strsafe_vprintf_generic.h. */
	#define STRSAFE_GENERIC_WIDE_CHAR 1
	#include "strsafe_vprintf_generic.h"
	#undef STRSAFE_GENERIC_WIDE_CHAR
}

HRESULT StringCbVPrintfA(
		LPSTR pszDest,
		size_t cbDest,
		LPCSTR pszFormat,
		va_list argList){
	return StringCbVPrintfExA(pszDest, cbDest, NULL, NULL, 0,
			pszFormat, argList);
}

HRESULT StringCbVPrintfW(
		LPWSTR pszDest,
		size_t cbDest,
		LPCWSTR pszFormat,
		va_list argList){
	return StringCbVPrintfExW(pszDest, cbDest, NULL, NULL, 0,
			pszFormat, argList);
}

HRESULT StringCbVPrintfExA(
		LPSTR pszDest,
		size_t cbDest,
		LPSTR * ppszDestEnd,
		size_t * pcbRemaining,
		DWORD dwFlags,
		LPCSTR pszFormat,
		va_list argList){
	return StringCchVPrintfExA(pszDest, cbDest, ppszDestEnd,
			pcbRemaining, dwFlags, pszFormat, argList);
}

HRESULT StringCbVPrintfExW(
		LPWSTR pszDest,
		size_t cbDest,
		LPWSTR * ppszDestEnd,
		size_t * pcbRemaining,
		DWORD dwFlags,
		LPCWSTR pszFormat,
		va_list argList){
	HRESULT result = StringCchVPrintfExW(pszDest, cbDest / sizeof(wchar_t),
			ppszDestEnd, pcbRemaining, dwFlags, pszFormat, argList);
	if(pcbRemaining != NULL){
		*pcbRemaining *= sizeof(wchar_t);
	}
	return result;
}
