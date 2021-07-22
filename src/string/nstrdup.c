/** See the end of this file for copyright and license terms. */

#include <errno.h>

#include "neo/_error.h"
#include "neo/_nalloc.h"
#include "neo/_nref.h"
#include "neo/_nstr.h"
#include "neo/_types.h"

nstr_t *nstrdup(nstr_t *s, error *err)
{
	if (s == nil) {
		yeet(err, EFAULT, "String is nil");
		return nil;
	}

	nstr_t *copy = nalloc(sizeof(*copy), err);
	catch(err) {
		return nil;
	}

	nget(s);

	copy->_len = s->_len;
	copy->_size = s->_size;
	copy->_borrow = &s->__neo_nref;
	copy->_data = s->_data;
	nref_init(copy, _neo_nstr_destroy);
	return copy;
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
