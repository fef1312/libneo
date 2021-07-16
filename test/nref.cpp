/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>

struct nref_test {
	NREF_FIELD;
	std::function<void(void)> cb;
	nref_test(std::function<void(void)> cb)
	{
		this->cb = cb;
	}
};

void test_destroy(struct nref_test *ptr)
{
	ptr->cb();
	delete ptr;
}

SCENARIO( "nref: call destroy callback when count reaches 0", "[src/nref.c]" )
{
	GIVEN( "structure is initialized" )
	{
		bool called = false;
		struct nref_test *instance = new nref_test([&called]() {
			called = true;
		});
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
