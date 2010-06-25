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

HRESULT StringCchLengthA(
		__in	LPCSTR psz,
		__in	size_t cchMax,
		__out	size_t *pcch){
	if(psz == NULL || cchMax > STRSAFE_MAX_CCH){
		/* Invalid value for psz or cchMax. */
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

HRESULT StringCchLengthW(
		__in	LPCWSTR psz,
		__in	size_t cchMax,
		__out	size_t *pcch){
	if(psz == NULL || cchMax > STRSAFE_MAX_CCH){
		/* Invalid value for psz or cchMax. */
		return STRSAFE_E_INVALID_PARAMETER;
	}

	/* This might be a good target for optimization. */
	for(*pcch = 0; *pcch < cchMax; ){
		if(psz[*pcch] == L'\0'){
			break;
		}
		(*pcch)++;
	}
	/* If *pcch was incremented to cchMax, the first cchMax characters
	 * did not contain a null termination. */
	if(*pcch == cchMax) return STRSAFE_E_INVALID_PARAMETER;
	return S_OK;
}

HRESULT StringCbLengthA(
		__in	LPCSTR psz,
		__in	size_t cbMax,
		__out	size_t *pcb){
	return StringCchLengthA(psz, cbMax, pcb);
}

HRESULT StringCbLengthW(
		__in	LPCWSTR psz,
		__in	size_t cbMax,
		__out	size_t *pcb){
	size_t pcch;
	HRESULT result = StringCchLengthW(psz, cbMax / sizeof(wchar_t), &pcch);
	*pcb = pcch * sizeof(wchar_t);
	return result;
}
