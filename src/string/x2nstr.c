/** See the end of this file for copyright and license terms. */

#include <errno.h>

#include "neo/_error.h"
#include "neo/_nstr.h"
#include "neo/_types.h"

static char *unsigned_convert(char *end, u64 n, int radix, error *err)
{
	static const char digits[] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b',
		'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	};

	if (radix < 2 || radix > (sizeof(digits) / sizeof(digits[0]))) {
		yeet(err, EINVAL, "Numerical base out of range");
		return nil;
	}

	*end-- = '\0';
	do {
		unsigned int digit = n % radix;
		n /= radix;
		*end-- = digits[digit];
	} while (n != 0);
	end++;

	neat(err);
	return end;
}

nstr_t *u2nstr(u64 n, int radix, error *err)
{
	char buf[65];
	char *s = unsigned_convert(&buf[64], n, radix, err);
	catch (err) {
		return nil;
	}
	return nstr(s, err);
}

nstr_t *i2nstr(i64 n, int radix, error *err)
{
	char buf[66];

	char *s = unsigned_convert(&buf[65], nabs(n), radix, err);
	catch(err) {
		return nil;
	}

	if (n < 0)
		*(--s) = '-';

	return nstr(s, err);
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
