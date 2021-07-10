/** See the end of this file for copyright and license terms. */

#include "neo/_nref.h"
#include "neo/_types.h"

int _neo_nget(struct _neo_nref *ref)
{
	return ++ref->_count;
}

int _neo_nput(struct _neo_nref *ref)
{
	int count = --ref->_count;

	if (count == 0) {
		void *container = (void *)ref - ref->_offset;
		ref->_destroy(container);
	}

	return count;
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
