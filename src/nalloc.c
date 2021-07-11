/** See the end of this file for copyright and license terms. */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "neo/_error.h"
#include "neo/_nalloc.h"
#include "neo/_stddef.h"
#include "neo/_types.h"

void nfree(void *ptr)
{
	free(ptr);
}

/*
 * the error messages are nil if malloc fails because if we are running low
 * on memory, vsnprintf (which yeet() uses) is probably gonna fail as well
 */

void *nalloc(usize size, error *err)
{
	if (size == 0) {
		yeet(err, EINVAL, "Requested memory size is 0");
		return nil;
	}

	void *ptr = malloc(size);

	if (!ptr)
		yeet(err, ENOMEM, nil);
	else
		neat(err);

	return ptr;
}

void *zalloc(usize size, error *err)
{
	if (size == 0) {
		yeet(err, EINVAL, "Requested memory size is 0");
		return nil;
	}

	void *ptr = calloc(1, size);

	if (!ptr)
		yeet(err, ENOMEM, nil);
	else
		neat(err);

	return ptr;
}

void *nrealloc(void *ptr, usize newsz, error *err)
{
	void *ret = realloc(ptr, newsz);

	if (!ret) {
		if (newsz == 0) {
			ret = nil;
			neat(err);
		} else {
			ret = ptr;
			yeet(err, ENOMEM, nil);
		}
	} else {
		neat(err);
	}

	return ret;
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
