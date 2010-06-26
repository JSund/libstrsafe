/*
 * Copyright (c) 2010, Jonas Sundberg <jsund@jsund.com>
 *
 * This software has been released under the terms of the ISC license. For
 * details, see the LICENSE file.
 */

#ifndef STRSAFE_GENERIC_WIDE_CHAR
#error "STRSAFE_GENERIC_WIDE_CHAR must be defined."
#elif STRSAFE_GENERIC_WIDE_CHAR == 0
#define STRSAFE_VPRINTF vsnprintf
#define STRSAFE_TEXT(c) c
#else
#define STRSAFE_VPRINTF vswprintf
#define STRSAFE_TEXT(c) L##c
#endif

if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
	/* Invalid value for cchDest. */
	return STRSAFE_E_INVALID_PARAMETER;
}

if((size_t)STRSAFE_VPRINTF(pszDest, cchDest, pszFormat, argList)
		>= cchDest){
	/* Data did not fit in pszDest. */
	pszDest[cchDest - 1] = STRSAFE_TEXT('\0');
	return STRSAFE_E_INSUFFICIENT_BUFFER;
}

return S_OK;

#undef STRSAFE_VPRINTF
#undef STRSAFE_TEXT
