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
	return StringCchCatNExA(pszDest, cchDest, pszSrc, cchSrc,
			NULL, NULL, 0);
}

HRESULT StringCchCatNW(
		__inout	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc,
		__in	size_t cchSrc){
	return StringCchCatNExW(pszDest, cchDest, pszSrc, cchSrc,
			NULL, NULL, 0);
}

HRESULT StringCchCatNExA(
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszSrc,
		__in	size_t cchSrc,
		__out	LPSTR *ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags){
	size_t srcLength;
	size_t destLength;
	size_t destCapacity;
	size_t length;
	HRESULT result = S_OK;

	if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
		/* Invalid value for cchDest. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(FAILED(StringCchLengthA(pszDest, cchDest, &destLength))){
		/* pszDest not null terminated. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(pszSrc == NULL && (dwFlags & STRSAFE_IGNORE_NULLS)){
		srcLength = 0;
	} else {
		if(FAILED(StringCchLengthA(pszSrc, cchSrc, &srcLength))){
			/* pszSrc longer than length required. */
			srcLength = cchSrc;
		}
	}

	destCapacity = cchDest - destLength;

	if(destCapacity < 2 && srcLength != 0){
		/* pszDest already full. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(srcLength >= destCapacity){
		/* pszSrc too long, copy first destCapacity - 1 characters. */
		srcLength = destCapacity - 1;
		result = STRSAFE_E_INSUFFICIENT_BUFFER;
	}

	length = destLength + srcLength;

	memcpy(pszDest + destLength, pszSrc, srcLength);
	pszDest[length] = '\0';
	if(ppszDestEnd != NULL){
		*ppszDestEnd = pszDest + length;
	}
	if(pcchRemaining != NULL){
		*pcchRemaining = cchDest - length;
	}
	if((dwFlags & STRSAFE_FILL_BEHIND_NULL) && length + 1 < cchDest){
		memset(pszDest + length + 1, dwFlags & 0xff, cchDest - length - 1);
	}

	return result;
}

HRESULT StringCchCatNExW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc,
		__in	size_t cchSrc,
		__out	LPWSTR *ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags){
	size_t srcLength;
	size_t destLength;
	size_t destCapacity;
	size_t length;
	HRESULT result = S_OK;

	if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
		/* Invalid value for cchDest. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(FAILED(StringCchLengthW(pszDest, cchDest, &destLength))){
		/* pszDest not null terminated. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(pszSrc == NULL && (dwFlags & STRSAFE_IGNORE_NULLS)){
		srcLength = 0;
	} else {
		if(FAILED(StringCchLengthW(pszSrc, cchSrc, &srcLength))){
			/* pszSrc longer than length required. */
			srcLength = cchSrc;
		}
	}

	destCapacity = cchDest - destLength;

	if(destCapacity < 2 && srcLength != 0){
		/* pszDest already full. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(srcLength >= destCapacity){
		/* pszSrc too long, copy first destCapacity - 1 characters. */
		srcLength = destCapacity - 1;
		result = STRSAFE_E_INSUFFICIENT_BUFFER;
	}

	length = destLength + srcLength;

	memcpy(pszDest + destLength, pszSrc, srcLength * sizeof(wchar_t));
	pszDest[length] = L'\0';
	if(ppszDestEnd != NULL){
		*ppszDestEnd = pszDest + length;
	}
	if(pcchRemaining != NULL){
		*pcchRemaining = cchDest - length;
	}
	if((dwFlags & STRSAFE_FILL_BEHIND_NULL) && length + 1 < cchDest){
		memset(pszDest + length + 1, dwFlags & 0xff,
				(cchDest - length - 1) * sizeof(wchar_t));
	}

	return result;
}

HRESULT StringCbCatNA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc,
		__in	size_t cbSrc){
	return StringCbCatNExA(pszDest, cbDest, pszSrc, cbSrc,
			NULL, NULL, 0);
}

HRESULT StringCbCatNW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszSrc,
		__in	size_t cbSrc){
	return StringCbCatNExW(pszDest, cbDest, pszSrc, cbSrc,
			NULL, NULL, 0);
}

HRESULT StringCbCatNExA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc,
		__in	size_t cbSrc,
		__out	LPSTR *ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags){
	return StringCchCatNExA(pszDest, cbDest, pszSrc, cbSrc,
			ppszDestEnd, pcbRemaining, dwFlags);
}

HRESULT StringCbCatNExW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszSrc,
		__in	size_t cbSrc,
		__out	LPWSTR *ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags){
	HRESULT result = StringCchCatNExW(pszDest, cbDest / sizeof(wchar_t),
			pszSrc, cbSrc / sizeof(wchar_t),
			ppszDestEnd, pcbRemaining, dwFlags);
	if(pcbRemaining != NULL){
		*pcbRemaining *= sizeof(wchar_t);
	}
	return result;
}
