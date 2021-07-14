/** See the end of this file for copyright and license terms. */

/*
 * The UTF-8 conversion functions are based on the branchless UTF-8 decoder by
 * Christopher Wellons, which is in the public domain.  For the original, see
 * <https://github.com/skeeto/branchless-utf8/blob/f2d0e24c3864d726cd009901726df4778ad3e0d5/utf8.h>
 */

#include <errno.h>
#include <stdint.h>

#include "neo/_error.h"
#include "neo/_nalloc.h"
#include "neo/_types.h"
#include "neo/utf.h"

usize utf8_check(const char *restrict s, error *err)
{
	usize ret = 0;
	nchar c;

	while (*s != '\0') {
		ret++;
		s += utf8_to_nchr(&c, s, err);
		catch(err) {
			break;
		}
	}

	return ret;
}

usize utf8_strlen(const char *restrict s)
{
	usize len = 0;

	while (*s != '\0')
		len += (*s++ & 0xc0) != 0x80;

	return len;
}

usize utf8_nchr_size(nchar c, error *err)
{
	usize ret;

	if (c > 0x0010ffff) {
		ret = 0;
		yeet(err, EINVAL, "Character code not within Unicode range");
	} else {
		ret = 1;
		ret += c > 0x7f;
		ret += c > 0x07ff;
		ret += c > 0xffff;
		neat(err);
	}

	return ret;
}

/*
 * From RFC 3629, Section 3:
 *
 * Char. number range  |        UTF-8 octet sequence
 *    (hexadecimal)    |              (binary)
 * --------------------+---------------------------------------------
 * 0000 0000-0000 007F | 0xxxxxxx
 * 0000 0080-0000 07FF | 110xxxxx 10xxxxxx
 * 0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
 * 0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 *
 * See <https://datatracker.ietf.org/doc/html/rfc3629#section-3>
 */

usize utf8_from_nchr(char *restrict dest, nchar c, error *err)
{
	static const char prefixes[] = { 0x00, 0x00, 0xc0, 0xe0, 0xf0 };

	usize utf8_size = utf8_nchr_size(c, err);
	catch(err) {
		*dest = '\0';
		return 0;
	}

	dest += utf8_size;
	*dest-- = '\0';

	switch (utf8_size) {
	case 4:
		*dest-- = (char)( 0x80 | (c & 0x3f) );
		c >>= 6;
		/* fall through */
	case 3:
		*dest-- = (char)( 0x80 | (c & 0x3f) );
		c >>= 6;
		/* fall through */
	case 2:
		*dest-- = (char)( 0x80 | (c & 0x3f) );
		c >>= 6;
		/* fall through */
	case 1:
		/*
		 * we don't need a bitmask for c here because utf8_nchr_size
		 * already did the validation work for us so we know that c
		 * doesn't have any upper bits it shouldn't
		 */
		*dest = (char)( prefixes[utf8_size] | c );
		break;
	}

	return utf8_size;
}

/*
 * TODO: This (almost) branchless implementation is all fancy and shit, but it
 *       may read up to two bytes beyond the memory area allocated for the input
 *       buffer if it is passed a malformed code sequence.  Someone (hopefully
 *       not me lmao) should decide whether potentially overreading 3 bytes is
 *       worth the considerable speed gain from this design.
 */

usize utf8_to_nchr(nchar *dest, const char *restrict utf8chr, error *err)
{
	/* Expected sequence length per the 5 MSBs of the start byte */
	static const uint_fast8_t lengths[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 4, 0,
	};
	/* Payload bitmask for first byte in the sequence per sequence length */
	static const char         cmasks[] = {       0x00, 0x7f, 0x1f,  0x0f,    0x07 };
	/* Minimum Unicode values per sequence length */
	static const nchar        mins[]   = { 0xffffffff, 0x00, 0x80, 0x800, 0x10000 };
	/* Error bitmasks for (unused) bytes 2-4 per sequence length */
	static const uint_fast8_t emasks[] = {       0x00, 0x03, 0x07,  0x3f,    0xff };

	uint_fast8_t cshift = 0;
	/*
	 * 0xff bitmask just in case we are on a really odd
	 * architecture where char is more than one byte
	 */
	uint_fast8_t len = lengths[(utf8chr[0] >> 3) & 0xff];
	/*
	 * 7-6: two MSBs of the fourth byte in the sequence, must be 0b10
	 * 5-4: two MSBs of the third byte in the sequence, must be 0b10
	 * 3-2: two MSBs of the second byte in the sequence, must be 0b10
	 * 1:   whether the start byte is invalid
	 * 0:   whether non-canonical encoding is used
	 */
	uint_fast8_t eflags = 0;
	nchar c = '\0';

	switch (len) {
	case 4:
		c = (nchar)(utf8chr[3] & 0x3f);			/* 10xx xxxx */
		cshift += 6;
		eflags |= utf8chr[3];
		/* fall through */
	case 3:
		c |= (nchar)(utf8chr[2] & 0x3f) << cshift;	/* 10xx xxxx */
		cshift += 6;
		eflags |= (utf8chr[2] & 0xc0) >> 2;
		/* fall through */
	case 2:
		c |= (nchar)(utf8chr[1] & 0x3f) << cshift;	/* 10xx xxxx */
		cshift += 6;
		eflags |= (utf8chr[1] & 0xc0) >> 4;
		/* fall through */
	case 1:
		c |= (nchar)(utf8chr[0] & cmasks[len]) << cshift;
		break;
	case 0:
		eflags |= 0x02;
		break;
	}

	/* UTF-8 mandates each char be stored in as few bytes as possible */
	eflags = c < mins[len];

	/*
	 * Bytes 7-2 in eflags store the respective 2 MSBs of each tail byte
	 * in the sequence which must all start with 0b10, therefore eflags
	 * should be 0b101010xx if we have a four byte sequence.  Toggling the
	 * bits we expect to be one (0xa8) zeores bytes 7-2 if they are correct,
	 * then we just need to mask out the bits that are unused if the
	 * sequence is less than 4 bytes (emasks).
	 */
	eflags ^= 0xa8;
	eflags &= emasks[len];

	if (eflags != 0) {
		/*
		 * Errors are expected to be rare, so it's okay to use a bunch
		 * of if statements in favor of accurate error descriptions
		 * (and yeet is slow af anyway because it uses vsnprintf)
		 */
		*dest = '\0';
		if ((eflags & 0x01) != 0) {
			yeet(err, EINVAL,
			     "Non canonical UTF-8 encoding: %zu byte character stored in %u bytes",
			     utf8_nchr_size(c, nil), len);
		} else if ((eflags & 0x02) != 0) {
			yeet(err, EINVAL, "Illegal UTF-8 sequence start byte: 0x%02x", utf8chr[0]);
		} else if ((eflags & 0x0c) != 0) {
			yeet(err, EINVAL, "Byte 2 in UTF-8 sequence invalid: 0x%02x", utf8chr[1]);
		} else if ((eflags & 0x30) != 0) {
			yeet(err, EINVAL, "Byte 3 in UTF-8 sequence invalid: 0x%02x", utf8chr[2]);
		} else if ((eflags & 0xc0) != 0) {
			yeet(err, EINVAL, "Byte 4 in UTF-8 sequence invalid: 0x%02x", utf8chr[3]);
		} else {
			yeet(err, EINVAL, "Unexpected decoding error");
		}
	} else {
		*dest = c;
		neat(err);
	}

	return len;
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
