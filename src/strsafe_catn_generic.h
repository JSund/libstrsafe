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

HRESULT StringCchCatNA(
		__inout	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszSrc,
		__in	size_t cchSrc){
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

	return StringCchCopyNA(pszDest + length, cchDest - length,
			pszSrc, cchSrc);
}

HRESULT StringCchCatNW(
		__inout	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc,
		__in	size_t cchSrc){
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

	return StringCchCopyNW(pszDest + length, cchDest - length,
			pszSrc, cchSrc);
}

HRESULT StringCbCatNA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc,
		__in	size_t cbSrc){
	return StringCchCatNA(pszDest, cbDest, pszSrc, cbSrc);
}

HRESULT StringCbCatNW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszSrc,
		__in	size_t cbSrc){
	return StringCchCatNW(pszDest, cbDest / sizeof(wchar_t),
			pszSrc, cbSrc / sizeof(wchar_t));
}
