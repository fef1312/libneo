/** See the end of this file for copyright and license terms. */

/* strnlen */
#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <string.h>

#include "neo/_error.h"
#include "neo/_nalloc.h"
#include "neo/_nref.h"
#include "neo/_nstr.h"
#include "neo/_stddef.h"
#include "neo/_types.h"

nstr_t *nstrcat(const nstr_t *s1, const nstr_t *s2, error *err)
{
	if (s1 == nil) {
		yeet(err, EFAULT, "First string is nil");
		return nil;
	}
	if (s2 == nil) {
		yeet(err, EFAULT, "Second string is nil");
		return nil;
	}

	usize s1_size_without_nul = strlen(s1->_data);
	usize s2_size_without_nul = strlen(s2->_data);
	usize cat_size = s1_size_without_nul + s2_size_without_nul + 1;
	char *cat = nalloc(cat_size, err);
	catch(err) {
		return nil;
	}

	memcpy(cat, s1->_data, s1_size_without_nul);
	memcpy(cat + s1_size_without_nul, s2->_data, s2_size_without_nul);
	cat[s1_size_without_nul + s2_size_without_nul] = '\0';

	nstr_t *ret = nstr(cat, err);
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
