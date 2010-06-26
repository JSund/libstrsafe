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
	/*
	 * This function has a generic implementation in strsafe_catn_generic.h.
	 */
#define STRSAFE_GENERIC_WIDE_CHAR 0
#include "strsafe_catn_generic.h"
#undef STRSAFE_GENERIC_WIDE_CHAR
}

HRESULT StringCchCatNExW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc,
		__in	size_t cchSrc,
		__out	LPWSTR *ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags){
	/*
	 * This function has a generic implementation in strsafe_catn_generic.h.
	 */
#define STRSAFE_GENERIC_WIDE_CHAR 1
#include "strsafe_catn_generic.h"
#undef STRSAFE_GENERIC_WIDE_CHAR
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
