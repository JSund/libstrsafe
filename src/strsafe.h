/*
 * Copyright (c) 2010, Jonas Sundberg <jsund@jsund.com>
 *
 * This software has been released under the terms of the ISC license. For
 * details, see the LICENSE file.
 *
 * strsafe.h provides the public interface to the libstrsafe functions.
 * For more information on libstrsafe, see the README file.
 */

#ifndef STRSAFE_H
#define STRSAFE_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

/* Enable both versions of the UNICODE macro. */

#ifdef _UNICODE
	#ifndef UNICODE
		#define UNICODE
	#endif
#endif

#ifdef UNICODE
	#ifndef _UNICODE
		#define _UNICODE
	#endif
#endif

/**
 * The result of a function call. All function calls in libstrsafe returns
 * an HRESULT, a value representing the result of the function call.
 * This can later be checked with the SUCCEEDED or FAILED macros.
 */
typedef uint32_t HRESULT;

/**
 * Function ran successfully. No errors occured during execution.
 */
#define S_OK (uint32_t)0x00000000

/**
 * End of file was reached. During execution, the end of an input file
 * or stream was reached.
 */
#define STRSAFE_E_END_OF_FILE (uint32_t)0x00000001

/**
 * An invalid parameter was sent. One or more of the input parameters
 * was invalid.
 */
#define STRSAFE_E_INVALID_PARAMETER (uint32_t)0x00000002

/**
 * An output buffer was too small. An output buffer used by the function
 * was too small to contain the data that was supposed to be written
 * into it.
 *
 * The data written into the buffer was truncated unless
 * STRSAFE_NO_TRUNCATION was set.
 */
#define STRSAFE_E_INSUFFICIENT_BUFFER (uint32_t)0x00000004

/*
 * Flags to set in parameters to the extended functions.
 */
#define STRSAFE_IGNORE_NULLS (uint32_t)0x00000100
#define STRSAFE_FILL_BEHIND_NULL (uint32_t)0x00000200
#define STRSAFE_FILL_ON_FAILURE (uint32_t)0x00000400
#define STRSAFE_NULL_ON_FAILURE (uint32_t)0x00000800
#define STRSAFE_NO_TRUNCATION (uint32_t)0x00001000

/**
 * The maximum allowed buffer capacity. It specifies the maximum number
 * of characters that a buffer is allowed to contain.
 */
#define STRSAFE_MAX_CCH (size_t)0x7fffffff /* 2^31 - 1 or 2,147,483,647 */

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

/**
 * A DWORD is used to set various arguments to extended versions of
 * functions.
 */
typedef uint32_t DWORD;

/**
 * A single character.
 */
#ifdef UNICODE
	typedef wchar_t TCHAR;
#else
	typedef char TCHAR;
#endif

/**
 * A pointer to a string buffer.
 */
typedef TCHAR * LPTSTR;
typedef wchar_t * LPWSTR;
typedef char * LPSTR;

/**
 * A pointer to an immutable string buffer.
 */
typedef const LPTSTR LPCTSTR;
typedef const LPWSTR LPCWSTR;
typedef const LPSTR LPCSTR;

/**
 * A macro that converts string literals to either C strings or Unicode
 * strings depending on whether UNICODE is set or not.
 */
#ifdef UNICODE
	#define TEXT(string) L##string
#else
	#define TEXT(string) string
#endif

#ifdef UNICODE
	#define StringCchCat StringCchCatW
#else
	#define StringCchCat StringCchCatA
#endif
HRESULT StringCchCatA(
	LPSTR pszDest,
	size_t cchDest,
	LPCSTR pszSrc
);
HRESULT StringCchCatW(
	LPWSTR pszDest,
	size_t cchDest,
	LPCWSTR pszSrc
);

#ifdef UNICODE
	#define StringCchCatEx StringCchCatExW
#else
	#define StringCchCatEx StringCchCatExA
