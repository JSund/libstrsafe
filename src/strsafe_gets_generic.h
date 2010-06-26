/*
 * Copyright (c) 2010, Jonas Sundberg <jsund@jsund.com>
 *
 * This software has been released under the terms of the ISC license. For
 * details, see the LICENSE file.
 */

/*
 * Internal header for generic implementation of libstrsafe functions.
 */

#ifndef STRSAFE_GENERIC_WIDE_CHAR
#error "STRSAFE_GENERIC_WIDE_CHAR must be defined."
#elif STRSAFE_GENERIC_WIDE_CHAR == 0
#define STRSAFE_CHAR_INT int
#define STRSAFE_GETCHAR getchar
#define STRSAFE_EOF EOF
#define STRSAFE_CHAR char
#define STRSAFE_TEXT(c) c
#else
#define STRSAFE_CHAR_INT wint_t
#define STRSAFE_GETCHAR getwchar
#define STRSAFE_EOF WEOF
#define STRSAFE_CHAR wchar_t
#define STRSAFE_TEXT(c) L##c
#endif

size_t length = 0;

if(cchDest < 2){
	return STRSAFE_E_INSUFFICIENT_BUFFER;
}
if(cchDest > STRSAFE_MAX_CCH){
	return STRSAFE_E_INVALID_PARAMETER;
}

while(length < cchDest - 1){
	STRSAFE_CHAR_INT c = STRSAFE_GETCHAR();
	if(c == STRSAFE_EOF){
		pszDest[length] = STRSAFE_TEXT('\0');
		return STRSAFE_E_END_OF_FILE;
	}
	if((STRSAFE_CHAR)c == STRSAFE_TEXT('\n')){
		break;
	}
	pszDest[length++] = (STRSAFE_CHAR)c;
}
pszDest[length] = STRSAFE_TEXT('\0');
return S_OK;

#undef STRSAFE_CHAR_INT
#undef STRSAFE_GETCHAR
#undef STRSAFE_EOF
#undef STRSAFE_CHAR
#undef STRSAFE_TEXT
