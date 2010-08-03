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
HRESULT result = S_OK;

if(cchDest < 2){
    if(cchDest == 1){
        *pszDest = STRSAFE_TEXT('\0');
    }
    return STRSAFE_E_INSUFFICIENT_BUFFER;
}
if(cchDest > STRSAFE_MAX_CCH){
    return STRSAFE_E_INVALID_PARAMETER;
}

/* If loop condition fails, the buffer was too small. */
while(length < cchDest - 1){
    STRSAFE_CHAR_INT c = STRSAFE_GETCHAR();
    if(c == STRSAFE_EOF){
        if(length == 0){
            result = STRSAFE_E_END_OF_FILE;
        }
        break;
    }
    if((STRSAFE_CHAR)c == STRSAFE_TEXT('\n')){
        /* The buffer was large enough, set result to S_OK. */
        break;
    }
    pszDest[length++] = (STRSAFE_CHAR)c;
}

if((dwFlags & STRSAFE_FILL_ON_FAILURE) && FAILED(result)){
    /* Fill entire buffer with lower byte of dwFlags and null terminate. */
    memset(pszDest, dwFlags & 0xff, (cchDest - 1) * sizeof(STRSAFE_CHAR));
    length = cchDest - 1;
}else if((dwFlags & (STRSAFE_NULL_ON_FAILURE | STRSAFE_NO_TRUNCATION))
        && FAILED(result)){
    /* Set the result to the empty string. */
    length = 0;
}

pszDest[length] = STRSAFE_TEXT('\0');

if(ppszDestEnd != NULL){
    *ppszDestEnd = pszDest + length;
}

if(pcchRemaining != NULL){
    *pcchRemaining = cchDest - length;
}

if(dwFlags & STRSAFE_FILL_BEHIND_NULL){
    memset(pszDest + length + 1, dwFlags & 0xff,
            (cchDest - length - 1) * sizeof(STRSAFE_CHAR));
}

return result;

#undef STRSAFE_CHAR_INT
#undef STRSAFE_GETCHAR
#undef STRSAFE_EOF
#undef STRSAFE_CHAR
#undef STRSAFE_TEXT
