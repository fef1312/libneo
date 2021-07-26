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
	/** @brief Null pointer. */
#	define nil ((void *)0)
#endif

#ifndef offsetof
	/**
	 * @brief Get the byte offset of a member within a struct.
	 *
	 * @param type Type of the structure
	 * @param member Name of the member within the struct
	 * @returns The byte offset of `member` within `type`
	 */
#	define offsetof(type, member) __builtin_offsetof(type, member)
#endif

#ifndef typeof
	/**
	 * @brief Get the type an expression evaluates to (for generic macros).
	 *
	 * @param expr Expression to get the type of
	 * @returns The type, can be used for casting or declarations
	 */
#	define typeof(expr) __typeof(expr)
#endif

/**
 * @brief Get the absolute (non negative) value of an integer.
 *
 * @param n The integer
 * @returns The absolute value
 */
#define nabs(n) ({			\
	typeof(n) __n = (n);		\
	__n < 0 ? -__n : __n;		\
})

/**
 * @brief Get the maximum value of two integer expressions.
 *
 * @param x1 First expression
 * @param x2 Second expression
 * @returns The bigger value
 */
#define nmax(x1, x2) ({			\
	typeof(x1) __x1 = (x1);		\
	typeof(x2) __x2 = (x2);		\
	__x1 > __x2 ? __x1 : __x2;	\
})

/**
 * @brief Get the minimum value of two integer expressions.
 *
 * @param x1 First expression
 * @param x2 Second expression
 * @returns The smaller value
 */
#define nmin(x1, x2) ({			\
	typeof(x1) __x1 = (x1);		\
	typeof(x2) __x2 = (x2);		\
	__x1 < __x2 ? __x1 : __x2;	\
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
