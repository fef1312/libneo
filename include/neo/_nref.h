/** See the end of this file for copyright and license terms. */

#pragma once

#include "neo/_types.h"

/**
 * Initialize the reference counter in a structure.
 *
 * The count is initialized to 1 and can be incremented and decremented using
 * `nget` and `nput` respectively.  If the count reaches 0, the `destroy`
 * callback is invoked where the structure and all resources tied to it must
 * be released.  The reference counter must be embedded in the struct using
 * the `NREF_FIELD` macro.
 *
 * @param ptr: The `struct *` containing the `NREF_FIELD`
 * @param destroy: A callback accepting a pointer to the original struct as its
 *	only parameter and return type `void`, which will deallocate the struct
 */
#define nref_init(ptr, destroy) ({						\
	struct _neo_nref *__nref = &(ptr)->__neo_nref;				\
	__nref->_offset = offsetof(typeof(*(ptr)), __neo_nref);			\
	void (*__destroy_typechecked)(typeof(ptr)) = destroy;			\
	__nref->_destroy = (void (*)(void *))__destroy_typechecked;		\
	__nref->_count = 1;							\
})

int _neo_nget(struct _neo_nref *ref);
int _neo_nput(struct _neo_nref *ref);

/**
 * Increment the reference counter of a structure embedding `NREF_FIELD`.
 *
 * @param ptr: The `struct *` to increment the reference counter of
 * @returns The new reference count
 */
#define nget(ptr) (_neo_nget( &(ptr)->__neo_nref ))

/**
 * Decrement the reference counter of a structure embedding `NREF_FIELD`.
 *
 * If the counter reaches zero, the destroy callback passed to `nref_init`
 * is invoked.
 *
 * @param ptr: The `struct *` to decrement the reference counter of
 * @returns The new reference count
 */
#define nput(ptr) (_neo_nput( &(ptr)->__neo_nref ))

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
