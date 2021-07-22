/** See the end of this file for copyright and license terms. */

#include <vector>
#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>
#include <neo/hashtab.h>

extern "C" struct test_item {
	unsigned int number;
};

SCENARIO( "hashtab: items can be inserted and removed", "[src/hashtab.c]" )
{
	GIVEN( "an empty hash table" )
	{
		error err;
		hashtab_t *table = hashtab_create(32, &err);

		REQUIRE( errnum(&err) == 0 );
		REQUIRE( table != nil );

		WHEN( "a new item is inserted" )
		{
			nbuf_t *key1 = nbuf_from_str("key1", nil);
			struct test_item val1 = {
				.number = 1,
			};
			hashtab_put(table, key1, &val1, &err);
			REQUIRE( errnum(&err) == 0 );

			THEN( "the item can be retrieved again" )
			{
				nbuf_t *key1_clone = nbuf_clone(key1, nil);
				struct test_item *retrieved1 =
					(struct test_item *)hashtab_get(table, key1_clone, &err);
				REQUIRE( retrieved1 == &val1 );
				REQUIRE( errnum(&err) == 0 );
				nput(key1_clone);
			}
		}

		WHEN( "more items than buckets are inserted" )
		{
			auto keys = std::vector<nbuf_t *>(64);
			auto vals = std::vector<struct test_item>(64);
			for (unsigned int i = 0; i < 64; i++) {
				auto s = u2nstr(i, 10, nil);
				auto k = nbuf_from_nstr(s, nil);
				nput(s);
				keys[i] = k;
				vals[i].number = i;
				hashtab_put(table, k, &vals[i], &err);
				REQUIRE( errnum(&err) == 0 );
				REQUIRE( nlen(table) == i + 1 );
			}

			THEN( "items can still be retrieved" )
			{
				for (unsigned int i = 0; i < 64; i++) {
					auto val = (struct test_item *)hashtab_get(
						table,
						keys[i],
						&err
					);
					REQUIRE( val == &vals[i] );
					REQUIRE( errnum(&err) == 0 );
				}
				REQUIRE( nlen(table) == 64 );
			}

			for (unsigned int i = 0; i < 64; i++) {
				nput(keys[i]);
				/*
				 * hashtab_put must have called an additional
				 * nget on the key, otherwise this would be nil
				 */
				REQUIRE( keys[i] != nil );
			}
		}

		nput(table);
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
