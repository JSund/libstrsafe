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
	return StringCchGetsExA(pszDest, cchDest, NULL, NULL, 0);
}

HRESULT StringCchGetsW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest){
	return StringCchGetsExW(pszDest, cchDest, NULL, NULL, 0);
}

HRESULT StringCchGetsExA(
		__out	LPSTR pszDest,
		__in	size_t cchDest,
		__out	LPSTR * ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags){
	if(ppszDestEnd != NULL || pcchRemaining != NULL || dwFlags != 0){
		/* Not implemented yet. */
		return 4711;
	}{
	/* This function has a generic implementation in
	 * strsafe_gets_generic.h. */
	#define STRSAFE_GENERIC_WIDE_CHAR 0
	#include "strsafe_gets_generic.h"
	#undef STRSAFE_GENERIC_WIDE_CHAR
	} /* Remove! */
}

HRESULT StringCchGetsExW(
		__out	LPWSTR pszDest,
		__in	size_t cchDest,
		__out	LPWSTR * ppszDestEnd,
		__out	size_t * pcchRemaining,
		__in	DWORD dwFlags){
	if(ppszDestEnd != NULL || pcchRemaining != NULL || dwFlags != 0){
		/* Not implemented yet. */
		return 4711;
	}{
	/* This function has a generic implementation in
	 * strsafe_gets_generic.h. */
	#define STRSAFE_GENERIC_WIDE_CHAR 1
	#include "strsafe_gets_generic.h"
	#undef STRSAFE_GENERIC_WIDE_CHAR
	} /* Remove! */
}

HRESULT StringCbGetsA(
		__out	LPSTR pszDest,
		__in	size_t cbDest){
	return StringCbGetsExA(pszDest, cbDest, NULL, NULL, 0);
}

HRESULT StringCbGetsW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest){
	return StringCbGetsExW(pszDest, cbDest, NULL, NULL, 0);
}

HRESULT StringCbGetsExA(
		__out	LPSTR pszDest,
		__in	size_t cbDest,
		__out	LPSTR * ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags){
	return StringCchGetsExA(pszDest, cbDest,
			ppszDestEnd, pcbRemaining, dwFlags);
}

HRESULT StringCbGetsExW(
		__out	LPWSTR pszDest,
		__in	size_t cbDest,
		__out	LPWSTR * ppszDestEnd,
		__out	size_t * pcbRemaining,
		__in	DWORD dwFlags){
	HRESULT result = StringCchGetsExW(pszDest, cbDest / sizeof(wchar_t),
			ppszDestEnd, pcbRemaining, dwFlags);
	if(pcbRemaining != NULL){
		*pcbRemaining *= sizeof(wchar_t);
	}
	return result;
}
