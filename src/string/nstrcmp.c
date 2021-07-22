/** See the end of this file for copyright and license terms. */

#include <errno.h>
#include <string.h>

#include "neo/_error.h"
#include "neo/_nref.h"
#include "neo/_nstr.h"
#include "neo/_stddef.h"
#include "neo/_types.h"

int nstrcmp(const nstr_t *s1, const nstr_t *s2, error *err)
{
	/*
	 * Return values are always undefined if an error was yeeted so it's not
	 * strictly necessary to return a correct(ish) result here, but the
	 * philosophy of libneo is to always behave in a way that is the least
	 * harmful.
	 */
	if (s1 == nil) {
		yeet(err, EFAULT, "First string is nil");
		if (s2 == nil)
			return 0;
		return -1;
	}
	if (s2 == nil) {
		yeet(err, EFAULT, "Second string is nil");
		return 1;
	}

	int ret;

	usize maxbytes;
	if (s1->_size > s2->_size)
		maxbytes = s2->_size;
	else
		maxbytes = s1->_size;

	ret = strncmp(s1->_data, s2->_data, maxbytes);
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
