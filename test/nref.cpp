/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>

/*
 * nref_init uses offsetof internally to be able to cast the nref_t field out
 * to the containing structure which is then passed to the destroy callback if
 * the refcount reached zero.  Neither gcc nor Clang seem to like using offsetof
 * in certain structures containing fields only valid in C++, and since libneo
 * is specifically meant to be used in plain C code anyway we just declare the
 * test structure as extern to make sure we actually test the behavior of the C
 * code rather than the fun quirks C++ is infamous for.
 */
extern "C" struct nref_test {
	bool *called;
	/* NREF_FIELD is not at the beginning to ensure offsets are subtracted */
	NREF_FIELD;
};

void test_destroy(struct nref_test *ptr)
{
	*ptr->called = true;
	delete ptr;
}

SCENARIO( "nref: call destroy callback when count reaches 0", "[src/nref.c]" )
{
	GIVEN( "structure is initialized" )
	{
		bool called = false;
		struct nref_test *instance = new nref_test();
		instance->called = &called;
		nref_init(instance, test_destroy);

		REQUIRE( !called );

		WHEN( "nget is called" )
		{
			nget(instance);

			THEN( "destroy is not called" )
			{
				REQUIRE( !called );
			}
		}

		WHEN( "nput is called" )
		{
			nput(instance);

			THEN( "destroy is called" )
			{
				REQUIRE( instance == nil );
			}
		}

		WHEN( "nget is called, then nput is called twice" )
		{
			nget(instance);
			nput(instance);
			nput(instance);

			THEN( "destroy is called" )
			{
				REQUIRE( called );
			}
		}
	}
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