#endif
HRESULT StringCchCatExA(
	LPSTR pszDest,
	size_t cchDest,
	LPCSTR pszSrc,
	LPSTR * ppszDestEnd,
	size_t * pcchRemaining,
	DWORD dwFlags
);
HRESULT StringCchCatExW(
	LPWSTR pszDest,
	size_t cchDest,
	LPCWSTR pszSrc,
	LPWSTR * ppszDestEnd,
	size_t * pcchRemaining,
	DWORD dwFlags
);

#ifdef UNICODE
	#define StringCchCatN StringCchCatNW
#else
	#define StringCchCatN StringCchCatNA
#endif
HRESULT StringCchCatNA(
	LPSTR pszDest,
	size_t cchDest,
	LPCSTR pszSrc,
	size_t cchMaxAppend
);
HRESULT StringCchCatNW(
	LPWSTR pszDest,
	size_t cchDest,
	LPCWSTR pszSrc,
	size_t cchMaxAppend
);

#ifdef UNICODE
	#define StringCchCatNEx StringCchCatNExW
#else
	#define StringCchCatNEx StringCchCatNExA
#endif
HRESULT StringCchCatNExA(
	LPSTR pszDest,
	size_t cchDest,
	LPCSTR pszSrc,
	size_t cchMaxAppend,
	LPSTR * ppszDestEnd,
	size_t * pcchRemaining,
	DWORD dwFlags
);
HRESULT StringCchCatNExW(
	LPWSTR pszDest,
	size_t cchDest,
	LPCWSTR pszSrc,
	size_t cchMaxAppend,
	LPWSTR * ppszDestEnd,
	size_t * pcchRemaining,
	DWORD dwFlags
);

#ifdef UNICODE
	#define StringCchCopy StringCchCopyW
#else
	#define StringCchCopy StringCchCopyA
#endif
HRESULT StringCchCopyA(
	LPSTR pszDest,
	size_t cchDest,
	LPCSTR pszSrc
);
HRESULT StringCchCopyW(
	LPWSTR pszDest,
	size_t cchDest,
	LPCWSTR pszSrc
);

#ifdef UNICODE
	#define StringCchCopyEx StringCchCopyExW
#else
	#define StringCchCopyEx StringCchCopyExA
#endif
HRESULT StringCchCopyExA(
	LPSTR pszDest,
	size_t cchDest,
	LPCSTR pszSrc,
	LPSTR *ppszDestEnd,
	size_t * pcchRemaining,
	DWORD dwFlags
);
HRESULT StringCchCopyExW(
	LPWSTR pszDest,
	size_t cchDest,
	LPCWSTR pszSrc,
	LPWSTR * ppszDestEnd,
	size_t * pcchRemaining,
	DWORD dwFlags
);

#ifdef UNICODE
	#define StringCchCopyN StringCchCopyNW
#else
	#define StringCchCopyN StringCchCopyNA
#endif
HRESULT StringCchCopyNA(
	LPSTR pszDest,
	size_t cchDest,
	LPCSTR pszSrc,
	size_t cchSrc
);
HRESULT StringCchCopyNW(
	LPWSTR pszDest,
	size_t cchDest,
	LPCWSTR pszSrc,
	size_t cchSrc
);

#ifdef UNICODE
	#define StringCchCopyNEx StringCchCopyNExW
#else
	#define StringCchCopyNEx StringCchCopyNExA
#endif
HRESULT StringCchCopyNExA(
	LPSTR pszDest,
	size_t cchDest,
	LPCSTR pszSrc,
	size_t cchSrc,
	LPSTR * ppszDestEnd,
	size_t * pcchRemaining,
	DWORD dwFlags
);
HRESULT StringCchCopyNExW(
	LPWSTR pszDest,
	size_t cchDest,
	LPCWSTR pszSrc,
	size_t cchSrc,
	LPWSTR * ppszDestEnd,
	size_t * pcchRemaining,
	DWORD dwFlags
);

