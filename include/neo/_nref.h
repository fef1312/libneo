/** See the end of this file for copyright and license terms. */

#pragma once

#include "neo/_types.h"

#define nref_init(ptr, destroy) ({						\
	(ptr)->__neo_nref._offset = offsetof(typeof(*(ptr)), __neo_nref);	\
	void (*__destroy_typechecked)(typeof(ptr)) = destroy;			\
	(ptr)->__neo_nref._destroy = (void (*)(void *))__destroy_typechecked;	\
	(ptr)->__neo_nref._count = 1;						\
})

int _neo_nget(struct _neo_nref *ref);
int _neo_nput(struct _neo_nref *ref);

#define nget(thing) (_neo_nget( &(thing)->__neo_nref ))
#define nput(thing) (_neo_nput( &(thing)->__neo_nref ))

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
