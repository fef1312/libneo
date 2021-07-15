/** See the end of this file for copyright and license terms. */

#pragma once

#include "neo/_types.h"

#ifdef __cplusplus
#	define nil nullptr
#else
#	define nil ((void *)0)
#endif

#if !defined(__cplusplus) && !defined(true)
#	define true ((bool)1)
#endif
#if !defined(__cplusplus) && !defined(false)
#	define false ((bool)0)
#endif

#ifndef offsetof
#	define offsetof(type, member) __builtin_offsetof(type, member)
#endif

#ifndef typeof
#	define typeof(expr) __typeof(expr)
#endif

/** Get the absolute (non negative) value of an integer */
#define nabs(n) ({								\
	/* n is an expression, not a variable, evaluate it only once */		\
	typeof(n) __neo_local_n = (n);						\
	__neo_local_n < 0 ? -__neo_local_n : __neo_local_n;			\
})

/**
 * Declare a length field in a structure.
 * This makes it compatible with the `nlen` macro.
 *
 * @param name: field name, will be of type `usize`
 */
#define NLEN_FIELD(name)		\
	union {				\
		usize name;		\
		const usize __neo_nlen;	\
	}

/**
 * Quickly get the length (as a `const usize`) of any libneo data structure
 * that supports it.  This includes strings, buffers, lists, and more.
 */
#define nlen(thing) ((thing)->__neo_nlen)

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