#ifdef UNICODE
	#define StringCchGets StringCchGetsW
#else
	#define StringCchGets StringCchGetsA
#endif
HRESULT StringCchGetsA(
	LPSTR pszDest,
	size_t cchDest
);
HRESULT StringCchGetsW(
	LPWSTR pszDest,
	size_t cchDest
);

#ifdef UNICODE
	#define StringCchGetsEx StringCchGetsExW
#else
	#define StringCchGetsEx StringCchGetsExA
#endif
HRESULT StringCchGetsExA(
	LPSTR pszDest,
	size_t cchDest,
	LPSTR * ppszDestEnd,
	size_t * pcchRemaining,
	DWORD dwFlags
);
HRESULT StringCchGetsExW(
	LPWSTR pszDest,
	size_t cchDest,
	LPWSTR * ppszDestEnd,
	size_t * pcchRemaining,
	DWORD dwFlags
);

#ifdef UNICODE
	#define StringCchPrintf StringCchPrintfW
#else
	#define StringCchPrintf StringCchPrintfA
#endif
HRESULT StringCchPrintfA(
	LPSTR pszDest,
	size_t cchDest,
	LPCSTR pszFormat,
	...
);
HRESULT StringCchPrintfW(
	LPWSTR pszDest,
	size_t cchDest,
	LPCWSTR pszFormat,
	...
);

#ifdef UNICODE
	#define StringCchPrintfEx StringCchPrintfExW
#else
	#define StringCchPrintfEx StringCchPrintfExA
#endif
HRESULT StringCchPrintfExA(
	LPSTR pszDest,
	size_t cchDest,
	LPSTR * ppszDestEnd,
	size_t * pcchRemaining,
	DWORD dwFlags,
	LPCSTR pszFormat,
	...
);
HRESULT StringCchPrintfExW(
	LPWSTR pszDest,
	size_t cchDest,
	LPWSTR * ppszDestEnd,
	size_t * pcchRemaining,
	DWORD dwFlags,
	LPCWSTR pszFormat,
	...
);

#ifdef UNICODE
	#define StringCchVPrintf StringCchVPrintfW
#else
	#define StringCchVPrintf StringCchVPrintfA
#endif
HRESULT StringCchVPrintfA(
	LPSTR pszDest,
	size_t cchDest,
	LPCSTR pszFormat,
	va_list argList
);
HRESULT StringCchVPrintfW(
	LPWSTR pszDest,
	size_t cchDest,
	LPCWSTR pszFormat,
	va_list argList
);

#ifdef UNICODE
	#define StringCchPrintExf StringCchVPrintfExW
#else
	#define StringCchPrintExf StringCchVPrintfExA
#endif
HRESULT StringCchVPrintfExA(
	LPSTR pszDest,
	size_t cchDest,
	LPSTR * ppszDestEnd,
	size_t * pcchRemaining,
	DWORD dwFlags,
	LPCSTR pszFormat,
	va_list argList
);
HRESULT StringCchVPrintfExW(
	LPWSTR pszDest,
	size_t cchDest,
	LPWSTR * ppszDestEnd,
	size_t * pcchRemaining,
	DWORD dwFlags,
	LPCWSTR pszFormat,
	va_list argList
);

#ifdef UNICODE
	#define StringCchLength StringCchLengthW
#else
	#define StringCchLength StringCchLengthA
#endif
HRESULT StringCchLengthA(
	LPCSTR psz,
	size_t cchMax,
	size_t * pcch
);
HRESULT StringCchLengthW(
	LPCWSTR psz,
	size_t cchMax,
	size_t * pcch
);

#ifdef UNICODE
	#define StringCbCat StringCbCatW
#else
	#define StringCbCat StringCbCatA
#endif
HRESULT StringCbCatA(
	LPSTR pszDest,
	size_t cbDest,
	LPCSTR pszSrc
);
HRESULT StringCbCatW(
	LPWSTR pszDest,
	size_t cbDest,
	LPCWSTR pszSrc
);

