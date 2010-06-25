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

HRESULT StringCchCopyA(
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszSrc){
	return StringCchCopyNA(pszDest, cchDest, pszSrc, cchDest);
}

HRESULT StringCchCopyW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc){
	return StringCchCopyNW(pszDest, cchDest, pszSrc, cchDest);
}

HRESULT StringCchCopyExA(
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__in	LPCSTR pszSrc,
		__out	LPSTR *ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags){
	return StringCchCopyNExA(pszDest, cchDest, pszSrc, cchDest,
			ppszDestEnd, pcchRemaining, dwFlags);
}

HRESULT StringCchCopyExW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc,
		__out	LPWSTR *ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags){
	return StringCchCopyNExW(pszDest, cchDest, pszSrc, cchDest,
			ppszDestEnd, pcchRemaining, dwFlags);
}

HRESULT StringCbCopyA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc){
	return StringCbCopyNA(pszDest, cbDest, pszSrc, cbDest);
}

HRESULT StringCbCopyW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszSrc){
	return StringCbCopyNW(pszDest, cbDest, pszSrc, cbDest);
}

HRESULT StringCbCopyExA(
		__inout	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc,
		__out	LPSTR *ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags){
	return StringCbCopyNExA(pszDest, cbDest, pszSrc, cbDest,
			ppszDestEnd, pcbRemaining, dwFlags);
}

HRESULT StringCbCopyExW(
		__inout	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszSrc,
		__out	LPWSTR * ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags){
	return StringCbCopyNExW(pszDest, cbDest, pszSrc, cbDest,
			ppszDestEnd, pcbRemaining, dwFlags);
}
