/** See the end of this file for copyright and license terms. */

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "neo/_error.h"
#include "neo/_nalloc.h"
#include "neo/_nref.h"
#include "neo/_stddef.h"
#include "neo/_types.h"

static void nbuf_destroy(struct _neo_nbuf *buf)
{
	if (buf->_borrow != nil)
		_neo_nput(buf->_borrow);

	nfree(buf);
}

nbuf_t *nbuf_create(usize size, error *err)
{
	if (size == 0) {
		yeet(err, ERANGE, "Cannot create zero-size buffer");
		return nil;
	}

	/*
	 * Just like with strings, we allocate 4 extra bytes.
	 * The buffer functions depend on this behavior, don't change.
	 */
	struct _neo_nbuf *buf = nalloc(sizeof(*buf) + size + 4, err);
	catch(err) {
		return nil;
	}

	byte *data = (byte *)buf + sizeof(*buf);
	for (unsigned int i = 0; i < 4; i++)
		data[size + i] = 0;

	buf->_size = size;
	buf->_data = data;
	buf->_borrow = nil;
	nref_init(buf, nbuf_destroy);
	neat(err);
	return buf;
}

nbuf_t *nbuf_from(const void *data, usize len, error *err)
{
	if (data == nil) {
		yeet(err, EFAULT, "Data is nil");
		return nil;
	}

	struct _neo_nbuf *buf = nbuf_create(len, err);
	catch(err) {
		return nil;
	}

	byte *buf_data = (byte *)buf + sizeof(*buf);
	memcpy(buf_data, data, len);
	/* _data field already filled by nbuf_create */

	return buf;
}

nbuf_t *nbuf_from_str(const char *s, error *err)
{
	if (s == nil) {
		yeet(err, EFAULT, "String is nil");
		return nil;
	}

	usize size = strlen(s) + 1;
	return nbuf_from(s, size, err);
}

nbuf_t *nbuf_from_nstr(nstr_t *s, error *err)
{
	if (s == nil) {
		yeet(err, EFAULT, "String is nil");
		return nil;
	}

	nbuf_t *buf = nalloc(sizeof(*buf), err);
	catch(err) {
		return nil;
	}

	nget(s);
	buf->_size = s->_size;
	buf->_borrow = &s->__neo_nref;
	buf->_data = (const byte *)s->_data;
	nref_init(buf, nbuf_destroy);

	return buf;
}

nbuf_t *nbuf_clone(nbuf_t *buf, error *err)
{
	if (buf == nil) {
		yeet(err, EFAULT, "Source buffer is nil");
		return nil;
	}

	nbuf_t *clone = nalloc(sizeof(*clone), err);
	catch(err) {
		return nil;
	}

	nget(buf);

	clone->_size = buf->_size;
	clone->_borrow = &buf->__neo_nref;
	clone->_data = buf->_data;
	nref_init(clone, nbuf_destroy);

	return clone;
}

int nbuf_cmp(const nbuf_t *buf1, const nbuf_t *buf2, error *err)
{
	if (buf1 == nil) {
		yeet(err, EFAULT, "First buffer is nil");
		if (buf2 == nil)
			return 0;
		else
			return -1;
	}
	if (buf2 == nil) {
		yeet(err, EFAULT, "Second buffer is nil");
		return 1;
	}

	neat(err);

	if (buf1->_data == buf2->_data)
		return 0;

	/*
	 * Extra byte because the two buffers might be of different size
	 * (one of the reasons nbuf_create() allocates 4 bytes more than needed)
	 */
	usize maxbytes = nmin(nlen(buf1), nlen(buf2)) + 1;
	return memcmp(&buf1->_data[0], &buf2->_data[0], maxbytes);
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
