/** See the end of this file for copyright and license terms. */

/* strnlen */
#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <string.h>

#include "neo/_error.h"
#include "neo/_nalloc.h"
#include "neo/_nref.h"
#include "neo/_nstr.h"
#include "neo/_toolchain.h"
#include "neo/_types.h"
#include "neo/utf.h"

void _neo_nstr_destroy(nstr_t *str)
{
	if (str->_borrow != nil)
		_neo_nput(str->_borrow);
	nfree(str);
}

static nstr_t *nstr_unsafe(const char *s, usize size_without_nul, error *err)
{
	usize len = utf8_ncheck(s, size_without_nul, err);
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

	nstr_t *str = nalloc(sizeof(*str) + size_without_nul + 4, err);
	catch(err) {
		return nil;
	}

	/*
	 * To improve locality and lower fragmentation, the actual data is
	 * stored immediately after the string itself.  This also saves us an
	 * additional memory allocation.
	 */
	char *data = (char *)str + sizeof(*str);
	memcpy(data, s, size_without_nul);
	for (unsigned int i = 0; i < 4; i++)
		data[size_without_nul + i] = '\0';

	str->_data = data;
	str->_len = len;
	str->_borrow = nil;
	str->_size = size_without_nul + 4;
	nref_init(str, _neo_nstr_destroy);

	return str;
}

nstr_t *nstr(const char *restrict s, error *err)
{
	if (s == nil) {
		yeet(err, EFAULT, "String is nil");
		return nil;
	}

	usize size_without_nul = strlen(s);
	return nstr_unsafe(s, size_without_nul, err);
}

nstr_t *nnstr(const char *restrict s, usize maxsize, error *err)
{
	if (s == nil) {
		yeet(err, EFAULT, "String is nil");
		return nil;
	}

	usize size_without_nul = strnlen(s, maxsize);
	return nstr_unsafe(s, size_without_nul, err);
}

nchar nchrat(const nstr_t *s, usize index, error *err)
{
	if (s == nil) {
		yeet(err, EFAULT, "String is nil");
		return '\0';
	}

	if (index >= s->_len) {
		yeet(err, ERANGE, "String index out of bounds");
		return '\0';
	}

	const char *ptr = s->_data;
	while (index != 0)
		index -= (*ptr++ & 0xc0) != 0x80;
	ptr--;

	nchar ret;
	utf8_to_nchr(&ret, ptr, err);

	return ret;
}

/* see src/neo.ld */
extern struct _neo_nstr_init_info __neo_nstr_array_start;
extern struct _neo_nstr_init_info __neo_nstr_array_end;

void _neo_nstr_init_array(void)
{
	struct _neo_nstr_init_info *ptr = &__neo_nstr_array_start;
	while (ptr != &__neo_nstr_array_end) {
		*ptr->dest = nstr(ptr->data, nil);
		ptr++;
	}
}
__neo_init(_neo_nstr_init_array);

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
