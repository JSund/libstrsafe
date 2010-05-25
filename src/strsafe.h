/*
 * Copyright (c) 2010, Jonas Sundberg <jsund@jsund.com>
 *
 * This software has been released under the terms of the ISC license. For
 * details, see the LICENSE file.
 */

/**
 * @file strsafe.h
 *
 * Provides the public interface to the libstrsafe functions.
 *
 * For more information on libstrsafe, see the README file.
 */

#ifndef STRSAFE_H
#define STRSAFE_H

#include <stddef.h>
#include <stdint.h>

/**
 * The result of a function call. All function calls in libstrsafe returns
 * an HRESULT, a value representing the result of the function call.
 * This can later be checked with the SUCCEEDED or FAILED macros.
 */
#define HRESULT uint32_t

/*
 * Bits set in a HRESULT correspond to various error messages.
 */
#define S_OK (uint32_t)0x0000
#define STRSAFE_E_END_OF_FILE (uint32_t)0x0001
#define STRSAFE_E_INVALID_PARAMETER (uint32_t)0x0002
#define STRSAFE_E_INSUFFICIENT_BUFFER (uint32_t)0x0004

/*
 * The maximum number of characters allowed.
 */
#define STRSAFE_MAX_CCH 0x7fffffff /* 2^31 - 1 or 2,147,483,647 */

/**
 * Checks that the previous call succeeded. This is implemented as a macro
 * that checks the data returned by a previous function call.
 *
 * @param result The result to check.
 *
 * @return True if the result contained no errors and false otherwise.
 */
#define SUCCEEDED(result) ((result) == S_OK)

/**
 * Checks that the previous call failed. This is implemented as a macro
 * that checks the data returned by a previous function call. 
 *
 * @param result The result to check.
 *
 * @return True if the result contained errors and false otherwise.
 */
#define FAILED(result) ((result) != S_OK)

/*
 * __out, __in and __inout marks whether a parameter to a function call
 * is used for output, input or both input and output, respectively.
 */
#define __out
#define __in
#define __inout

/**
 * A pointer to a string buffer. In this simplified version of the library,
 * an LPTSTR is a pointer to a string buffer consisting of chars.
 */
#define LPTSTR char *

/**
 * A pointer to an immutable string buffer. In this simplified version of
 * the library, an LPCTSTR is a pointer to a string buffer consisting of
 * chars that should not be modified.
 */
#define LPCTSTR const char *

/**
 * Concatenates the strings in pszDest and pszSrc and stores the result
 * in pszDest. If the concatenated string does not fit into pszDest, the
 * string is truncated and null terminated.
 *
 * Running time is linear in the length of the strings pszSrc and pszDest
 * or the value of cchDest, whichever is lower.
 *
 * @param pszDest The first part of the concatenated string as well as the
 *                destination of the concatenated string.
 * @param cchDest Capacity of pszDest in number of characters.
 * @param pszSrc The second part of the concatenated string that is to be
 *               appended to pszDest.
 *
 * @return A HRESULT that should be checked with the SUCCEEDED or FAILED
 *         macros after use.
 *
 *         Returns S_OK if the concatenation was successful.
 *
 *         Returns STRSAFE_E_INVALID_PARAMETER if the capacity cbDest
 *         is zero, larger than the maximum capacity allowed or if
 *         a null termination is not found in pszDest.
 *
 *         Returns STRSAFE_E_INSUFFICIENT_BUFFER if the data in pszSrc
 *         did not fint into the remaining part of pszDst. The data from
 *         pszSrc has been truncated to fit in the remaining part of
 *         pszDst and this truncated data has been null terminated and
 *         written after the current data in pszDst.
 */
#ifdef UNICODE
	#define StringCchCat StringCchCatW
#else
	#define StringCchCat StringCchCatA
#endif
HRESULT StringCchCatA(
	__inout	LPSTR pszDest,
	__in	size_t cchDest,
	__in	LPCSTR pszSrc
);
HRESULT StringCchCatW(
	__inout LPWSTR pszDest,
	__in	size_t cchDest,
	__in	LPCWSTR pszSrc
);

