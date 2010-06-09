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
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszSrc,
		__in	size_t cchSrc){
	size_t length;
	HRESULT result;

	if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
		/* Invalid value for cchDest. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(FAILED(StringCchLengthA(pszSrc, cchSrc + 1, &length))){
		/* pszSrc is longer than the maximum length to copy. */
		/* Copy only first cchSrc characters. */
		length = cchSrc;
	}

	if(length >= cchDest){
		/* pszSrc too long, copy first cchDest - 1 characters. */
		length = cchDest - 1;
		result = STRSAFE_E_INSUFFICIENT_BUFFER;
	}else{
		result = S_OK;
	}

	memcpy(pszDest, pszSrc, length);
	pszDest[length] = '\0';

	return result;
}

HRESULT StringCchCopyNW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc,
		__in	size_t cchSrc){
	size_t length;
	HRESULT result;

	if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
		/* Invalid value for cchDest. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(FAILED(StringCchLengthW(pszSrc, cchSrc + 1, &length))){
		/* pszSrc is longer than the maximum length to copy. */
		/* Copy only first cchSrc characters. */
		length = cchSrc;
	}

	if(length >= cchDest){
		/* pszSrc too long, copy first cchDest - 1 characters. */
		length = cchDest - 1;
		result = STRSAFE_E_INSUFFICIENT_BUFFER;
	}else{
		result = S_OK;
	}

	memcpy(pszDest, pszSrc, length * sizeof(wchar_t));
	pszDest[length] = L'\0';

	return result;
}

HRESULT StringCbCopyNA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc,
		__in	size_t cbSrc){
	return StringCchCopyNA(pszDest, cbDest, pszSrc, cbSrc);
}

HRESULT StringCbCopyNW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszSrc,
		__in	size_t cbSrc){
	return StringCchCopyNW(pszDest, cbDest / sizeof(wchar_t),
			pszSrc, cbSrc / sizeof(wchar_t));
}
