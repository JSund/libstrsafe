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
			pszDest[length] = L'\0';
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

HRESULT StringCchGetsW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest){
	size_t length = 0;

	if(cchDest < 2){
		return STRSAFE_E_INSUFFICIENT_BUFFER;
	}
	if(cchDest > STRSAFE_MAX_CCH){
		return STRSAFE_E_INVALID_PARAMETER;
	}

	while(length < cchDest - 1){
		wint_t c = getwchar(stdin);
		if(c == WEOF){
			pszDest[length] = L'\0';
			return STRSAFE_E_END_OF_FILE;
		}
		if((wchar_t)c == L'\n'){
			break;
		}
		pszDest[length++] = (wchar_t)c;
	}
	pszDest[length] = L'\0';
	return S_OK;
}

HRESULT StringCbGetsA(
		__out	LPSTR pszDest,
		__in	size_t cbDest){
	return StringCchGetsA(pszDest, cbDest);
}

HRESULT StringCbGetsW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest){
	return StringCchGetsW(pszDest, cbDest / sizeof(wchar_t));
}
