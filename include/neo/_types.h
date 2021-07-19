/** See the end of this file for copyright and license terms. */

#pragma once

#include "neo/_stddef.h"

typedef __INT8_TYPE__		i8;
typedef __INT16_TYPE__		i16;
typedef __INT32_TYPE__		i32;
typedef __INT64_TYPE__		i64;

typedef __UINT8_TYPE__		u8;
typedef __UINT8_TYPE__		byte;
typedef __UINT16_TYPE__		u16;
typedef __UINT32_TYPE__		u32;
typedef __UINT64_TYPE__		u64;

typedef __SIZE_TYPE__		usize;
typedef __PTRDIFF_TYPE__	isize;

/** A single Unicode character (32 bits) */
typedef u32			nchar;

typedef float		f32;
typedef double		f64;
typedef long double	f128;

#ifdef __cplusplus
	/* TODO: This is probably not a good idea */
	#define __neo_atomic_type volatile int
#else
	typedef _Bool bool;
#	ifdef __STDC_NO_ATOMICS__
#		error "Atomic types are not implemented"
#	else
#		define __neo_atomic_type _Atomic int
#	endif
#endif

/**
 * Declare a length field in a structure.
 * This makes it compatible with the `nlen` macro.
 *
 * @param name: field name, will be of type `usize`
 */
#define NLEN_FIELD(name)				\
	union {						\
		usize name;				\
		volatile const usize __neo_nlen;	\
	}

struct _neo_nref {
	void (*_destroy)(void *);
	/** byte offset into the struct this is embedded in */
	usize _offset;
	__neo_atomic_type _count;
};
/**
 * A basic reference counter for data structures.
 * Embed this into your data structure using the `NREF_FIELD` macro, initialize
 * it using `nref_init`, and use `nget` and `nput` to increment/decrement the
 * reference counter.
 */
typedef struct _neo_nref nref_t;
#define NREF_FIELD nref_t __neo_nref

struct _neo_string {
	/* The *amount of Unicode code points*, NOT amount of bytes */
	NLEN_FIELD(_len);
	NREF_FIELD;
	/* physical size in bytes, including the four NUL terminators */
	usize _size;
	char *_data;
};
typedef struct _neo_string string;

struct _neo_error {
	string *_message;
	u32 _number;
};
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
