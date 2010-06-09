/*
 * Wide character string support for the C TAP Harness by Russ Allbery.
 *
 * Copyright 2010 Jonas Sundberg <jsund@jsund.com>
 */

#ifndef TAP_WIDE_H
#define TAP_WIDE_H

#include <wchar.h>
#include <tap/basic.h>

BEGIN_DECLS

void is_wstring(const wchar_t *wanted, const wchar_t *seen, const char *format, ...)
    __attribute__((__format__(printf, 3, 4)));

END_DECLS

#endif /* TAP_WIDE_H */
