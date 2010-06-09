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
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszSrc){
	size_t length;
	HRESULT result;

	if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
		/* Invalid value for cchDest. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(FAILED(StringCchLengthA(pszSrc, STRSAFE_MAX_CCH, &length))){
		/* Should not happen if pszSrc is null terminated. */
		return STRSAFE_E_INVALID_PARAMETER;
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

HRESULT StringCchCopyW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc){
	size_t length;
	HRESULT result;

	if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
		/* Invalid value for cchDest. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(FAILED(StringCchLengthW(pszSrc, STRSAFE_MAX_CCH, &length))){
		/* Should not happen if pszSrc is null terminated. */
		return STRSAFE_E_INVALID_PARAMETER;
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

HRESULT StringCbCopyA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc){
	return StringCchCopyA(pszDest, cbDest, pszSrc);
}

HRESULT StringCbCopyW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszSrc){
	return StringCchCopyW(pszDest, cbDest / sizeof(wchar_t), pszSrc);
}
