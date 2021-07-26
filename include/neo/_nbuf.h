/* See the end of this file for copyright and license terms. */

#pragma once

#include "neo/_toolchain.h"
#include "neo/_types.h"

/**
 * @defgroup nbuf Buffers
 *
 * @{
 */

/**
 * @brief Create a new buffer of fixed size.
 *
 * If allocation fails or `size` is 0, an error is yeeted.
 *
 * @param size Size in bytes
 * @param err Error pointer
 * @returns The buffer, except if an error occurred
 */
nbuf_t *nbuf_create(usize size, error *err);

/**
 * @brief Create a new buffer of fixed size and copy `data` into it.
 *
 * The original pointer is neither modified nor deallocated.
 * If allocation fails, `data` is `nil`, or `size` is 0, an error is yeeted.
 *
 * @param data Raw data to fill the buffer with
 * @param size How many bytes are read from `data`, and the buffer size
 * @param err Error pointer
 * @returns The buffer, except if an error occurred
 */
nbuf_t *nbuf_from(const void *restrict data, usize size, error *err);

/**
 * @brief Create a new buffer of fixed size and copy a string into it.
 *
 * The original string is neither modified nor deallocated.
 * If allocation fails or `s` is `nil`, an error is yeeted.
 *
 * @param s String to fill the buffer with
 * @param err Error pointer
 * @returns The buffer, except if an error occurred
 */
nbuf_t *nbuf_from_str(const char *restrict s, error *err);

/**
 * @brief Create a new buffer of fixed size and copy a neo string into it.
 *
 * The original string is unmodified.
 * If allocation fails or `s` is `nil`, an error is yeeted.
 *
 * @param s Neo string to fill the buffer with
 * @param err Error pointer
 * @returns The buffer, except if an error occurred
 */
nbuf_t *nbuf_from_nstr(nstr_t *s, error *err);

/**
 * @brief Return a new copy of `buf`.
 *
 * If `buf` is `nil` or allocation fails, an error is yeeted.
 *
 * @param buf Buffer to create a copy of
 * @param err Error pointer
 * @returns A copy of `buf`, unless an error occurred
 */
nbuf_t *nbuf_clone(nbuf_t *buf, error *err);

/**
 * @brief Get the byte at the specified index.
 *
 * If `buf` is `nil` or `index` is out of bounds, an error is yeeted.
 *
 * @param buf `nbuf_t *` to get the byte from
 * @param index Byte index (counting from 0)
 * @param err Error pointer
 * @returns The byte at position `index` (as a `u8`), unless an error occurred
 */
#define nbuf_byte(buf, index, err) ({					\
	u8 __byte = 0;							\
	if (nlen(buf) <= index) {					\
		yeet(err, ERANGE, "Buffer index out of bounds");	\
	} else {							\
		neat(err);						\
		__byte = buf->_data[index];				\
	}								\
	__byte;								\
})

/**
 * @brief Iterate over every byte in a buffer.
 *
 * @param cursor A `const u8 *` to be used as an iteration cursor
 * @param buf `nbuf_t *` to iterate over
 */
#define nbuf_foreach(cursor, buf)			\
	for (cursor = &buf->_data[0];			\
	     cursor != &buf->_data[nlen(buf)];		\
	     cursor++)

/**
 * @brief Compare two buffers.
 *
 * If the first buffer is found to be greater than the second one, the return
 * value is greater than 0.\n
 * If the two buffers are equal, the return value is zero.\n
 * If the first buffer is found to be less than the second one, the return
 * value is less than 0.
 *
 * If `buf1` or `buf2` is `nil`, an error is yeeted.
 *
 * @param buf1 First buffer to compare
 * @param buf2 Second buffer to compare
 * @param err Error pointer
 * @returns The difference between the buffers, unless an error occurred
 */
int nbuf_cmp(const nbuf_t *buf1, const nbuf_t *buf2, error *err);

/**
 * @brief Determine whether two buffers are equal.
 *
 * @param buf1 First `nbuf_t *` to compare
 * @param buf2 Second `nbuf_t *` to compare
 * @param err Error pointer
 * @returns `true` if the two buffers are found to be equal, `false` if not
 */
#define nbuf_eq(buf1, buf2, err) ( (bool)(nbuf_cmp(buf1, buf2, err) == 0) )

/** @} */

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
