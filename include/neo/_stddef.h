/* See the end of this file for copyright and license terms. */

#pragma once

#include "neo/_types.h"

/**
 * @defgroup stddef Core Macros
 *
 * @{
 */

#ifdef __cplusplus
#	define nil nullptr
#else
#	define nil ((void *)0)
#endif

#ifndef offsetof
#	define offsetof(type, member) __builtin_offsetof(type, member)
#endif

#ifndef typeof
#	define typeof(expr) __typeof(expr)
#endif

/** @brief Get the absolute (non negative) value of an integer */
#define nabs(n) ({								\
	/* n is an expression, not a variable, evaluate it only once */		\
	typeof(n) __neo_local_n = (n);						\
	__neo_local_n < 0 ? -__neo_local_n : __neo_local_n;			\
})

#define nmax(x1, x2) ({			\
	typeof(x1) __x1 = (x1);		\
	typeof(x2) __x2 = (x2);		\
	__x1 > __x2 ? __x1 : __x2;	\
})

#define nmin(x1, x2) ({			\
	typeof(x1) __x1 = (x1);		\
	typeof(x2) __x2 = (x2);		\
	__x1 < __x2 ? __x1 : x2;	\
})

/**
 * @brief Get the length of a data structure embedding `NLEN_FIELD`.
 *
 * Quickly get the length (as in amount of items, not bytes) of any libneo data
 * structure that supports it.  This includes strings, buffers, lists, and more.
 *
 * @param thing Thing to get the length of
 * @returns The length as a `const usize`
 */
#define nlen(thing) ((thing)->__neo_nlen)

/* @} */

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
