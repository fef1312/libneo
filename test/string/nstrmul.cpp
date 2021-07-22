/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>

TEST_CASE( "nstrmul: Repeat a string", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *s = nstr("aaaaa", nil);

	nstr_t *expected = nstr("aaaaaaaaaaaaaaa", nil);
	nstr_t *actual = nstrmul(s, 3, &err);

	REQUIRE( actual != nil );
	REQUIRE( nlen(actual) == 5 * 3 );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(s);
	nput(expected);
	nput(actual);
}

TEST_CASE( "nstrmul: Duplicate a string if count is 1", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *s = nstr("aaaaa", nil);

	nstr_t *mul = nstrmul(s, 1, &err);

	REQUIRE( nul != nil );
	REQUIRE( nlen(mul) == 5 );
	REQUIRE( nstreq(s, mul, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(s);
	nput(mul);
}

TEST_CASE( "nstrmul: Error if string is nil", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *mul = nstrmul(nil, 1, &err);

	nstr_t *expected_msg = nstr("String is nil", nil);

	REQUIRE( mul == nil );
	REQUIRE( errnum(&err) == EFAULT );
	REQUIRE( nstreq(expected_msg, errmsg(&err), nil) );

	errput(&err);
}

TEST_CASE( "nstrmul: Return empty string if count is 0", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *s = nstr("aaaaa", nil);
	nstr_t *mul = nstrmul(s, 0, &err);

	nstr_t *expected_msg = nstr("String is nil", nil);

	REQUIRE( mul == nil );
	REQUIRE( errnum(&err) == EFAULT );
	REQUIRE( nstreq(expected_msg, errmsg(&err), nil) );

	errput(&err);
}

TEST_CASE( "nstrmul: Error if string is nil", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *mul = nstrmul(nil, 3, &err);

	nstr_t *expected_msg = nstr("String is nil", nil);

	REQUIRE( mul == nil );
	REQUIRE( errnum(&err) == EFAULT );
	REQUIRE( nstreq(expected_msg, errmsg(&err), nil) );

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
