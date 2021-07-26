/* See the end of this file for copyright and license terms. */

#pragma once

#include "neo/_stddef.h"

/**
 * @defgroup types Primitive Types
 *
 * @{
 */

/** @brief Signed 8-bit integer. */
typedef __INT8_TYPE__		i8;
/** @brief Signed 16-bit integer. */
typedef __INT16_TYPE__		i16;
/** @brief Signed 32-bit integer. */
typedef __INT32_TYPE__		i32;
/** @brief Signed 64-bit integer. */
typedef __INT64_TYPE__		i64;

/** @brief Unsigned 8-bit integer. */
typedef __UINT8_TYPE__		u8;
/** @brief Alias for @a `u8`. */
typedef __UINT8_TYPE__		byte;
/** @brief Unsigned 16-bit integer. */
typedef __UINT16_TYPE__		u16;
/** @brief Unsigned 32-bit integer. */
typedef __UINT32_TYPE__		u32;
/** @brief Unsigned 64-bit integer. */
typedef __UINT64_TYPE__		u64;

/** @brief Platform-dependent unsigned integer for storing sizes. */
typedef __SIZE_TYPE__		usize;
/** @brief Platform-dependent signed integer for storing sizes. */
typedef __PTRDIFF_TYPE__	isize;

/** @brief A single Unicode character (32 bits). */
typedef u32			nchar;

/** @brief Single precision (32-bit) floating-point number. */
typedef float		f32;
/** @brief Double precision (64-bit) floating-point number. */
typedef double		f64;

/** @} */

#ifdef __cplusplus
	/* TODO: This is probably not a good idea */
#	define __neo_atomic_type volatile int
#else
#	include <stdbool.h>
#	ifdef __STDC_NO_ATOMICS__
#		error "Atomic types are not implemented"
#	else
#		define __neo_atomic_type _Atomic int
#	endif
#endif

/**
 * @brief Declare a length field in a structure.
 * This makes it compatible with the `nlen()` macro.
 *
 * @param name field name, will be of type `usize`
 *
 * @ingroup stddef
 */
#define NLEN_FIELD(name)				\
	union {						\
		usize name;				\
		volatile const usize __neo_nlen;	\
	}

/** @private */
struct _neo_nref {
	void (*_destroy)(void *);
	/** byte offset into the struct this is embedded in */
	usize _offset;
	__neo_atomic_type _count;
};
/**
 * @brief A basic reference counter for data structures.
 *
 * Embed this into your data structure using the `NREF_FIELD` macro, initialize
 * it using `nref_init`, and use `nget` and `nput` to increment/decrement the
 * reference counter.
 *
 * @ingroup nref
 */
typedef struct _neo_nref nref_t;
/**
 * @brief Embed this macro into your structure to enable refcounting.
 *
 * The reference counter must be initialized using `nref_init` and may be
 * incremented and decremented using `nget` and `nput` respectively.
 *
 * @ingroup stddef
 */
#define NREF_FIELD nref_t __neo_nref

/** @private */
struct _neo_nbuf {
	NREF_FIELD;
	NLEN_FIELD(_size);
	/**
	 * If this buffer was cloned or converted from a string, this points to
	 * the original structure's refcounter.  Otherwise, it is nil.
	 */
	nref_t *_borrow;
	const byte *_data;
};
/**
 * @brief An immutable, refcounted buffer.
 *
 * @ingroup nbuf
 */
typedef struct _neo_nbuf nbuf_t;

/** @private */
struct _neo_nstr {
	/* The *amount of Unicode code points*, NOT amount of bytes */
	NLEN_FIELD(_len);
	NREF_FIELD;
	/* physical size in bytes, including the four NUL terminators */
	usize _size;
	/**
	 * If this string was cloned or converted from a buffer, this points to
	 * the original structure's refcounter.  Otherwise, it is nil.
	 */
	nref_t *_borrow;
	const char *_data;
};
/**
 * @brief An immutable, refcounted UTF-8 string.
 *
 * @ingroup nstr
 */
typedef struct _neo_nstr nstr_t;

/** @private */
struct _neo_error {
	nstr_t *_message;
	u32 _number;
};
/**
 * @brief The generic error type.
 *
 * @ingroup error
 */
typedef struct _neo_error error;

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
