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

HRESULT StringCchCatA(
		__inout	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszSrc){
	return StringCchCatExA(pszDest, cchDest, pszSrc, NULL, NULL, 0);
}

HRESULT StringCchCatW(
		__inout LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc){
	return StringCchCatExW(pszDest, cchDest, pszSrc, NULL, NULL, 0);
}

HRESULT StringCchCatExA(
		__inout	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszSrc,
		__out	LPSTR * ppszDestEnd __attribute__((unused)),
		__out	size_t * pcchRemaining __attribute__((unused)),
		__in	DWORD dwFlags __attribute__((unused))){
	size_t length;

	if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
		/* Invalid value for cchDest. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(FAILED(StringCchLengthA(pszDest, cchDest, &length))){
		/* pszDest not null terminated. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(cchDest - length < 2){
		/* pszDest already full. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	return StringCchCopyA(pszDest + length, cchDest - length, pszSrc);
}

HRESULT StringCchCatExW(
		__inout	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc,
		__out	LPWSTR * ppszDestEnd __attribute__((unused)),
		__out	size_t * pcchRemaining __attribute__((unused)),
		__in	DWORD dwFlags __attribute__((unused))){
	size_t length;

	if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
		/* Invalid value for cchDest. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(FAILED(StringCchLengthW(pszDest, cchDest, &length))){
		/* pszDest not null terminated. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(cchDest - length < 2){
		/* pszDest already full. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	return StringCchCopyW(pszDest + length, cchDest - length, pszSrc);
}

HRESULT StringCbCatA(
		__inout	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc){
	return StringCchCatA(pszDest, cbDest, pszSrc);
}

HRESULT StringCbCatW(
		__inout	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszSrc){
	return StringCchCatW(pszDest, cbDest / sizeof(wchar_t), pszSrc);
}

HRESULT StringCbCatExA(
		__inout	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc,
		__out	LPSTR * ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags){
	return StringCchCatExA(pszDest, cbDest, pszSrc,
			ppszDestEnd, pcbRemaining, dwFlags);
}

HRESULT StringCbCatExW(
		__inout	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszSrc,
		__out	LPWSTR * ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags){
	HRESULT result = StringCchCatExW(pszDest, cbDest / sizeof(wchar_t),
			pszSrc, ppszDestEnd, pcbRemaining, dwFlags);
	if(pcbRemaining != NULL){
		*pcbRemaining *= sizeof(wchar_t);
	}
	return result;
}
