/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>
#include <string.h>

#include <neo.h>

SCENARIO( "nbuf_clone: Zero-copy clone", "[src/nbuf.c]" )
{
	const char *data = "i'm gay,,,";
	usize size = strlen(data);

	GIVEN( "a populated buffer" )
	{
		nbuf_t *original = nbuf_from(data, size, nil);

		WHEN( "the buffer is cloned" )
		{
			error err;
			nbuf_t *clone = nbuf_clone(original, &err);
			REQUIRE( clone != nil );
			REQUIRE( errnum(&err) == 0 );

			THEN( "the clone's data pointer is equal to the original" )
			{
				REQUIRE( clone->_data == original->_data );
			}

			WHEN( "the original buffer is put" )
			{
				nput(original);
				THEN( "the original is not deallocated" )
				{
					REQUIRE( original != nil );
				}
			}

			WHEN( "the cloned buffer is put" )
			{
				nput(clone);
				THEN( "the original is not deallocated" )
				{
					REQUIRE( clone == nil );
					REQUIRE( original->__neo_nref._count == 1 );
				}
			}
		}
	}
}

TEST_CASE( "nbuf_clone: Error if original buffer is nil", "[src/nbuf.c]" )
{
	error err;
	nbuf_t *buf = nbuf_clone(nil, &err);

	nstr_t *expected_msg = nstr("Source buffer is nil", nil);

	REQUIRE( buf == nil );
	REQUIRE( errnum(&err) == EFAULT );
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
