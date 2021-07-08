/** See the end of this file for copyright and license terms. */

#pragma once

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

typedef float		f32;
typedef double		f64;
typedef long double	f128;

typedef _Bool bool;

struct _neo_string {
	usize _len;
	usize _capacity;
	char *_data;
};
typedef struct _neo_string string;

struct _neo_error {
	int _number;
	string *_error;
};
typedef struct _neo_error *error;

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