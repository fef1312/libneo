/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>
#include <neo/utf.h>

TEST_CASE( "utf8_check: ASCII string", "[string/utf.c]" )
{
	error err;
	utf8_check("i'm gay,,,", &err);

	REQUIRE( errnum(&err) == 0 );
	REQUIRE( errmsg(&err) == nil );
}

TEST_CASE( "utf8_check: String with 2-byte UTF-8 sequence", "[string/utf.c]" )
{
	error err;
	/* U+03B1 Greek Smol Letter Alpha */
	utf8_check("i'm g\xce\xb1y,,,", &err);

	REQUIRE( errnum(&err) == 0 );
	REQUIRE( errmsg(&err) == nil );
}

TEST_CASE( "utf8_check: String with 3-byte UTF-8 sequence", "[string/utf.c]" )
{
	error err;
	/* U+3042 Hiragana Letter A */
	utf8_check("i'm g\xe3\x81\x82y,,,", &err);

	REQUIRE( errnum(&err) == 0 );
	REQUIRE( errmsg(&err) == nil );
}

TEST_CASE( "utf8_check: String with 4-byte UTF-8 sequence", "[string/utf.c]" )
{
	error err;
	/* U+1F97A The Bottom Emoji(TM) */
	utf8_check("i'm gay\xf0\x9f\xa5\xba,,,", &err);

	REQUIRE( errnum(&err) == 0 );
	REQUIRE( errmsg(&err) == nil );
}

TEST_CASE( "utf8_check: Error on malformed sequence start", "[string/utf.c]" )
{
	error err;
	utf8_check("\xff", &err);

	nstr_t *expected = nstr("Illegal UTF-8 sequence start byte: 0xff", nil);
	nstr_t *actual = errmsg(&err);

	REQUIRE( errnum(&err) == EINVAL );
	REQUIRE( nstreq(expected, actual, nil) );
	errput(&err);
}

TEST_CASE( "utf8_check: Error on wrong second byte", "[string/utf.c]" )
{
	error err;
	utf8_check("\xce\xff", &err);

	nstr_t *expected = nstr("Byte 2 in UTF-8 sequence invalid: 0xff", nil);
	nstr_t *actual = errmsg(&err);

	REQUIRE( errnum(&err) == EINVAL );
	REQUIRE( nstreq(expected, actual, nil) );
	errput(&err);
}

TEST_CASE( "utf8_check: Error on wrong third byte", "[string/utf.c]" )
{
	error err;
	utf8_check("\xe3\x81\xff", &err);

	nstr_t *expected = nstr("Byte 3 in UTF-8 sequence invalid: 0xff", nil);
	nstr_t *actual = errmsg(&err);

	REQUIRE( errnum(&err) == EINVAL );
	REQUIRE( nstreq(expected, actual, nil) );
	errput(&err);
}

TEST_CASE( "utf8_check: Error on wrong fourth byte", "[string/utf.c]" )
{
	error err;
	utf8_check("\xf0\x9f\xa5\xff", &err);

	nstr_t *expected = nstr("Byte 4 in UTF-8 sequence invalid: 0xff", nil);
	nstr_t *actual = errmsg(&err);

	REQUIRE( errnum(&err) == EINVAL );
	REQUIRE( nstreq(expected, actual, nil) );
	errput(&err);
}

TEST_CASE( "utf8_check: Error on non canonical encoding", "[string/utf.c]" )
{
	error err;
	utf8_check("\xf0\x80\x80\xa0", &err);

	nstr_t *expected = nstr("Non canonical UTF-8 encoding: 1 byte character stored in 4 bytes", nil);
	nstr_t *actual = errmsg(&err);

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
