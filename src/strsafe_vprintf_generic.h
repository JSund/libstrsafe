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
	if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
		/* Invalid value for cchDest. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if((size_t)vsnprintf(pszDest, cchDest, pszFormat, argList) >= cchDest){
		/* Data did not fit in pszDest. */
		pszDest[cchDest - 1] = '\0';
		return STRSAFE_E_INSUFFICIENT_BUFFER;
	}

	return S_OK;
}

HRESULT StringCchVPrintfW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszFormat,
		__in	va_list argList){
	if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
		/* Invalid value for cchDest. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if((size_t)vswprintf(pszDest, cchDest, pszFormat, argList) >= cchDest){
		/* Data did not fit in pszDest. */
		pszDest[cchDest - 1] = L'\0';
		return STRSAFE_E_INSUFFICIENT_BUFFER;
	}

	return S_OK;
}

HRESULT StringCbVPrintfA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszFormat,
		__in	va_list argList){
	return StringCchVPrintfA(pszDest, cbDest, pszFormat, argList);
}

HRESULT StringCbVPrintfW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszFormat,
		__in	va_list argList){
	return StringCchVPrintfW(pszDest, cbDest / sizeof(wchar_t),
			pszFormat, argList);
}
