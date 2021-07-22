/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>
#include <neo/utf.h>

TEST_CASE( "utf8_to_nchr: Decode 1-byte character sequence", "[string/utf.c]" )
{
	error err;
	nchar c;
	usize size = utf8_to_nchr(&c, ",", &err);

	REQUIRE( size == 1 );
	REQUIRE( c == ',' );
	REQUIRE( errnum(&err) == 0 );
	REQUIRE( errmsg(&err) == nil );
}

TEST_CASE( "utf8_to_nchr: Decode 2-byte character sequence", "[string/utf.c]" )
{
	error err;
	nchar c;
	/* U+03B1 Greek Smol Letter Alpha */
	usize size = utf8_to_nchr(&c, "\xce\xb1", &err);

	REQUIRE( size == 2 );
	REQUIRE( c == 0x03b1 );
	REQUIRE( errnum(&err) == 0 );
	REQUIRE( errmsg(&err) == nil );
}

TEST_CASE( "utf8_to_nchr: Decode 3-byte character sequence", "[string/utf.c]" )
{
	error err;
	nchar c;
	/* U+3042 Hiragana Letter A */
	usize size = utf8_to_nchr(&c, "\xe3\x81\x82", &err);

	REQUIRE( size == 3 );
	REQUIRE( c == 0x3042 );
	REQUIRE( errnum(&err) == 0 );
	REQUIRE( errmsg(&err) == nil );
}

TEST_CASE( "utf8_to_nchr: Decode 4-byte character sequence", "[string/utf.c]" )
{
	error err;
	nchar c;
	/* U+1F97A The Bottom Emoji(TM) */
	usize size = utf8_to_nchr(&c, "\xf0\x9f\xa5\xba", &err);

	REQUIRE( size == 4 );
	REQUIRE( c == 0x01f97a );
	REQUIRE( errnum(&err) == 0 );
	REQUIRE( errmsg(&err) == nil );
}

TEST_CASE( "utf8_to_nchr: Error on malformed sequence start", "[string/utf.c]" )
{
	error err;
	nchar c;
	utf8_to_nchr(&c, "\xff", &err);

	nstr_t *expected = nstr("Illegal UTF-8 sequence start byte: 0xff", nil);
	nstr_t *actual = errmsg(&err);

	REQUIRE( c == '\0' );
	REQUIRE( errnum(&err) == EINVAL );
	REQUIRE( nstreq(expected, actual, nil) );
	errput(&err);
}

TEST_CASE( "utf8_to_nchr: Error on wrong second byte", "[string/utf.c]" )
{
	error err;
	nchar c;
	utf8_to_nchr(&c, "\xce\xff", &err);

	nstr_t *expected = nstr("Byte 2 in UTF-8 sequence invalid: 0xff", nil);
	nstr_t *actual = errmsg(&err);

	REQUIRE( c == '\0' );
	REQUIRE( errnum(&err) == EINVAL );
	REQUIRE( nstreq(expected, actual, nil) );
	errput(&err);
}

TEST_CASE( "utf8_to_nchr: Error on wrong third byte", "[string/utf.c]" )
{
	error err;
	nchar c;
	utf8_to_nchr(&c, "\xe3\x81\xff", &err);

	nstr_t *expected = nstr("Byte 3 in UTF-8 sequence invalid: 0xff", nil);
	nstr_t *actual = errmsg(&err);

	REQUIRE( c == '\0' );
	REQUIRE( errnum(&err) == EINVAL );
	REQUIRE( nstreq(expected, actual, nil) );
	errput(&err);
}

TEST_CASE( "utf8_to_nchr: Error on wrong fourth byte", "[string/utf.c]" )
{
	error err;
	nchar c;
	utf8_to_nchr(&c, "\xf0\x9f\xa5\xff", &err);

	nstr_t *expected = nstr("Byte 4 in UTF-8 sequence invalid: 0xff", nil);
	nstr_t *actual = errmsg(&err);

	REQUIRE( c == '\0' );
	REQUIRE( errnum(&err) == EINVAL );
	REQUIRE( nstreq(expected, actual, nil) );
	errput(&err);
}

TEST_CASE( "utf8_to_nchr: Error on non canonical encoding", "[string/utf.c]" )
{
	error err;
	nchar c;
	utf8_to_nchr(&c, "\xf0\x80\x80\xa0", &err);

	nstr_t *expected = nstr("Non canonical UTF-8 encoding: 1 byte character stored in 4 bytes", nil);
	nstr_t *actual = errmsg(&err);

	REQUIRE( c == '\0' );
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