#ifdef UNICODE
	#define StringCbCatEx StringCbCatExW
#else
	#define StringCbCatEx StringCbCatExA
#endif
HRESULT StringCbCatExA(
	LPSTR pszDest,
	size_t cbDest,
	LPCSTR pszSrc,
	LPSTR * ppszDestEnd,
	size_t * pcbRemaining,
	DWORD dwFlags
);
HRESULT StringCbCatExW(
	LPWSTR pszDest,
	size_t cbDest,
	LPCWSTR pszSrc,
	LPWSTR * ppszDestEnd,
	size_t * pcbRemaining,
	DWORD dwFlags
);

#ifdef UNICODE
	#define StringCbCatN StringCbCatNW
#else
	#define StringCbCatN StringCbCatNA
#endif
HRESULT StringCbCatNA(
	LPSTR pszDest,
	size_t cbDest,
	LPCSTR pszSrc,
	size_t cbMaxAppend
);
HRESULT StringCbCatNW(
	LPWSTR pszDest,
	size_t cbDest,
	LPCWSTR pszSrc,
	size_t cbMaxAppend
);

#ifdef UNICODE
	#define StringCbCatNEx StringCbCatNExW
#else
	#define StringCbCatNEx StringCbCatNExA
#endif
HRESULT StringCbCatNExA(
	LPSTR pszDest,
	size_t cbDest,
	LPCSTR pszSrc,
	size_t cbMaxAppend,
	LPSTR * ppszDestEnd,
	size_t * pcbRemaining,
	DWORD dwFlags
);
HRESULT StringCbCatNExW(
	LPWSTR pszDest,
	size_t cbDest,
	LPCWSTR pszSrc,
	size_t cbMaxAppend,
	LPWSTR * ppszDestEnd,
	size_t * pcbRemaining,
	DWORD dwFlags
);

#ifdef UNICODE
	#define StringCbCopy StringCbCopyW
#else
	#define StringCbCopy StringCbCopyA
#endif
HRESULT StringCbCopyA(
	LPSTR pszDest,
	size_t cbDest,
	LPCSTR pszSrc
);
HRESULT StringCbCopyW(
	LPWSTR pszDest,
	size_t cbDest,
	LPCWSTR pszSrc
);

#ifdef UNICODE
	#define StringCbCopyEx StringCbCopyExW
#else
	#define StringCbCopyEx StringCbCopyExA
#endif
HRESULT StringCbCopyExA(
	LPSTR pszDest,
	size_t cbDest,
	LPCSTR pszSrc,
	LPSTR *ppszDestEnd,
	size_t * pcbRemaining,
	DWORD dwFlags
);
HRESULT StringCbCopyExW(
	LPWSTR pszDest,
	size_t cbDest,
	LPCWSTR pszSrc,
	LPWSTR * ppszDestEnd,
	size_t * pcbRemaining,
	DWORD dwFlags
);

#ifdef UNICODE
	#define StringCbCopyN StringCbCopyNW
#else
	#define StringCbCopyN StringCbCopyNA
#endif
HRESULT StringCbCopyNA(
	LPSTR pszDest,
	size_t cbDest,
	LPCSTR pszSrc,
	size_t cbSrc
);
HRESULT StringCbCopyNW(
	LPWSTR pszDest,
	size_t cbDest,
	LPCWSTR pszSrc,
	size_t cbSrc
);

#ifdef UNICODE
	#define StringCbCopyNEx StringCbCopyNExW
#else
	#define StringCbCopyNEx StringCbCopyNExA
#endif
HRESULT StringCbCopyNExA(
	LPSTR pszDest,
	size_t cbDest,
	LPCSTR pszSrc,
	size_t cbSrc,
	LPSTR * ppszDestEnd,
	size_t * pcbRemaining,
	DWORD dwFlags
);
HRESULT StringCbCopyNExW(
	LPWSTR pszDest,
	size_t cbDest,
	LPCWSTR pszSrc,
	size_t cbSrc,
	LPWSTR * ppszDestEnd,
	size_t * pcbRemaining,
	DWORD dwFlags
);

