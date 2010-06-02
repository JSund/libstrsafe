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

HRESULT StringCchCatW(
		__inout	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc){
	size_t length;
	HRESULT result;

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

HRESULT StringCchCatNW(
		__inout	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc,
		__in	size_t cchSrc){
	size_t length;
	HRESULT result;

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

HRESULT StringCchGetsA(
		__out	LPSTR pszDest,
		__in	size_t cchDest){
	size_t length = 0;
	if(cchDest < 2){
		return STRSAFE_E_INSUFFICIENT_BUFFER;
	}
	if(cchDest > STRSAFE_MAX_CCH){
		return STRSAFE_E_INVALID_PARAMETER;
	}
	while(length < cchDest - 1){
		int c = getchar();
		if(c == EOF){
			return STRSAFE_E_END_OF_FILE;
		}
		if((char)c == '\n'){
			break;
		}
		pszDest[length++] = (char)c;
	}
	pszDest[length] = '\0';
	return S_OK;
}

HRESULT StringCchPrintfA(
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszFormat,
		__in	...){
	va_list argList;
	HRESULT result;
	
	va_start(argList, pszFormat);
	result = StringCchVPrintfA(pszDest, cchDest, pszFormat, argList);
	va_end(argList);

	return result;
}

HRESULT StringCchVPrintfA(
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszFormat,
		__in	va_list argList){
	return 0;
}

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

/* Since sizeof(char) == 1, we can let Cb functions wrap Cch functions. */

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
	*pcb = pcch;
	return result;
}
