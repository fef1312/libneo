/** See the end of this file for copyright and license terms. */

#include <errno.h>

#include "neo/_error.h"
#include "neo/_string.h"
#include "neo/_types.h"

string *nstrdup(const string *s, error *err)
{
	if (s == nil) {
		yeet(err, EFAULT, "String is nil");
		return nil;
	}

	return nstr(s->_data, err);
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