/* TODO: Documentation of StringCchCatEx. */
#ifdef UNICODE
	#define StringCchCatEx StringCchCatExW
#else
	#define StringCchCatEx StringCchCatExA
#endif
HRESULT StringCchCatExA(
	__inout	LPSTR pszDest,
	__in	size_t cchDest,
	__in	LPCSTR pszSrc,
	__out	LPSTR *ppszDestEnd,
	__out	size_t *pcchRemaining,
	__in	DWORD dwFlags
);
HRESULT StringCchCatExW(
	__inout	LPWSTR pszDest,
	__in	size_t cchDest,
	__in	LPCWSTR pszSrc,
	__out	LPWSTR *ppszDestEnd,
	__out	size_t *pcchRemaining,
	__in	DWORD dwFlags
);


/**
 * Copies the content of pszSrc into pszDest until a null character is
 * found. StringCchCopy assures that the string is null terminated.
 * If the data in pszSrc does not fit into pszDest, the string is
 * truncated and null terminated.
 *
 * Running time is linear in the length of pszSrc or the value of cchDest,
 * whichever is lower.
 *
 * @param pszDest The destination of the copy.
 * @param cchDest Capacity of pszDest in number of characters.
 * @param pszSrc The source to copy data from.
 *
 * @return A HRESULT that should be checked with the SUCCEEDED or FAILED
 *         macros after use.
 *
 *         Returns S_OK if the copy was successful.
 *
 *         Returns STRSAFE_E_INVALID_PARAMETER if the capacity cchDest
 *         is zero or larger than the maximum capacity allowed.
 *
 *         Returns STRSAFE_E_INSUFFICIENT_BUFFER if the data in pszSrc did
 *         not fit into pszDst. The data from pszSrc has been truncated
 *         to fit in pszDst and this truncated data has been null terminated
 *         and written into pszDst.
 */
#ifdef UNICODE
	#define StringCchCopy StringCchCopyW
#else
	#define StringCchCopy StringCchCopyA
#endif
HRESULT StringCchCopyA(
	__out	LPSTR pszDest,
	__in	size_t cchDest,
	__in	LPCSTR pszSrc
);
HRESULT StringCchCopyA(
	__out	LPWSTR pszDest,
	__in	size_t cchDest,
	__in	LPCWSTR pszSrc
);

/**
 * Calculates the length of psz by iterating over it until a null character
 * is reached. The null character is not counted as part of the string.
 *
 * Running time is linear in the length of the string.
 *
 * @param psz The string to calculate the length for.
 * @param cchMax Capacity of psz in number of characters.
 * @param pcch The calculated length. The calculated value is undefined if
 *             the function failed.
 *
 * @return A HRESULT that should be checked with the SUCCEEDED or FAILED
 *         macros after use.
 *
 *         Returns S_OK if the length was calculated correctly.
 *
 *         Returns STRSAFE_E_INVALID_PARAMETER if the capacity cbMax
 *         is larger than the maximum capacity allowed or if a null
 *         termination is not found in psz.
 */
#ifdef UNICODE
	#define StringCchLength StringCchLengthW
#else
	#define StringCchLength StringCchLengthA
#endif
HRESULT StringCchLengthA(
	__in	LPCSTR psz,
	__in	size_t cchMax,
	__out	size_t *pcch
);
HRESULT StringCchLengthA(
	__in	LPCWSTR psz,
	__in	size_t cchMax,
	__out	size_t *pcch
);

