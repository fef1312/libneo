/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>

TEST_CASE( "nstrcat: Concatenate two strings", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *s1 = nstr("i'm ", nil);
	nstr_t *s2 = nstr("gay,,,", nil);
	nstr_t *expected = nstr("i'm gay,,,", nil);
	nstr_t *actual = nstrcat(s1, s2, &err);

	REQUIRE( actual != nil );
	REQUIRE( nlen(actual) == 10 );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(s1);
	nput(s2);
	nput(expected);
	nput(actual);
}

TEST_CASE( "nstrcat: Concatenate two UTF-8 strings", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *s1 = nstr("i'm ", nil);
	nstr_t *s2 = nstr("gay\xf0\x9f\xa5\xba,,,", nil);
	nstr_t *expected = nstr("i'm gay\xf0\x9f\xa5\xba,,,", nil);
	nstr_t *actual = nstrcat(s1, s2, &err);

	REQUIRE( actual != nil );
	REQUIRE( nlen(actual) == 11 );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(s1);
	nput(s2);
	nput(expected);
	nput(actual);
}

TEST_CASE( "nstrcat: Concatenate two empty strings", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *s1 = nstr("", nil);
	nstr_t *s2 = nstr("", nil);
	nstr_t *expected = nstr("", nil);
	nstr_t *actual = nstrcat(s1, s2, &err);

	REQUIRE( actual != nil );
	REQUIRE( nlen(actual) == 0 );
	REQUIRE( nstreq(expected, actual, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(s1);
	nput(s2);
	nput(expected);
	nput(actual);
}

TEST_CASE( "nstrcat: Error if first string is nil", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *s2 = nstr("", nil);
	nstr_t *cat = nstrcat(nil, s2, &err);

	nstr_t *expected_msg = nstr("First string is nil", nil);
	nstr_t *actual_msg = errmsg(&err);

	REQUIRE( cat == nil );
	REQUIRE( errnum(&err) == EFAULT );
	REQUIRE( nstreq(expected_msg, actual_msg, nil) );

	nput(s2);
	nput(expected_msg);
	errput(&err);
}

TEST_CASE( "nstrcat: Error if second string is nil", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *s1 = nstr("", nil);
	nstr_t *cat = nstrcat(s1, nil, &err);

	nstr_t *expected_msg = nstr("Second string is nil", nil);
	nstr_t *actual_msg = errmsg(&err);

	REQUIRE( cat == nil );
	REQUIRE( errnum(&err) == EFAULT );
	REQUIRE( nstreq(expected_msg, actual_msg, nil) );

	nput(s1);
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
