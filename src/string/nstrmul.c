/** See the end of this file for copyright and license terms. */

#include <errno.h>
#include <string.h>

#include "neo/_error.h"
#include "neo/_nalloc.h"
#include "neo/_nref.h"
#include "neo/_stddef.h"
#include "neo/_string.h"
#include "neo/_types.h"
#include "neo/utf.h"

string *nstrmul(const string *s, usize n, error *err)
{
	if (s == nil) {
		yeet(err, EFAULT, "String is nil");
		return 0;
	}
	if (nlen(s) == 0 || n == 0)
		return nstr("", err);
	if (n == 1)
		return nstrdup(s, err);

	usize s_size = strlen(s->_data);
	char *multiplied = nalloc(s_size * n + 1, err);
	catch(err) {
		return nil;
	}

	char *pos = multiplied;
	while (n-- != 0) {
		strcpy(pos, s->_data);
		pos += s_size;
	}

	string *ret = nstr(multiplied, err);
	nfree(multiplied);
	return ret;
}

string *nchrmul(nchar c, usize n, error *err)
{
	if (n == 0)
		return nstr("", err);

	char s[5];
	usize s_size = utf8_from_nchr(&s[0], c, err);
	catch(err) {
		return nil;
	}

	char *multiplied = nalloc(s_size * n + 1, err);
	catch(err) {
		return nil;
	}

	char *pos = multiplied;
	while (n-- != 0) {
		memcpy(pos, &s[0], s_size);
		pos += s_size;
	}

	string *ret = nstr(multiplied, err);
	nfree(multiplied);
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
