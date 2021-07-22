/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>
#include <string.h>

#include <neo.h>

SCENARIO( "nbuf_from_nstr: Zero-copy from neo string", "[src/nbuf.c]" )
{
	const char *data = "i'm gay,,,";
	usize size = strlen(data);

	GIVEN( "a neo string" )
	{
		nbuf_t *original = nbuf_from(data, size, nil);

		WHEN( "a buffer is created from it" )
		{
			error err;
			nbuf_t *clone = nbuf_clone(original, &err);
			REQUIRE( clone != nil );
			REQUIRE( errnum(&err) == 0 );

			THEN( "the buffer's data pointer is equal to the string's" )
			{
				REQUIRE( clone->_data == original->_data );
			}

			WHEN( "the string is put" )
			{
				nput(original);
				THEN( "the original is not deallocated" )
				{
					REQUIRE( original != nil );
				}
			}

			WHEN( "the buffer is put" )
			{
				nput(clone);
				THEN( "the string is not deallocated" )
				{
					REQUIRE( clone == nil );
					REQUIRE( original->__neo_nref._count == 1 );
				}
			}
		}
	}
}

TEST_CASE( "nbuf_from_nstr: Error if string is nil", "[src/nbuf.c]" )
{
	error err;
	nbuf_t *buf = nbuf_from_nstr(nil, &err);

	nstr_t *expected_msg = nstr("String is nil", nil);

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
