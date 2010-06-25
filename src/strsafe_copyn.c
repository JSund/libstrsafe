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
	*pszDest = '\0';
	return StringCchCatNA(pszDest, cchDest, pszSrc, cchSrc);
}

HRESULT StringCchCopyNW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__in	LPCWSTR pszSrc,
		__in	size_t cchSrc){
	*pszDest = L'\0';
	return StringCchCatNW(pszDest, cchDest, pszSrc, cchSrc);
}

HRESULT StringCbCopyNA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__in	LPCSTR pszSrc,
		__in	size_t cbSrc){
	*pszDest = '\0';
	return StringCbCatNA(pszDest, cbDest, pszSrc, cbSrc);
}

HRESULT StringCbCopyNW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest,
		__in	LPCWSTR pszSrc,
		__in	size_t cbSrc){
	*pszDest = L'\0';
	return StringCbCatNW(pszDest, cbDest, pszSrc, cbSrc);
}
