/** See the end of this file for copyright and license terms. */

#pragma once

#include "neo/_types.h"
#include "neo/_toolchain.h"

/**
 * Used internally for statically initializing strings created with
 * the `NSTR_DEFINE` macro.  This is written to a special data section that
 * is iterated over before program start; see `_neo_nstr_init_array` in
 * `src/string/nstr.c` for details.
 */
struct _neo_nstr_init_info {
	nstr_t **dest;
	const char *data;
};

/**
 * Statically define a neo string.
 *
 * The string will be initialized before `main` is called.
 *
 * @param name: Name of the `nstr_t *` variable to be declared
 * @param content: A `const char *` with the contents of the string
 */
#define NSTR_DEFINE(name, content)						\
	nstr_t *name = nil;							\
	__neo_section(.data.__neo.nstr_array)					\
	struct _neo_nstr_init_info __neo_nstr_init_info_##name = {		\
		.dest = &name,							\
		.data = content,						\
	}

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
nstr_t *nstr(const char *restrict s, error *err);

/**
 * Copy a regular C string to a neo string, but at most `maxsize` bytes.
 *
 * The string is copied until a NUL terminator is encountered, or until
 * `maxsize` bytes have been read.  If `maxsize` is 0, an empty string is
 * returned.  If `s` is `nil` or allocation fails, an error is yeeted.
 * Strings in libneo are reference counted, see `nget` and `nput`.
 *
 * @param s: String to convert
 * @param err: Error pointer
 * @returns The converted string, unless an error occurred
 */
nstr_t *nnstr(const char *restrict s, usize maxsize, error *err);

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
nchar nchrat(const nstr_t *s, usize index, error *err);

/**
 * Convert a signed integer to a string.
 *
 * If allocation fails or the radix is out of range, an error is yeeted.
 *
 * @param i: The integer
 * @param radix: Base of the numerical system to convert to, must be within 2~36
 * @param err: Error pointer
 * @returns The stringified integer, unless an error occurred
 */
nstr_t *i2nstr(i64 i, int radix, error *err);

/**
 * Convert an unsigned integer to a string.
 *
 * If allocation fails or the radix is out of range, an error is yeeted.
 *
 * @param u: The integer
 * @param radix: Base of the numerical system to convert to, must be within 2~36
 * @param err: Error pointer
 * @returns The stringified integer, unless an error occurred
 */
nstr_t *u2nstr(u64 u, int radix, error *err);

/**
 * Duplicate a string.
 *
 * This should never be neccessary because strings in libneo are refcounted
 * and immutable.  If `s` is `nil` or allocation fails, an error is yeeted.
 *
 * @param s: String to duplicate
 * @param err: Error pointer
 * @returns The duplicated string, unless an error occurred
 */
nstr_t *nstrdup(const nstr_t *s, error *err);

/**
 * Repeat a string `n` times and return the new string.
 *
 * If `s` is `nil` or allocation fails, an error is yeeted.
 * If `n` is 0, an empty string is returned.
 * If `n` is 1, this function behaves exactly like `nstrdup`.
 *
 * @param s: String to repeat, remains unmodified
 * @param n: Total amount of repetitions
 * @param err: Error pointer
 * @returns A new string with the repeated content, unless an error occurred
 */
nstr_t *nstrmul(const nstr_t *s, usize n, error *err);

/**
 * Create a string considting of `n` repetitions of `c`.
 *
 * If `c` is not within unicode space or allocation fails, an error is yeeted.
 * If `n` is 0, an empty string is returned.
 *
 * @param c: Character to fill the string with
 * @param n: How many characters to put into the string
 * @param err: Error pointer
 * @returns The string, unless an error occurred
 */
nstr_t *nchrmul(nchar c, usize n, error *err);

/**
 * Concatenate two strings and return the result.
 *
 * The original two strings are unmodified.
 * If any of the two strings are `nil` or allocation fails, an error is yeeted.
 *
 * @param s1: First string
 * @param s2: Second string
 * @param err: Error pointer
 * @returns A new string instance that consists of the two concatenated ones,
 *	unless an error occurred
 */
nstr_t *nstrcat(const nstr_t *s1, const nstr_t *s2, error *err);

/**
 * Compare two strings character by character.
 * The return value is negative if the first different character in `s1` comes
 * before the one in `s2`
 *
 * @param s1: First string
 * @param s2: Second string
 * @param err: Error pointer
 * @returns The difference between the two strings, unless an error occurred
 */
int nstrcmp(const nstr_t *s1, const nstr_t *s2, error *err);

/**
 * Determine whether two strings are exactly equal.
 * If either of the two string are `nil` or acquiring a lock on them fails,
 * an error is yeeted.
 *
 * @param s1: First `nstr_t *`
 * @param s2: Second `nstr_t *`
 * @param err: Error pointer
 * @returns Whether the two strings are equal, unless an error occurred
 */
#define nstreq(s1, s2, err) ( (bool)(nstrcmp(s1, s2, err) == 0) )

/**
 * Prepend fill characters to a string to make it a specific length, and return
 * a new string with the result.  The original string is unmodified.
 * If the string is already longer than the desired width or allocation fails,
 * an error is yeeted.
 *
 * @param s: String to expand
 * @param length: Desired length of the new string
 * @param fill: Character to fill the space with
 * @param err: Error pointer
 * @returns The new padded string
 */
nstr_t *leftpad(const nstr_t *s, usize length, nchar fill, error *err);

/**
 * Iterate over each character in a string.
 *
 * @param cursor: `nchar *` to store the current character in
 * @param nstr: `nstr_t *` to iterate over
 * @param err: Error pointer; the loop will terminate early if an uncaught
 *	error occurred
 */
#define nstr_foreach(cursor, nstr, err)						\
	for (const char *__pos =						\
	         (nstr)->_data + utf8_to_nchr(cursor, (nstr)->_data, err);	\
	     /* errput sets the error number to 0xffffffff, thus number + 1 */	\
	     *__pos != '\0' && (err) != nil && (err)->_number + 1 < 2;		\
	     __pos += utf8_to_nchr(cursor, __pos, err))

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
