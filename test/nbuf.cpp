/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>
#include <string.h>

#include <neo.h>

TEST_CASE( "nbuf_create: Create regular buffer", "[src/nbuf.c]" )
{
	error err;
	nbuf_t *buf = nbuf_create(32, &err);

	REQUIRE( buf != nil );
	REQUIRE( nlen(buf) == 32 );
	REQUIRE( errnum(&err) == 0 );
}

TEST_CASE( "nbuf_create: Error if size is 0", "[src/nbuf.c]" )
{
	error err;
	nbuf_t *buf = nbuf_create(0, &err);
	string *expected_msg = nstr("Cannot create zero-size buffer", nil);

	REQUIRE( buf == nil );
	REQUIRE( errnum(&err) == ERANGE );
	REQUIRE( nstreq(errmsg(&err), expected_msg, nil) );
	errput(&err);
	nput(expected_msg);
}

TEST_CASE( "nbuf_from: Copy data", "[src/nbuf.c]" )
{
	error err;
	const char *data = "i'm gay,,,";
	usize size = strlen(data);
	nbuf_t *buf = nbuf_from(data, size, &err);

	REQUIRE( buf != nil );
	REQUIRE( nlen(buf) == size );
	REQUIRE( errnum(&err) == 0 );
	REQUIRE( memcmp(data, &buf->_data[0], size) == 0 );

	nput(buf);
}

TEST_CASE( "nbuf_from: Error if data is nil", "[src/nbuf.c]" )
{
	error err;
	nbuf_t *buf = nbuf_from(nil, 1, &err);

	string *expected_msg = nstr("Data is nil", nil);

	REQUIRE( buf == nil );
	REQUIRE( errnum(&err) == EFAULT );
	REQUIRE( nstreq(expected_msg, errmsg(&err), nil) );

	errput(&err);
	nput(expected_msg);
}

TEST_CASE( "nbuf_from: Error if size is 0", "[src/nbuf.c]" )
{
	error err;
	const char *data = "i'm gay,,,";
	nbuf_t *buf = nbuf_from(data, 0, &err);

	string *expected_msg = nstr("Cannot create zero-size buffer", nil);

	REQUIRE( buf == nil );
	REQUIRE( errnum(&err) == ERANGE );
	REQUIRE( nstreq(expected_msg, errmsg(&err), nil) );

	errput(&err);
	nput(expected_msg);
}

TEST_CASE( "nbuf_clone: Copy data", "[src/nbuf.c]" )
{
	error err;
	const char *data = "i'm gay,,,";
	usize size = strlen(data);

	nbuf_t *original = nbuf_from(data, size, nil);
	nbuf_t *clone = nbuf_clone(original, &err);

	REQUIRE( clone != nil );
	REQUIRE( nlen(clone) == nlen(original) );
	REQUIRE( errnum(&err) == 0 );
	REQUIRE( memcmp(data, &clone->_data[0], size) == 0 );

	nput(original);
	nput(clone);
}

TEST_CASE( "nbuf_clone: Error if original buffer is nil", "[src/nbuf.c]" )
{
	error err;
	nbuf_t *buf = nbuf_clone(nil, &err);

	string *expected_msg = nstr("Source buffer is nil", nil);

	REQUIRE( buf == nil );
	REQUIRE( errnum(&err) == EFAULT );
	REQUIRE( nstreq(expected_msg, errmsg(&err), nil) );

	errput(&err);
	nput(expected_msg);
}

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

	string *expected_msg = nstr("First buffer is nil", nil);

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

	string *expected_msg = nstr("Second buffer is nil", nil);

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

	string *expected_msg = nstr("First buffer is nil", nil);

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
