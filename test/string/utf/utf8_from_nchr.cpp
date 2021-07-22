/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>
#include <neo/utf.h>

TEST_CASE( "utf8_from_nchr: Encode 1-byte character", "[string/utf.c]" )
{
	char buf[5] = { '\xff', '\xff', '\xff', '\xff', '\xff' };
	error err;
	usize size = utf8_from_nchr(&buf[0], ',', &err);

	REQUIRE( buf[0] == ',' );
	REQUIRE( buf[1] == '\0' );
	REQUIRE( buf[2] == '\xff' );
	REQUIRE( buf[3] == '\xff' );
	REQUIRE( buf[4] == '\xff' );
	REQUIRE( size == 1 );
	REQUIRE( errnum(&err) == 0 );
}

TEST_CASE( "utf8_from_nchr: Encode 2-byte character", "[string/utf.c]" )
{
	char buf[5] = { '\xff', '\xff', '\xff', '\xff', '\xff' };
	error err;
	/* U+03B1 Greek Smol Letter Alpha */
	usize size = utf8_from_nchr(&buf[0], 0x03b1, &err);

	REQUIRE( buf[0] == '\xce' );
	REQUIRE( buf[1] == '\xb1' );
	REQUIRE( buf[2] == '\0' );
	REQUIRE( buf[3] == '\xff' );
	REQUIRE( buf[4] == '\xff' );
	REQUIRE( size == 2 );
	REQUIRE( errnum(&err) == 0 );
}

TEST_CASE( "utf8_from_nchr: Encode 3-byte character", "[string/utf.c]" )
{
	char buf[5] = { '\xff', '\xff', '\xff', '\xff', '\xff' };
	error err;
	/* U+3042 Hiragana Letter A */
	usize size = utf8_from_nchr(&buf[0], 0x3042, &err);

	REQUIRE( buf[0] == '\xe3' );
	REQUIRE( buf[1] == '\x81' );
	REQUIRE( buf[2] == '\x82' );
	REQUIRE( buf[3] == '\0' );
	REQUIRE( buf[4] == '\xff' );
	REQUIRE( size == 3 );
	REQUIRE( errnum(&err) == 0 );
}

TEST_CASE( "utf8_from_nchr: Encode 4-byte character", "[string/utf.c]" )
{
	char buf[5] = { '\xff', '\xff', '\xff', '\xff', '\xff' };
	error err;
	/* U+1F97A The Bottom Emoji(TM) */
	usize size = utf8_from_nchr(&buf[0], 0x01f97a, &err);

	REQUIRE( buf[0] == '\xf0' );
	REQUIRE( buf[1] == '\x9f' );
	REQUIRE( buf[2] == '\xa5' );
	REQUIRE( buf[3] == '\xba' );
	REQUIRE( buf[4] == '\0' );
	REQUIRE( size == 4 );
	REQUIRE( errnum(&err) == 0 );
}

TEST_CASE( "utf8_from_nchr: Error if out of Unicode range", "[string/utf.c]" )
{
	char buf[5] = { '\xff', '\xff', '\xff', '\xff', '\xff' };
	error err;
	/* Unicode range is 0x00~0x10ffff */
	usize size = utf8_from_nchr(&buf[0], 0x110000, &err);

	nstr_t *expected = nstr("Character code not within Unicode range", nil);
	nstr_t *actual = errmsg(&err);

	REQUIRE( buf[0] == '\0' );
	REQUIRE( buf[1] == '\xff' );
	REQUIRE( buf[2] == '\xff' );
	REQUIRE( buf[3] == '\xff' );
	REQUIRE( buf[4] == '\xff' );
	REQUIRE( size == 0 );
	REQUIRE( errnum(&err) == EINVAL );
	REQUIRE( nstreq(expected, actual, nil) );
	errput(&err);
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
