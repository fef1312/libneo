/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>

TEST_CASE( "nstrdup: Duplicate a string", "[string/nstrcat.c]" )
{
	error err;
	string *s = nstr("aaaaa", nil);
	string *dup = nstrdup(s, &err);

	REQUIRE( dup != nil );
	REQUIRE( dup != s );
	REQUIRE( nstreq(s, dup, nil) );
	REQUIRE( errnum(&err) == 0 );

	nput(s);
	nput(dup);
}

TEST_CASE( "nstrdup: Error if string is nil", "[string/nstrcat.c]" )
{
	error err;
	string *dup = nstrdup(nil, &err);

	string *expected_msg = nstr("String is nil", nil);

	REQUIRE( dup == nil );
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
