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
	nstr_t *expected_msg = nstr("Cannot create zero-size buffer", nil);

	REQUIRE( buf == nil );
	REQUIRE( errnum(&err) == ERANGE );
	REQUIRE( nstreq(errmsg(&err), expected_msg, nil) );
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