#ifdef UNICODE
	#define StringCbGets StringCbGetsW
#else
	#define StringCbGets StringCbGetsA
#endif
HRESULT StringCbGetsA(
	LPSTR pszDest,
	size_t cbDest
);
HRESULT StringCbGetsW(
	LPWSTR pszDest,
	size_t cbDest
);

#ifdef UNICODE
	#define StringCbGetsEx StringCbGetsExW
#else
	#define StringCbGetsEx StringCbGetsExA
#endif
HRESULT StringCbGetsExA(
	LPSTR pszDest,
	size_t cbDest,
	LPSTR * ppszDestEnd,
	size_t * pcbRemaining,
	DWORD dwFlags
);
HRESULT StringCbGetsExW(
	LPWSTR pszDest,
	size_t cbDest,
	LPWSTR * ppszDestEnd,
	size_t * pcbRemaining,
	DWORD dwFlags
);

#ifdef UNICODE
	#define StringCbPrintf StringCbPrintfW
#else
	#define StringCbPrintf StringCbPrintfA
#endif
HRESULT StringCbPrintfA(
	LPSTR pszDest,
	size_t cbDest,
	LPCSTR pszFormat,
	...
);
HRESULT StringCbPrintfW(
	LPWSTR pszDest,
	size_t cbDest,
	LPCWSTR pszFormat,
	...
);

#ifdef UNICODE
	#define StringCbPrintfEx StringCbPrintfExW
#else
	#define StringCbPrintfEx StringCbPrintfExA
#endif
HRESULT StringCbPrintfExA(
	LPSTR pszDest,
	size_t cbDest,
	LPSTR * ppszDestEnd,
	size_t * pcbRemaining,
	DWORD dwFlags,
	LPCSTR pszFormat,
	...
);
HRESULT StringCbPrintfExW(
	LPWSTR pszDest,
	size_t cbDest,
	LPWSTR * ppszDestEnd,
	size_t * pcbRemaining,
	DWORD dwFlags,
	LPCWSTR pszFormat,
	...
);

#ifdef UNICODE
	#define StringCbVPrintf StringCbVPrintfW
#else
	#define StringCbVPrintf StringCbVPrintfA
#endif
HRESULT StringCbVPrintfA(
	LPSTR pszDest,
	size_t cbDest,
	LPCSTR pszFormat,
	va_list argList
);
HRESULT StringCbVPrintfW(
	LPWSTR pszDest,
	size_t cbDest,
	LPCWSTR pszFormat,
	va_list argList
);

#ifdef UNICODE
	#define StringCbPrintExf StringCbVPrintfExW
#else
	#define StringCbPrintExf StringCbVPrintfExA
#endif
HRESULT StringCbVPrintfExA(
	LPSTR pszDest,
	size_t cbDest,
	LPSTR * ppszDestEnd,
	size_t * pcbRemaining,
	DWORD dwFlags,
	LPCSTR pszFormat,
	va_list argList
);
HRESULT StringCbVPrintfExW(
	LPWSTR pszDest,
	size_t cbDest,
	LPWSTR * ppszDestEnd,
	size_t * pcbRemaining,
	DWORD dwFlags,
	LPCWSTR pszFormat,
	va_list argList
);

#ifdef UNICODE
	#define StringCbLength StringCbLengthW
#else
	#define StringCbLength StringCbLengthA
#endif
HRESULT StringCbLengthA(
	LPCSTR psz,
	size_t cbMax,
	size_t *pcb
);
HRESULT StringCbLengthW(
	LPCWSTR psz,
	size_t cbMax,
	size_t *pcb
);

#endif /* STRSAFE_H */
