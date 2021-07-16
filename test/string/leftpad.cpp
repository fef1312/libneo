/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>

TEST_CASE( "leftpad: Pad a string with ASCII character", "[string/leftpad.c]" )
{
	error err;
	string *s = nstr("i'm gay,,,", nil);

	string *expected = nstr(",,,i'm gay,,,", nil);
	string *actual = leftpad(s, 13, ',', &err);

	REQUIRE( actual != nil );
	REQUIRE( nlen(actual) == 13 );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(s);
	nput(expected);
	nput(actual);
}

TEST_CASE( "leftpad: Pad a string with UTF-8 character", "[string/leftpad.c]" )
{
	error err;
	string *s = nstr("i'm gay,,,", nil);

	string *expected = nstr("\xf0\x9f\xa5\xba\xf0\x9f\xa5\xbai'm gay,,,", nil);
	string *actual = leftpad(s, 12, 0x01f97a, &err);

	REQUIRE( actual != nil );
	REQUIRE( nlen(actual) == 12 );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(s);
	nput(expected);
	nput(actual);
}

TEST_CASE( "leftpad: Duplicate if string is expected length", "[string/leftpad.c]" )
{
	error err;
	string *s = nstr("i'm gay,,,", nil);

	string *padded = leftpad(s, 10, ',', &err);

	REQUIRE( padded != nil );
	REQUIRE( nlen(padded) == 10 );
	REQUIRE( nstreq(s, padded, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(s);
	nput(padded);
}

TEST_CASE( "leftpad: Error if string is nil", "[string/leftpad.c]" )
{
	error err;
	string *s = leftpad(nil, 10, ',', &err);

	string *expected_msg = nstr("String is nil", nil);

	REQUIRE( s == nil );
	REQUIRE( errnum(&err) == EFAULT );
	REQUIRE( nstreq(expected_msg, errmsg(&err), nil) );

	nput(expected_msg);
	errput(&err);
}

TEST_CASE( "leftpad: Error if string is too long", "[string/leftpad.c]" )
{
	error err;
	string *s = nstr("i'm gay,,,", nil);
	string *padded = leftpad(s, 9, ',', &err);

	string *expected_msg = nstr("String is longer than requested length", nil);

	REQUIRE( padded == nil );
	REQUIRE( errnum(&err) == ERANGE );
	REQUIRE( nstreq(expected_msg, errmsg(&err), nil) );

	nput(s);
	nput(expected_msg);
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