/**
 * Concatenates the strings in pszDest and pszSrc and stores the result
 * in pszDest. If the concatenated string does not fit into pszDest, the
 * string is truncated and null terminated.
 *
 * Running time is linear in the length of the strings pszSrc and pszDest
 * or the value of cbDest, whichever is lower.
 *
 * @param pszDest The first part of the concatenated string as well as the
 *                destination of the concatenated string.
 * @param cbDest Capacity of pszDest in bytes.
 * @param pszSrc The second part of the concatenated string that is to be
 *               appended to pszDest.
 *
 * @return A HRESULT that should be checked with the SUCCEEDED or FAILED
 *         macros after use.
 *
 *         Returns S_OK if the concatenation was successful.
 *
 *         Returns STRSAFE_E_INVALID_PARAMETER if the capacity cbDest
 *         is zero, larger than the maximum capacity allowed or if
 *         a null termination is not found in pszDest.
 *
 *         Returns STRSAFE_E_INSUFFICIENT_BUFFER if the data in pszSrc
 *         did not fint into the remaining part of pszDst. The data from
 *         pszSrc has been truncated to fit in the remaining part of
 *         pszDst and this truncated data has been null terminated and
 *         written after the current data in pszDst.
 */
#ifdef UNICODE
	#define StringCbCat StringCbCatW
#else
	#define StringCbCat StringCbCatA
#endif
HRESULT StringCbCatA(
	__inout	LPSTR pszDest,
	__in	size_t cbDest,
	__in	LPCSTR pszSrc
);
HRESULT StringCbCatW(
	__inout	LPWSTR pszDest,
	__in	size_t cbDest,
	__in	LPCWSTR pszSrc
);

/**
 * Copies the content of pszSrc into pszDest until a null byte is found.
 * StringCbCopy assures that the string is null terminated. If the data in
 * pszSrc does not fit into pszDest, the string is truncated and null
 * terminated.
 *
 * Running time is linear in the length of pszSrc or the value of cbDest,
 * whichever is lower.
 *
 * @param pszDest The destination of the copy.
 * @param cbDest Capacity of pszDest in bytes.
 * @param pszSrc The source to copy data from.
 *
 * @return A HRESULT that should be checked with the SUCCEEDED or FAILED
 *         macros after use.
 *
 *         Returns S_OK if the copy was successful.
 *
 *         Returns STRSAFE_E_INVALID_PARAMETER if the capacity cbDest
 *         is zero or larger than the maximum capacity allowed.
 *
 *         Returns STRSAFE_E_INSUFFICIENT_BUFFER if the data in pszSrc did
 *         not fit into pszDst. The data from pszSrc has been truncated
 *         to fit in pszDst and this truncated data has been null terminated
 *         and written into pszDst.
 */
#ifdef UNICODE
	#define StringCbCopy StringCbCopyW
#else
	#define StringCbCopy StringCbCopyA
#endif
HRESULT StringCbCopyA(
	__out	LPSTR pszDest,
	__in	size_t cbDest,
	__in	LPCSTR pszSrc
);
HRESULT StringCbCopyW(
	__out	LPWSTR pszDest,
	__in	size_t cbDest,
	__in	LPCWSTR pszSrc
);

/**
 * Calculates the length of psz by iterating over it until a null character
 * is reached. The null character is not counted as part of the string.
 *
 * Running time is linear in the length of the string.
 *
 * @param psz The string to calculate the length for.
 * @param cbMax Capacity of psz in bytes.
 * @param pcb The calculated length. The calculated value is undefined if
 *            the function failed.
 *
 * @return A HRESULT that should be checked with the SUCCEEDED or FAILED
 *         macros after use.
 *
 *         Returns S_OK if the length was calculated correctly.
 *
 *         Returns STRSAFE_E_INVALID_PARAMETER if the capacity cbMax
 *         is larger than the maximum capacity allowed or if a null
 *         termination is not found in psz.
 */
#ifdef UNICODE
	#define StringCbLength StringCbLengthW
#else
	#define StringCbLength StringCbLengthA
#endif
HRESULT StringCbLengthA(
	__in	LPCSTR psz,
	__in	size_t cbMax,
	__out	size_t *pcb
);
HRESULT StringCbLengthW(
	__in	LPCWSTR psz,
	__in	size_t cbMax,
	__out	size_t *pcb
);

#endif /* STRSAFE_H */
