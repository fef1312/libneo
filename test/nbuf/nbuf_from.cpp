/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>
#include <string.h>

#include <neo.h>

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

	nstr_t *expected_msg = nstr("Data is nil", nil);

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

	nstr_t *expected_msg = nstr("Cannot create zero-size buffer", nil);

	REQUIRE( buf == nil );
	REQUIRE( errnum(&err) == ERANGE );
	REQUIRE( nstreq(expected_msg, errmsg(&err), nil) );

	errput(&err);
	nput(expected_msg);
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
