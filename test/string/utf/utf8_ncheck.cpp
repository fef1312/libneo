/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>
#include <neo/utf.h>

TEST_CASE( "utf8_ncheck: ASCII string", "[string/utf.c]" )
{
	error err;
	usize len = utf8_ncheck("i'm gay,,,", 10, &err);

	REQUIRE( len == 10 );
	REQUIRE( errnum(&err) == 0 );
	REQUIRE( errmsg(&err) == nil );
}

TEST_CASE( "utf8_ncheck: String with 2-byte UTF-8 sequence", "[string/utf.c]" )
{
	error err;
	/* U+03B1 Greek Smol Letter Alpha */
	usize len = utf8_ncheck("i'm g\xce\xb1y,,,", 11, &err);

	REQUIRE( len == 10 );
	REQUIRE( errnum(&err) == 0 );
	REQUIRE( errmsg(&err) == nil );
}

TEST_CASE( "utf8_ncheck: String with 3-byte UTF-8 sequence", "[string/utf.c]" )
{
	error err;
	/* U+3042 Hiragana Letter A */
	usize len = utf8_ncheck("i'm g\xe3\x81\x82y,,,", 12, &err);

	REQUIRE( len == 10 );
	REQUIRE( errnum(&err) == 0 );
	REQUIRE( errmsg(&err) == nil );
}

TEST_CASE( "utf8_ncheck: String with 4-byte UTF-8 sequence", "[string/utf.c]" )
{
	error err;
	/* U+1F97A The Bottom Emoji(TM) */
	usize len = utf8_ncheck("i'm gay\xf0\x9f\xa5\xba,,,", 14, &err);

	REQUIRE( len == 11 );
	REQUIRE( errnum(&err) == 0 );
	REQUIRE( errmsg(&err) == nil );
}

TEST_CASE( "utf8_ncheck: Don't overread", "[string/utf.c]" )
{
	error err;
	usize len = utf8_ncheck("i'm gay,,,", 8, &err);

	REQUIRE( len == 8 );
	REQUIRE( errnum(&err) == 0 );
	REQUIRE( errmsg(&err) == nil );
}

TEST_CASE( "utf8_ncheck: Error on malformed sequence start", "[string/utf.c]" )
{
	error err;
	utf8_ncheck("\xff", 1, &err);

	string *expected = nstr("Illegal UTF-8 sequence start byte: 0xff", nil);
	string *actual = errmsg(&err);

	REQUIRE( errnum(&err) == EINVAL );
	REQUIRE( nstreq(expected, actual, nil) );
	errput(&err);
}

TEST_CASE( "utf8_ncheck: Error on wrong second byte", "[string/utf.c]" )
{
	error err;
	utf8_ncheck("\xce\xff", 2, &err);

	string *expected = nstr("Byte 2 in UTF-8 sequence invalid: 0xff", nil);
	string *actual = errmsg(&err);

	REQUIRE( errnum(&err) == EINVAL );
	REQUIRE( nstreq(expected, actual, nil) );
	errput(&err);
}

TEST_CASE( "utf8_ncheck: Error on wrong third byte", "[string/utf.c]" )
{
	error err;
	utf8_ncheck("\xe3\x81\xff", 3, &err);

	string *expected = nstr("Byte 3 in UTF-8 sequence invalid: 0xff", nil);
	string *actual = errmsg(&err);

	REQUIRE( errnum(&err) == EINVAL );
	REQUIRE( nstreq(expected, actual, nil) );
	errput(&err);
}

TEST_CASE( "utf8_ncheck: Error on wrong fourth byte", "[string/utf.c]" )
{
	error err;
	utf8_ncheck("\xf0\x9f\xa5\xff", 4, &err);

	string *expected = nstr("Byte 4 in UTF-8 sequence invalid: 0xff", nil);
	string *actual = errmsg(&err);

	REQUIRE( errnum(&err) == EINVAL );
	REQUIRE( nstreq(expected, actual, nil) );
	errput(&err);
}

TEST_CASE( "utf8_ncheck: Error on non canonical encoding", "[string/utf.c]" )
{
	error err;
	utf8_ncheck("\xf0\x80\x80\xa0", 4, &err);

	string *expected = nstr("Non canonical UTF-8 encoding: 1 byte character stored in 4 bytes", nil);
	string *actual = errmsg(&err);

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
