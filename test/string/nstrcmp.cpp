/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>

TEST_CASE( "nstrcmp: Return 0 if strings are equal", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *s1 = nstr("aaaaa", nil);
	nstr_t *s2 = nstr("aaaaa", nil);

	int diff = nstrcmp(s1, s2, &err);

	REQUIRE( diff == 0 );
	REQUIRE( errnum(&err) == 0 );

	nput(s1);
	nput(s2);
}

TEST_CASE( "nstrcmp: Return negative if first string is empty", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *s1 = nstr("", nil);
	nstr_t *s2 = nstr("aaaaa", nil);

	int diff = nstrcmp(s1, s2, &err);

	REQUIRE( diff < 0 );
	REQUIRE( errnum(&err) == 0 );

	nput(s1);
	nput(s2);
}

TEST_CASE( "nstrcmp: Return positive if second string is empty", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *s1 = nstr("aaaaa", nil);
	nstr_t *s2 = nstr("", nil);

	int diff = nstrcmp(s1, s2, &err);

	REQUIRE( diff > 0 );
	REQUIRE( errnum(&err) == 0 );

	nput(s1);
	nput(s2);
}

TEST_CASE( "nstrcmp: Return 0 if both strings are empty", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *s1 = nstr("", nil);
	nstr_t *s2 = nstr("", nil);

	int diff = nstrcmp(s1, s2, &err);

	REQUIRE( diff == 0 );
	REQUIRE( errnum(&err) == 0 );

	nput(s1);
	nput(s2);
}

TEST_CASE( "nstrcmp: Return positive if first string is larger", "[string/nstrcat.c]" )
{
	error err;
	/* 'a' has a higher ASCII value than 'A' */
	nstr_t *s1 = nstr("aaaaa", nil);
	nstr_t *s2 = nstr("aaaAa", nil);

	int diff = nstrcmp(s1, s2, &err);

	REQUIRE( diff > 0 );
	REQUIRE( errnum(&err) == 0 );

	nput(s1);
	nput(s2);
}

TEST_CASE( "nstrcmp: Return negative if second string is larger", "[string/nstrcat.c]" )
{
	error err;
	/* 'a' has a higher ASCII value than 'A' */
	nstr_t *s1 = nstr("aaaAa", nil);
	nstr_t *s2 = nstr("aaaaa", nil);

	int diff = nstrcmp(s1, s2, &err);

	REQUIRE( diff < 0 );

	REQUIRE( errnum(&err) == 0 );

	nput(s1);
	nput(s2);
}

TEST_CASE( "nstrcmp: Error if first string is nil", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *s2 = nstr("aaaaa", nil);
	usize diff = nstrcmp(nil, s2, &err);

	nstr_t *expected_msg = nstr("First string is nil", nil);
	nstr_t *actual_msg = errmsg(&err);

	REQUIRE( diff > 0 );
	REQUIRE( errnum(&err) == EFAULT );
	REQUIRE( nstreq(expected_msg, actual_msg, nil) );

	nput(s2);
	nput(expected_msg);
	errput(&err);
}

TEST_CASE( "nstrcmp: Error if second string is nil", "[string/nstrcat.c]" )
{
	error err;
	nstr_t *s1 = nstr("aaaaa", nil);
	usize diff = nstrcmp(s1, nil, &err);

	nstr_t *expected_msg = nstr("Second string is nil", nil);
	nstr_t *actual_msg = errmsg(&err);

	REQUIRE( diff > 0 );
	REQUIRE( errnum(&err) == EFAULT );
	REQUIRE( nstreq(expected_msg, actual_msg, nil) );

	nput(s1);
	nput(expected_msg);
	errput(&err);
}

/*
 * We don't need to test for Unicode sequences because Unicode sequences are
 * designed to be able to be treated like ASCII strings in comparison operations
 * and still produce a correct result.
 */

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
