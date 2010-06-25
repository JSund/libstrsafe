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
HRESULT StringCchCopyNA(
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszSrc,
		__in	size_t cchSrc){
	return StringCchCopyNExA(pszDest, cchDest, pszSrc, cchSrc,
			NULL, NULL, 0);
}

HRESULT StringCchCopyNW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc,
		__in	size_t cchSrc){
	return StringCchCopyNExW(pszDest, cchDest, pszSrc, cchSrc,
			NULL, NULL, 0);
}

HRESULT StringCchCopyNExA(
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszSrc,
		__out	LPSTR *ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags){
	if(pszDest != NULL){
		*pszDest = '\0';
	}
	return StringCchCatNExA(pszDest, cchDest, pszSrc, cchDest,
			ppszDestEnd, pcchRemaining, dwFlags);
}

HRESULT StringCchCopyNExW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc,
		__out	LPWSTR *ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags){
	if(pszDest != NULL){
		*pszDest = L'\0';
	}
	return StringCchCatNExW(pszDest, cchDest, pszSrc, cchDest,
			ppszDestEnd, pcchRemaining, dwFlags);
}

HRESULT StringCbCopyNA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc,
		__in	size_t cbSrc){
	return StringCbCopyNExA(pszDest, cbDest, pszSrc, cbSrc,
			NULL, NULL, 0);
}

HRESULT StringCbCopyNW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszSrc,
		__in	size_t cbSrc){
	return StringCbCopyNExW(pszDest, cbDest, pszSrc, cbSrc,
			NULL, NULL, 0);
}

HRESULT StringCbCopyNExA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc,
		__out	LPSTR *ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags){
	if(pszDest != NULL){
		*pszDest = '\0';
	}
	return StringCbCatNExA(pszDest, cbDest, pszSrc, cbDest,
			ppszDestEnd, pcbRemaining, dwFlags);
}

HRESULT StringCbCopyNExW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszSrc,
		__out	LPWSTR *ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags){
	if(pszDest != NULL){
		*pszDest = L'\0';
	}
	return StringCbCatNExW(pszDest, cbDest, pszSrc, cbDest,
			ppszDestEnd, pcbRemaining, dwFlags);
}
