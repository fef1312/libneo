/** See the end of this file for copyright and license terms. */

/* strnlen */
#define _POSIX_C_SOURCE 200809L

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

static string *nstr_unsafe(const char *restrict s, usize size_without_nul, error *err)
{
	usize len = utf8_check(s, err);
	catch(err) {
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

	str->_data = nalloc(size_without_nul + 4, err);
	catch(err) {
		nfree(str);
		return nil;
	}

	str->_len = len;
	str->_size = size_without_nul + 4;
	nref_init(str, nstr_destroy);

	memcpy(str->_data, s, size_without_nul);
	str->_data[size_without_nul] = '\0';
	str->_data[size_without_nul + 1] = '\0';
	str->_data[size_without_nul + 2] = '\0';
	str->_data[size_without_nul + 3] = '\0';

	return str;
}

string *nstr(const char *restrict s, error *err)
{
	if (s == nil) {
		yeet(err, EFAULT, "String is nil");
		return nil;
	}

	usize size_without_nul = strlen(s);
	return nstr_unsafe(s, size_without_nul, err);
}

string *nnstr(const char *restrict s, usize maxsize, error *err)
{
	if (s == nil) {
		yeet(err, EFAULT, "String is nil");
		return nil;
	}

	usize size_without_nul = strnlen(s, maxsize);
	return nstr_unsafe(s, size_without_nul, err);
}

nchar nchrat(const string *s, usize index, error *err)
{
	if (s == nil) {
		yeet(err, EFAULT, "String is nil");
		return '\0';
	}

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
