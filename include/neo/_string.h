/** See the end of this file for copyright and license terms. */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "neo/_types.h"

/**
 * Copy a regular C string to a neo string.
 *
 * `s` must be NUL terminated, and be deallocated manually if no longer needed.
 * If `s` is `nil` or allocation fails, an error is yeeted.  Strings in libneo
 * are reference counted, see `nget` and `nput`.
 *
 * @param s: String to convert
 * @param err: Error pointer
 * @returns The converted string, unless an error occurred
 */
string *nstr(const char *restrict s, error *err);

/**
 * Get the Unicode code point in a string at the specified index.
 *
 * If the string is `nil` or the index is out of range, an error is yeeted.
 *
 * @param s: String to get a character from
 * @param index: Character index, starting from 0
 * @param err: Error pointer
 * @returns The Unicode code point at the specified index,
 *	unless an error occurred
 */
nchar nchrat(string *s, usize index, error *err);

#ifdef __cplusplus
}; /* extern "C" */
#endif

/*
 * This file is part of libneo.
 * Copyright (c) 2021 Fefie <owo@fef.moe>.
 *
 * libneo is non-violent software: you may only use, redistribute,
 * and/or modify it under the terms of the CNPLv6+ as found in
 * the LICENSE file in the source code root directory or at
 * <https://git.pixie.town/thufie/CNPL>.
 *
 * libneo comes with ABSOLUTELY NO WARRANTY, to the extent
 * permitted by applicable law.  See the CNPLv6+ for details.
 */
