/*
 * Copyright (c) 2010, Jonas Sundberg <jsund@jsund.com>
 *
 * This software has been released under the terms of the ISC license. For
 * details, see the LICENSE file.
 */

#include "strsafe.h"
#include <string.h>

HRESULT StringCchCatA(
		__inout	LPTSTR pszDest,
		__in	size_t cchDest,
		__in	LPCTSTR pszSrc){
	size_t length;
	HRESULT result;

	if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
		return STRSAFE_E_INVALID_PARAMETER;
	}
	result = StringCchLengthA(pszDest, cchDest, &length);
	if(FAILED(result)){
		return STRSAFE_E_INVALID_PARAMETER;
	}

	result = StringCchCopyA(pszDest + length, cchDest - length, pszSrc);
	if(FAILED(result)){
		return result;
	}
	return S_OK;
}

HRESULT StringCchCopyA(
		__out	LPTSTR pszDest,
		__in	size_t cchDest,
		__in	LPCTSTR pszSrc){
	size_t length;
	HRESULT result;

	if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
		return STRSAFE_E_INVALID_PARAMETER;
	}

	strncpy(pszDest, pszSrc, cchDest);
	result = StringCchLengthA(pszDest, cchDest, &length);
	if(FAILED(result)){
		/* A null termination was not copied into pszDest. */
		pszDest[cchDest - 1] = '\0';
		return STRSAFE_E_INSUFFICIENT_BUFFER;
	}
	return S_OK;
}

HRESULT StringCchLengthA(
		__in	LPCTSTR psz,
		__in	size_t cchMax,
		__out	size_t *pcch){
	if(psz == NULL || cchMax > STRSAFE_MAX_CCH){
		return STRSAFE_E_INVALID_PARAMETER;
	}

	/* This might be a good target for optimization. */
	for(*pcch = 0; *pcch < cchMax; ){
		if(psz[*pcch] == '\0'){
			break;
		}
		(*pcch)++;
	}
	/* If *pcch was incremented to cchMax, the first cchMax characters
	 * did not contain a null termination. */
	if(*pcch == cchMax) return STRSAFE_E_INVALID_PARAMETER;
	return S_OK;
}

HRESULT StringCbCatA(
		__inout	LPTSTR pszDest,
		__in	size_t cbDest,
		__in	LPCTSTR pszSrc){
	return StringCchCatA(pszDest, cbDest / sizeof(char), pszSrc);
}

HRESULT StringCbCopyA(
		__out	LPTSTR pszDest,
		__in	size_t cbDest,
		__in	LPCTSTR pszSrc){
	return StringCchCopyA(pszDest, cbDest / sizeof(char), pszSrc);
}

HRESULT StringCbLengthA(
		__in	LPCTSTR psz,
		__in	size_t cbMax,
		__out	size_t *pcb){
	HRESULT result = StringCchLengthA(psz, cbMax / sizeof(char), pcb);
	*pcb *= sizeof(char);
	return result;
}
