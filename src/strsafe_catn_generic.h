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
#define STRSAFE_LENGTH StringCchLengthA
#define STRSAFE_CHAR char
#define STRSAFE_TEXT(c) c
#else
#define STRSAFE_LENGTH StringCchLengthW
#define STRSAFE_CHAR wchar_t
#define STRSAFE_TEXT(c) L##c
#endif

size_t srcLength;
size_t destLength;
size_t destCapacity;
size_t length;
HRESULT result = S_OK;

if(cchDest == 0 || cchDest > STRSAFE_MAX_CCH){
	/* Invalid value for cchDest. */
	return STRSAFE_E_INVALID_PARAMETER;
}

if(pszDest == NULL && (dwFlags & STRSAFE_IGNORE_NULLS)){
	destLength = 0;
} else {
	if(FAILED(STRSAFE_LENGTH(pszDest, cchDest, &destLength))){
		/* pszDest not null terminated. */
		return STRSAFE_E_INVALID_PARAMETER;
	}
}

if(pszSrc == NULL && (dwFlags & STRSAFE_IGNORE_NULLS)){
	srcLength = 0;
} else {
	if(FAILED(STRSAFE_LENGTH(pszSrc, cchSrc, &srcLength))){
		/* pszSrc longer than length required. */
		srcLength = cchSrc;
	}
}

destCapacity = cchDest - destLength;

if(destCapacity < 2 && srcLength != 0){
	/* pszDest already full. */
	return STRSAFE_E_INVALID_PARAMETER;
}

if(srcLength >= destCapacity){
	/* pszSrc too long, copy first destCapacity - 1 characters. */
	srcLength = destCapacity - 1;
	result = STRSAFE_E_INSUFFICIENT_BUFFER;
}

length = destLength + srcLength;

if(FAILED(result)){
	if(dwFlags & STRSAFE_NO_TRUNCATION){
		/* pszDest should be left untouched. */
		return result;
	}
	if(dwFlags & STRSAFE_NULL_ON_FAILURE){
		/* pszDest should be set to the empty string. */
		*pszDest = STRSAFE_TEXT('\0');
		return result;
	}
	if(dwFlags & STRSAFE_FILL_ON_FAILURE){
		/* pszDest should be filled with the lower byte of dwFlags
		 * and null terminated. */
		memset(pszDest, dwFlags & 0xff, cchDest - 1 * sizeof(STRSAFE_CHAR));
		pszDest[cchDest - 1] = STRSAFE_TEXT('\0');
		return result;
	}
}

memcpy(pszDest + destLength, pszSrc, srcLength * sizeof(STRSAFE_CHAR));
pszDest[length] = STRSAFE_TEXT('\0');
if(ppszDestEnd != NULL){
	*ppszDestEnd = pszDest + length;
}
if(pcchRemaining != NULL){
	*pcchRemaining = cchDest - length;
}
if((dwFlags & STRSAFE_FILL_BEHIND_NULL) && length + 1 < cchDest){
	memset(pszDest + length + 1, dwFlags & 0xff,
			(cchDest - length - 1) * sizeof(STRSAFE_CHAR));
}

return result;

#undef STRSAFE_LENGTH
#undef STRSAFE_CHAR
#undef STRSAFE_TEXT
