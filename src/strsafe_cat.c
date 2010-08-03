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

HRESULT StringCchCatA(
		LPSTR pszDest,
		size_t cchDest,
		LPCSTR pszSrc){
	return StringCchCatNA(pszDest, cchDest, pszSrc, cchDest);
}

HRESULT StringCchCatW(
		LPWSTR pszDest,
		size_t cchDest,
		LPCWSTR pszSrc){
	return StringCchCatNW(pszDest, cchDest, pszSrc, cchDest);
}

HRESULT StringCchCatExA(
		LPSTR pszDest,
		size_t cchDest,
		LPCSTR pszSrc,
		LPSTR * ppszDestEnd,
		size_t * pcchRemaining,
		DWORD dwFlags){
	return StringCchCatNExA(pszDest, cchDest, pszSrc, cchDest,
			ppszDestEnd, pcchRemaining, dwFlags);
}

HRESULT StringCchCatExW(
		LPWSTR pszDest,
		size_t cchDest,
		LPCWSTR pszSrc,
		LPWSTR * ppszDestEnd,
		size_t * pcchRemaining,
		DWORD dwFlags){
	return StringCchCatNExW(pszDest, cchDest, pszSrc, cchDest,
			ppszDestEnd, pcchRemaining, dwFlags);
}

HRESULT StringCbCatA(
		LPSTR pszDest,
		size_t cbDest,
		LPCSTR pszSrc){
	return StringCbCatNA(pszDest, cbDest, pszSrc, cbDest);
}

HRESULT StringCbCatW(
		LPWSTR pszDest,
		size_t cbDest,
		LPCWSTR pszSrc){
	return StringCbCatNW(pszDest, cbDest, pszSrc, cbDest);
}

HRESULT StringCbCatExA(
		LPSTR pszDest,
		size_t cbDest,
		LPCSTR pszSrc,
		LPSTR * ppszDestEnd,
		size_t * pcbRemaining,
		DWORD dwFlags){
	return StringCbCatNExA(pszDest, cbDest, pszSrc, cbDest,
			ppszDestEnd, pcbRemaining, dwFlags);
}

HRESULT StringCbCatExW(
		LPWSTR pszDest,
		size_t cbDest,
		LPCWSTR pszSrc,
		LPWSTR * ppszDestEnd,
		size_t * pcbRemaining,
		DWORD dwFlags){
	return StringCbCatNExW(pszDest, cbDest, pszSrc, cbDest,
			ppszDestEnd, pcbRemaining, dwFlags);
}
