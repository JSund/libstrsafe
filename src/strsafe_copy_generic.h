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
	return StringCchCopyExA(pszDest, cchDest, pszSrc, NULL, NULL, 0);
}

HRESULT StringCchCopyW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc){
	return StringCchCopyExW(pszDest, cchDest, pszSrc, NULL, NULL, 0);
}

HRESULT StringCchCopyExA(
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszSrc,
		__out	LPSTR *ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags){
	size_t length;
	HRESULT result;

	if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
		/* Invalid value for cchDest. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(pszSrc == NULL && (dwFlags & STRSAFE_IGNORE_NULLS)){
		length = 0;
	}else{
		if(FAILED(StringCchLengthA(pszSrc, STRSAFE_MAX_CCH, &length))){
			/* Should not happen if pszSrc is null terminated. */
			return STRSAFE_E_INVALID_PARAMETER;
		}
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
	if(ppszDestEnd != NULL){
		*ppszDestEnd = pszDest + length;
	}
	if(pcchRemaining != NULL){
		*pcchRemaining = cchDest - length;
	}
	if(dwFlags & STRSAFE_FILL_BEHIND_NULL && length + 1 < cchDest){
		memset(pszDest + length + 1, dwFlags & 0xff, cchDest - length - 1);
	}

	return result;
}

HRESULT StringCchCopyExW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc,
		__out	LPWSTR *ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags){
	size_t length;
	HRESULT result;

	if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
		/* Invalid value for cchDest. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	if(pszSrc == NULL && (dwFlags & STRSAFE_IGNORE_NULLS)){
		length = 0;
	}else{
		if(FAILED(StringCchLengthW(pszSrc, STRSAFE_MAX_CCH, &length))){
			/* Should not happen if pszSrc is null terminated. */
			return STRSAFE_E_INVALID_PARAMETER;
		}
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
	if(ppszDestEnd != NULL){
		*ppszDestEnd = pszDest + length;
	}
	if(pcchRemaining != NULL){
		*pcchRemaining = cchDest - length;
	}
	if(dwFlags & STRSAFE_FILL_BEHIND_NULL && length + 1 < cchDest){
		memset(pszDest + length + 1, dwFlags & 0xff, cchDest - length - 1);
	}

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

HRESULT StringCbCopyExA(
		__inout	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc,
		__out	LPSTR *ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags){
	return StringCchCopyExA(pszDest, cbDest, pszSrc,
			ppszDestEnd, pcbRemaining, dwFlags);
}

HRESULT StringCbCopyExW(
		__inout	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszSrc,
		__out	LPWSTR * ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags){
	HRESULT result = StringCchCopyExW(pszDest, cbDest / sizeof(wchar_t),
			pszSrc, ppszDestEnd, pcbRemaining, dwFlags);
	if(pcbRemaining != NULL){
		*pcbRemaining *= sizeof(wchar_t);
	}
	return result;
}
