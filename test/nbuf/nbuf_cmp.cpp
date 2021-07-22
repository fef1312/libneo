/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>
#include <string.h>

#include <neo.h>

TEST_CASE( "nbuf_cmp: Return 0 if buffers are equal", "[src/nbuf.c]" )
{
	error err;
	const char *data = "aaaaa";
	usize size = strlen(data);

	nbuf_t *original = nbuf_from(data, size, nil);
	nbuf_t *clone = nbuf_clone(original, nil);

	int diff = nbuf_cmp(original, clone, &err);

	REQUIRE( diff == 0 );
	REQUIRE( errnum(&err) == 0 );

	nput(original);
	nput(clone);
}

TEST_CASE( "nbuf_cmp: Return positive if buffer 1 > buffer 2", "[src/nbuf.c]" )
{
	error err;
	const char *data = "aaaaa";
	usize size = strlen(data);

	nbuf_t *buf1 = nbuf_from(data, size, nil);
	nbuf_t *buf2 = nbuf_from(data, size - 1, nil);

	int diff = nbuf_cmp(buf1, buf2, &err);

	REQUIRE( diff > 0 );
	REQUIRE( errnum(&err) == 0 );

	nput(buf1);
	nput(buf2);
}

TEST_CASE( "nbuf_cmp: Return negative if buffer 1 < buffer 2", "[src/nbuf.c]" )
{
	error err;
	const char *data = "aaaaa";
	usize size = strlen(data);

	nbuf_t *buf1 = nbuf_from(data, size - 1, nil);
	nbuf_t *buf2 = nbuf_from(data, size, nil);

	int diff = nbuf_cmp(buf1, buf2, &err);

	REQUIRE( diff < 0 );
	REQUIRE( errnum(&err) == 0 );

	nput(buf1);
	nput(buf2);
}

TEST_CASE( "nbuf_cmp: Error if first buffer is nil", "[src/nbuf.c]" )
{
	error err;
	const char *data = "aaaaa";
	usize size = strlen(data);

	nbuf_t *buf2 = nbuf_from(data, size, nil);
	int diff = nbuf_cmp(nil, buf2, &err);

	nstr_t *expected_msg = nstr("First buffer is nil", nil);

	REQUIRE( diff < 0 );
	REQUIRE( errnum(&err) == EFAULT );
	REQUIRE( nstreq(expected_msg, errmsg(&err), nil) );

	errput(&err);
	nput(buf2);
}

TEST_CASE( "nbuf_cmp: Error if second buffer is nil", "[src/nbuf.c]" )
{
	error err;
	const char *data = "aaaaa";
	usize size = strlen(data);

	nbuf_t *buf1 = nbuf_from(data, size, nil);
	int diff = nbuf_cmp(buf1, nil, &err);

	nstr_t *expected_msg = nstr("Second buffer is nil", nil);

	REQUIRE( diff > 0 );
	REQUIRE( errnum(&err) == EFAULT );
	REQUIRE( nstreq(expected_msg, errmsg(&err), nil) );

	errput(&err);
	nput(buf1);
}

TEST_CASE( "nbuf_cmp: Error if both buffers are nil", "[src/nbuf.c]" )
{
	error err;

	int diff = nbuf_cmp(nil, nil, &err);

	nstr_t *expected_msg = nstr("First buffer is nil", nil);

	REQUIRE( diff == 0 );
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
