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
		__inout	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszSrc){
	return StringCchCatNA(pszDest, cchDest, pszSrc, cchDest);
}

HRESULT StringCchCatW(
		__inout LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc){
	return StringCchCatNW(pszDest, cchDest, pszSrc, cchDest);
}

HRESULT StringCchCatExA(
		__inout	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszSrc,
		__out	LPSTR * ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags){
	return StringCchCatNExA(pszDest, cchDest, pszSrc, cchDest,
			ppszDestEnd, pcchRemaining, dwFlags);
}

HRESULT StringCchCatExW(
		__inout	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc,
		__out	LPWSTR * ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags){
	return StringCchCatNExW(pszDest, cchDest, pszSrc, cchDest,
			ppszDestEnd, pcchRemaining, dwFlags);
}

HRESULT StringCbCatA(
		__inout	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc){
	return StringCbCatNA(pszDest, cbDest, pszSrc, cbDest);
}

HRESULT StringCbCatW(
		__inout	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszSrc){
	return StringCbCatNW(pszDest, cbDest, pszSrc, cbDest);
}

HRESULT StringCbCatExA(
		__inout	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc,
		__out	LPSTR * ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags){
	return StringCbCatNExA(pszDest, cbDest, pszSrc, cbDest,
			ppszDestEnd, pcbRemaining, dwFlags);
}

HRESULT StringCbCatExW(
		__inout	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszSrc,
		__out	LPWSTR * ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags){
	return StringCbCatNExW(pszDest, cbDest, pszSrc, cbDest,
			ppszDestEnd, pcbRemaining, dwFlags);
}
