/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>

TEST_CASE( "u2nstr: Convert 0 to base 2", "[string/x2nstr.c]" )
{
	error err;

	string *expected = nstr("0", nil);
	string *actual = u2nstr(0, 2, &err);

	REQUIRE( actual != nil );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(expected);
	nput(actual);
}

TEST_CASE( "u2nstr: Convert 0 to base 36", "[string/x2nstr.c]" )
{
	error err;

	string *expected = nstr("0", nil);
	string *actual = u2nstr(0, 36, &err);

	REQUIRE( actual != nil );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(expected);
	nput(actual);
}

TEST_CASE( "u2nstr: Convert 255 to base 2", "[string/x2nstr.c]" )
{
	error err;

	string *expected = nstr("11111111", nil);
	string *actual = u2nstr(255, 2, &err);

	REQUIRE( actual != nil );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(expected);
	nput(actual);
}

TEST_CASE( "u2nstr: Convert 1679615 to base 36", "[string/x2nstr.c]" )
{
	error err;

	string *expected = nstr("zzzz", nil);
	string *actual = u2nstr(1679615, 36, &err);

	REQUIRE( actual != nil );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(expected);
	nput(actual);
}

TEST_CASE( "u2nstr: Convert 2^64-1 to base 16", "[string/x2nstr.c]" )
{
	error err;

	string *expected = nstr("ffffffffffffffff", nil);
	string *actual = u2nstr(0xffffffffffffffff, 16, &err);

	REQUIRE( actual != nil );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(expected);
	nput(actual);
}

TEST_CASE( "u2nstr: Error if base too low", "[string/x2nstr.c]" )
{
	error err;
	string *s = u2nstr(420, 1, &err);

	string *expected_msg = nstr("Numerical base out of range", nil);
	string *actual_msg = errmsg(&err);

	REQUIRE( s == nil );
	REQUIRE( nstreq(expected_msg, actual_msg, nil) );
	REQUIRE( errnum(&err) == EINVAL );

	nput(expected_msg);
	errput(&err);
}

TEST_CASE( "u2nstr: Error if base too high", "[string/x2nstr.c]" )
{
	error err;
	string *s = u2nstr(420, 37, &err);

	string *expected_msg = nstr("Numerical base out of range", nil);
	string *actual_msg = errmsg(&err);

	REQUIRE( s == nil );
	REQUIRE( nstreq(expected_msg, actual_msg, nil) );
	REQUIRE( errnum(&err) == EINVAL );

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
