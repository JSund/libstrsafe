/*
 * Copyright (c) 2010, Jonas Sundberg <jsund@jsund.com>
 *
 * This software has been released under the terms of the ISC license. For
 * details, see the LICENSE file.
 */

#include "strsafe.h"
#include "../config.h"
#ifdef HAVE_STRING_H
	#include <string.h>
#endif
#ifdef HAVE_STDIO_H
	#include <stdio.h>
#endif

HRESULT StringCchCatA(
		__inout	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszSrc){
	size_t length;
	HRESULT result;

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

HRESULT StringCchCatNA(
		__inout	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszSrc,
		__in	size_t cchSrc){
	size_t length;
	HRESULT result;

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

HRESULT StringCchGetsA(
		__out	LPSTR pszDest,
		__in	size_t cchDest){
	size_t length = 0;
	int c;
	if(cchDest < 2){
		return STRSAFE_E_INSUFFICIENT_BUFFER;
	}
	if(cchDest > STRSAFE_MAX_CCH){
		return STRSAFE_E_INVALID_PARAMETER;
	}
	c = getchar();
	while(length < cchDest){
		if(c == EOF){
			return STRSAFE_E_END_OF_FILE;
		}
		if((char)c == '\n'){
			pszDest[length] = '\0';
			return S_OK;
		}
		pszDest[length++] = (char)c;
		c = getchar();
	}
}

HRESULT StringCchPrintfA(
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszFormat,
		__in	...){
	va_list args;
	HRESULT result;
	
	va_start(args, pszFormat);
	result = StringCchVPrintfA(pszDest, cchDest, pszFormat, args);
	va_end(args);

	return result;
}

HRESULT StringCchLengthA(
		__in	LPCSTR psz,
		__in	size_t cchMax,
		__out	size_t *pcch){
	if(psz == NULL || cchMax > STRSAFE_MAX_CCH){
		/* Invalid value for cchDest. */
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

/* Since sizeof(char) == 1, we can let Cb functions wrap Cch functions. */

HRESULT StringCbCatA(
		__inout	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc){
	return StringCchCatA(pszDest, cbDest, pszSrc);
}

HRESULT StringCbCatNA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc,
		__in	size_t cbSrc){
	return StringCchCatNA(pszDest, cbDest, pszSrc, cbSrc);
}

HRESULT StringCbCopyA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc){
	return StringCchCopyA(pszDest, cbDest, pszSrc);
}

HRESULT StringCbCopyNA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc,
		__in	size_t cbSrc){
	return StringCchCopyNA(pszDest, cbDest, pszSrc, cbSrc);
}

HRESULT StringCbLengthA(
		__in	LPCSTR psz,
		__in	size_t cbMax,
		__out	size_t *pcb){
	return StringCchLengthA(psz, cbMax, pcb);
}
