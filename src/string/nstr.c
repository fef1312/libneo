/** See the end of this file for copyright and license terms. */

#include <errno.h>
#include <string.h>

#include "neo/_error.h"
#include "neo/_nalloc.h"
#include "neo/_nref.h"
#include "neo/_string.h"
#include "neo/_types.h"
#include "neo/utf.h"

static void nstr_destroy(string *str)
{
	nfree(str->_data);
	nfree(str);
}

string *nstr(const char *restrict s, error *err)
{
	if (s == nil) {
		yeet(err, EFAULT, "String must not be nil");
		return nil;
	}

	string *str = nalloc(sizeof(*str), err);
	catch(err) {
		return nil;
	}

	/*
	 * neo strings are terminated by four NUL characters rather than just
	 * one.  We do this to make sure nothing bad can happen if some stupid
	 * UTF-8 implementation (read: my UTF-8 implementation) reads beyond the
	 * last byte if it is malformed to suggest the beginning of a multibyte
	 * sequence when it is actually not.  The rationale behind this is that
	 * it is way easier to write a branchless decoder if it is allowed to
	 * always read up to four bytes rather than honor an unexpected NUL
	 * terminator within a multibyte sequence.
	 *
	 * Yeah, this is definitely never gonna break my legs.
	 */
	usize nbytes = strlen(s) + 4;
	str->_data = nalloc(nbytes, err);
	catch(err) {
		nfree(str);
		return nil;
	}

	strcpy(str->_data, s);
	str->_data[nbytes - 3] = '\0';
	str->_data[nbytes - 2] = '\0';
	str->_data[nbytes - 1] = '\0';
	str->_len = utf8_strlen(str->_data);
	str->_capacity = nbytes;
	nref_init(str, nstr_destroy);

	return str;
}

nchar nchrat(string *s, usize index, error *err)
{
	if (s == nil) {
		yeet(err, EFAULT, "String is nil");
		return '\0';
	}

	nget(s);

	if (index >= s->_len) {
		yeet(err, ERANGE, "String index out of bounds");
		return '\0';
	}

	char *ptr = s->_data;
	while (index != 0)
		index -= (*ptr++ & 0xc0) != 0x80;
	ptr--;

	nchar ret;
	utf8_to_nchr(&ret, ptr, err);

	nput(s);

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
