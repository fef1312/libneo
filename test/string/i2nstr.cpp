/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>

TEST_CASE( "i2nstr: Convert 0 to base 2", "[string/x2nstr.c]" )
{
	error err;

	nstr_t *expected = nstr("0", nil);
	nstr_t *actual = i2nstr(0, 2, &err);

	REQUIRE( actual != nil );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(expected);
	nput(actual);
}

TEST_CASE( "i2nstr: Convert 0 to base 36", "[string/x2nstr.c]" )
{
	error err;

	nstr_t *expected = nstr("0", nil);
	nstr_t *actual = i2nstr(0, 36, &err);

	REQUIRE( actual != nil );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(expected);
	nput(actual);
}

TEST_CASE( "i2nstr: Convert 255 to base 2", "[string/x2nstr.c]" )
{
	error err;

	nstr_t *expected = nstr("11111111", nil);
	nstr_t *actual = i2nstr(255, 2, &err);

	REQUIRE( actual != nil );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(expected);
	nput(actual);
}

TEST_CASE( "i2nstr: Convert -255 to base 2", "[string/x2nstr.c]" )
{
	error err;

	nstr_t *expected = nstr("-11111111", nil);
	nstr_t *actual = i2nstr(-255, 2, &err);

	REQUIRE( actual != nil );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(expected);
	nput(actual);
}

TEST_CASE( "i2nstr: Convert 1679615 to base 36", "[string/x2nstr.c]" )
{
	error err;

	nstr_t *expected = nstr("zzzz", nil);
	nstr_t *actual = i2nstr(1679615, 36, &err);

	REQUIRE( actual != nil );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(expected);
	nput(actual);
}

TEST_CASE( "i2nstr: Convert -1679615 to base 36", "[string/x2nstr.c]" )
{
	error err;

	nstr_t *expected = nstr("-zzzz", nil);
	nstr_t *actual = i2nstr(-1679615, 36, &err);

	REQUIRE( actual != nil );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(expected);
	nput(actual);
}

TEST_CASE( "i2nstr: Convert 2^63-1 to base 16", "[string/x2nstr.c]" )
{
	error err;

	nstr_t *expected = nstr("7fffffffffffffff", nil);
	nstr_t *actual = i2nstr(0x7fffffffffffffff, 16, &err);

	REQUIRE( actual != nil );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(expected);
	nput(actual);
}

TEST_CASE( "i2nstr: Convert -2^63 to base 16", "[string/x2nstr.c]" )
{
	error err;

	nstr_t *expected = nstr("-8000000000000000", nil);
	nstr_t *actual = i2nstr(-0x8000000000000000, 16, &err);

	REQUIRE( actual != nil );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(expected);
	nput(actual);
}

TEST_CASE( "i2nstr: Error if base too low", "[string/x2nstr.c]" )
{
	error err;
	nstr_t *s = i2nstr(420, 1, &err);

	nstr_t *expected_msg = nstr("Numerical base out of range", nil);
	nstr_t *actual_msg = errmsg(&err);

	REQUIRE( s == nil );
	REQUIRE( nstreq(expected_msg, actual_msg, nil) );
	REQUIRE( errnum(&err) == EINVAL );

	nput(expected_msg);
	errput(&err);
}

TEST_CASE( "i2nstr: Error if base too high", "[string/x2nstr.c]" )
{
	error err;
	nstr_t *s = i2nstr(420, 37, &err);

	nstr_t *expected_msg = nstr("Numerical base out of range", nil);
	nstr_t *actual_msg = errmsg(&err);

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
