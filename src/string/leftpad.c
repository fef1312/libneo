/** See the end of this file for copyright and license terms. */

#include <errno.h>
#include <string.h>

#include "neo/_error.h"
#include "neo/_nalloc.h"
#include "neo/_nref.h"
#include "neo/_nstr.h"
#include "neo/_types.h"
#include "neo/utf.h"

static inline nstr_t *leftpad_unsafe(const nstr_t *s, usize len, nchar fillchr, error *err)
{
	char utf8_fillchr[5];
	usize fillchr_size = utf8_from_nchr(&utf8_fillchr[0], fillchr, err);
	catch(err) {
		return 0;
	}

	usize extra_chars = len - s->_len;
	/*
	 * This is actually three bytes larger than the actual size because neo
	 * strings are terminated with four NUL characters rather than just one,
	 * but that's okay because if we don't even have enough memory for three
	 * extra bytes we are screwed anyway.
	 */
	usize size_now = s->_size;
	usize size_after = size_now + (extra_chars * fillchr_size);
	char *dest = nalloc(size_after, err);
	catch(err) {
		return 0;
	}

	char *pos = dest;
	while (extra_chars-- > 0) {
		for (int i = 0; i < fillchr_size; i++)
			*pos++ = utf8_fillchr[i];
	}
	strcpy(pos, s->_data);

	nstr_t *padded = nstr(dest, err);
	catch(err) {
		padded = nil;
	}
	nfree(dest);
	return padded;
}

nstr_t *leftpad(nstr_t *s, usize len, nchar fillchr, error *err)
{
	if (s == nil) {
		yeet(err, EFAULT, "String is nil");
		return 0;
	}

	nstr_t *padded;

	if (len < nlen(s)) {
		yeet(err, ERANGE, "String is longer than requested length");
		padded = nil;
	} else if (nlen(s) == len) {
		padded = nstrdup(s, err);
	} else {
		padded = leftpad_unsafe(s, len, fillchr, err);
	}

	return padded;
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
