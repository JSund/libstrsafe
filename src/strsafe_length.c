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

HRESULT StringCchLengthA(
		__in	LPCSTR psz,
		__in	size_t cchMax,
		__out	size_t *pcch){
	/* This function has a generic implementation in
	 * strsafe_length_generic.h. */
	#define STRSAFE_GENERIC_WIDE_CHAR 0
	#include "strsafe_length_generic.h"
	#undef STRSAFE_GENERIC_WIDE_CHAR
}

HRESULT StringCchLengthW(
		__in	LPCWSTR psz,
		__in	size_t cchMax,
		__out	size_t *pcch){
	/* This function has a generic implementation in
	 * strsafe_length_generic.h. */
	#define STRSAFE_GENERIC_WIDE_CHAR 1
	#include "strsafe_length_generic.h"
	#undef STRSAFE_GENERIC_WIDE_CHAR
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
	*pcb = pcch * sizeof(wchar_t);
	return result;
}
