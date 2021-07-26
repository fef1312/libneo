/* See the end of this file for copyright and license terms. */

#pragma once

#include "neo/_types.h"

void _neo_nref_init(struct _neo_nref *ref, void (*destroy)(void *ptr), usize offset);

int _neo_nget(struct _neo_nref *ref);
int _neo_nput(struct _neo_nref *ref);

/**
 * @defgroup nref Reference Counting
 *
 * @{
 */

/**
 * @brief Initialize the reference counter in a structure.
 *
 * The count is initialized to 1 and can be incremented and decremented using
 * `nget()` and `nput()` respectively.  If the count reaches 0, the `destroy`
 * callback is invoked where the structure and all resources tied to it must
 * be released.  The reference counter must be embedded in the struct using
 * the `NREF_FIELD` macro.
 *
 * @param ptr The `struct *` containing the `NREF_FIELD`
 * @param destroy A callback accepting a pointer to the original struct as its
 *	only parameter and return type `void`, which will deallocate the struct
 */
#define nref_init(ptr, destroy) ({						\
	void (*__destroy_typechecked)(typeof(ptr)) = (destroy);			\
	_neo_nref_init(&(ptr)->__neo_nref,					\
		       (void (*)(void *))__destroy_typechecked,			\
		       offsetof(typeof(*(ptr)), __neo_nref));			\
})

/**
 * @brief Increment the reference counter of a structure embedding `NREF_FIELD`.
 *
 * @param ptr The `struct *` to increment the reference counter of
 */
#define nget(ptr) ((void)_neo_nget( &(ptr)->__neo_nref ))

/**
 * @brief Decrement the reference counter of a structure embedding `NREF_FIELD`.
 *
 * If the counter reaches zero, the destroy callback passed to `nref_init`
 * is invoked and the pointer is set to `nil` to prevent any further usage.
 *
 * @param ptr The `struct *` to decrement the reference counter of
 */
#define nput(ptr) ({					\
	if (_neo_nput(&(ptr)->__neo_nref) == 0)		\
		ptr = nil;				\
})

/**
 * @brief Return the current reference count of a structure embedding `NREF_FIELD`.
 * You usually shouldn't need this though.
 *
 * @param ptr The `struct *` embedding `NREF_FIELD`
 * @returns The structure's current refcount value as a `const int`
 */
#define nref_count(ptr) ((const int)(ptr)->__neo_nref._count)

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
