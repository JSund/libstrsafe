/*
 * Copyright (c) 2010, Jonas Sundberg <jsund@jsund.com>
 *
 * This software has been released under the terms of the ISC license. For
 * details, see the LICENSE file.
 */

#ifndef STRSAFE_GENERIC_WIDE_CHAR
#error "STRSAFE_GENERIC_WIDE_CHAR must be defined."
#elif STRSAFE_GENERIC_WIDE_CHAR == 0
#define STRSAFE_CHAR(c) c
#else
#define STRSAFE_CHAR(c) L##c
#endif

if(psz == NULL || cchMax > STRSAFE_MAX_CCH){
	/* Invalid value for psz or cchMax. */
	return STRSAFE_E_INVALID_PARAMETER;
}

/* This might be a good target for optimization. */
for(*pcch = 0; *pcch < cchMax; ){
	if(psz[*pcch] == STRSAFE_CHAR('\0')){
		break;
	}
	(*pcch)++;
}

/* If *pcch was incremented to cchMax, the first cchMax characters
 * did not contain a null termination. */
if(*pcch == cchMax) return STRSAFE_E_INVALID_PARAMETER;

return S_OK;

#undef STRSAFE_CHAR
