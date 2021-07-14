/** See the end of this file for copyright and license terms. */

#include <errno.h>
#include <string.h>

#include "neo/_error.h"
#include "neo/_nalloc.h"
#include "neo/_nref.h"
#include "neo/_stddef.h"
#include "neo/_string.h"
#include "neo/_types.h"

string *nstrcat(const string *s1, const string *s2, error *err)
{
	if (s1 == nil) {
		yeet(err, EFAULT, "First string is nil");
		return nil;
	}
	if (s2 == nil) {
		yeet(err, EFAULT, "Second string is nil");
		return nil;
	}

	usize s1_size = strlen(s1->_data);
	usize s2_size = strlen(s2->_data);
	char *cat = nalloc(s1_size + s2_size + 1, err);
	catch(err) {
		return nil;
	}

	strcpy(cat, s1->_data);
	strcpy(cat + s1_size, s2->_data);

	string *ret = nstr(cat, err);
	nfree(cat);
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
