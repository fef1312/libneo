/** See the end of this file for copyright and license terms. */

#include <stdatomic.h>

#include "neo/_nref.h"
#include "neo/_types.h"

void _neo_nref_init(struct _neo_nref *ref, void (*destroy)(void *ptr), usize offset)
{
	ref->_destroy = destroy;
	ref->_offset = offset;
	atomic_init(&ref->_count, 1);
}

int _neo_nget(struct _neo_nref *ref)
{
	int old = atomic_fetch_add(&ref->_count, 1);
	return old + 1;
}

int _neo_nput(struct _neo_nref *ref)
{
	int old = atomic_fetch_sub(&ref->_count, 1);

	if (old == 1) {
		void *container = (void *)ref - ref->_offset;
		ref->_destroy(container);
	}

	return old - 1;
}

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
