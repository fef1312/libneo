/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>

TEST_CASE( "nstr: Create a string", "[string/nstr.c]" )
{
	error err;
	nstr_t *s = nstr("i'm gay,,,", &err);

	REQUIRE( s != nil );
	REQUIRE( nlen(s) == 10 );
	REQUIRE( s->_size == 14 );
	REQUIRE( s->_data[10] == '\0' );
	REQUIRE( errnum(&err) == 0 );
	nput(s);
}

TEST_CASE( "nstr: Error if raw strig is nil", "[string/nstr,c]")
{
	error err;
	nstr_t *s = nstr(nil, &err);

	nstr_t *expected = nstr("String is nil", nil);
	nstr_t *actual = errmsg(&err);

	REQUIRE( s == nil );
	REQUIRE( errnum(&err) == EFAULT );
	REQUIRE( nstreq(expected, actual, nil) );
	errput(&err);
}

TEST_CASE( "nnstr: Create a string", "[string/nstr.c]" )
{
	error err;
	/* 10 character string, must be truncated */
	nstr_t *s = nnstr("i'm gay,,,", 8, &err);

	REQUIRE( s != nil );
	REQUIRE( nlen(s) == 8 );
	REQUIRE( s->_size == 12 );
	REQUIRE( s->_data[8] == '\0' );
	REQUIRE( errnum(&err) == 0 );
	nput(s);
}

TEST_CASE( "nnstr: Error if raw strig is nil", "[string/nstr,c]")
{
	error err;
	nstr_t *s = nnstr(nil, 10, &err);

	nstr_t *expected = nstr("String is nil", nil);
	nstr_t *actual = errmsg(&err);

	REQUIRE( s == nil );
	REQUIRE( errnum(&err) == EFAULT );
	REQUIRE( nstreq(expected, actual, nil) );
	errput(&err);
}

NSTR_DEFINE(static_test_string_1, "i'm gay,,,");

TEST_CASE( "_neo_nstr_init_array: Statically initialize ASCII string", "[string/nstr.c]" )
{
	nstr_t *expected_s1 = nstr("i'm gay,,,", nil);

	REQUIRE( nstreq(expected_s1, static_test_string_1, nil) );
	REQUIRE( nlen(static_test_string_1) == 10 );
}

NSTR_DEFINE(static_test_string_2, "i'm gay\xf0\x9f\xa5\xba,,,");

TEST_CASE( "_neo_nstr_init_array: Statically initialize UTF-8 string", "[string/nstr.c]" )
{
	nstr_t *expected_s2 = nstr("i'm gay\xf0\x9f\xa5\xba,,,", nil);

	REQUIRE( nstreq(expected_s2, static_test_string_2, nil) );
	REQUIRE( nlen(static_test_string_2) == 11 );
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
