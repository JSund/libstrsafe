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
		LPSTR pszDest,
		size_t cchDest,
		LPCSTR pszSrc,
		size_t cchSrc){
	return StringCchCatNExA(pszDest, cchDest, pszSrc, cchSrc,
			NULL, NULL, 0);
}

HRESULT StringCchCatNW(
		LPWSTR pszDest,
		size_t cchDest,
		LPCWSTR pszSrc,
		size_t cchSrc){
	return StringCchCatNExW(pszDest, cchDest, pszSrc, cchSrc,
			NULL, NULL, 0);
}

HRESULT StringCchCatNExA(
		LPSTR pszDest,
		size_t cchDest,
		LPCSTR pszSrc,
		size_t cchSrc,
		LPSTR * ppszDestEnd,
		size_t * pcchRemaining,
		DWORD dwFlags){
	/* This function has a generic implementation in
	 * strsafe_catn_generic.h. */
	#define STRSAFE_GENERIC_WIDE_CHAR 0
	#include "strsafe_catn_generic.h"
	#undef STRSAFE_GENERIC_WIDE_CHAR
}

HRESULT StringCchCatNExW(
		LPWSTR pszDest,
		size_t cchDest,
		LPCWSTR pszSrc,
		size_t cchSrc,
		LPWSTR * ppszDestEnd,
		size_t * pcchRemaining,
		DWORD dwFlags){
	/* This function has a generic implementation in
	 * strsafe_catn_generic.h. */
	#define STRSAFE_GENERIC_WIDE_CHAR 1
	#include "strsafe_catn_generic.h"
	#undef STRSAFE_GENERIC_WIDE_CHAR
}

HRESULT StringCbCatNA(
		LPSTR pszDest,
		size_t cbDest,
		LPCSTR pszSrc,
		size_t cbSrc){
	return StringCbCatNExA(pszDest, cbDest, pszSrc, cbSrc,
			NULL, NULL, 0);
}

HRESULT StringCbCatNW(
		LPWSTR pszDest,
		size_t cbDest,
		LPCWSTR pszSrc,
		size_t cbSrc){
	return StringCbCatNExW(pszDest, cbDest, pszSrc, cbSrc,
			NULL, NULL, 0);
}

HRESULT StringCbCatNExA(
		LPSTR pszDest,
		size_t cbDest,
		LPCSTR pszSrc,
		size_t cbSrc,
		LPSTR * ppszDestEnd,
		size_t * pcbRemaining,
		DWORD dwFlags){
	return StringCchCatNExA(pszDest, cbDest, pszSrc, cbSrc,
			ppszDestEnd, pcbRemaining, dwFlags);
}

HRESULT StringCbCatNExW(
		LPWSTR pszDest,
		size_t cbDest,
		LPCWSTR pszSrc,
		size_t cbSrc,
		LPWSTR * ppszDestEnd,
		size_t * pcbRemaining,
		DWORD dwFlags){
	HRESULT result = StringCchCatNExW(pszDest, cbDest / sizeof(wchar_t),
			pszSrc, cbSrc / sizeof(wchar_t),
			ppszDestEnd, pcbRemaining, dwFlags);
	if(pcbRemaining != NULL){
		*pcbRemaining *= sizeof(wchar_t);
	}
	return result;
}
