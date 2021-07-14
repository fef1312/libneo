/** See the end of this file for copyright and license terms. */

#include <errno.h>
#include <string.h>

#include "neo/_error.h"
#include "neo/_nref.h"
#include "neo/_stddef.h"
#include "neo/_string.h"
#include "neo/_types.h"

int nstrcmp(const string *s1, const string *s2, error *err)
{
	if (s1 == nil) {
		yeet(err, EFAULT, "First string is nil");
		return 0;
	}
	if (s2 == nil) {
		yeet(err, EFAULT, "Second string is nil");
		return 0;
	}

	int ret;

	if (nlen(s1) > nlen(s2))
		ret = 1;
	else if (nlen(s1) < nlen(s2))
		ret = -1;
	else
		ret = strcmp(s1->_data, s2->_data);

	neat(err);
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
