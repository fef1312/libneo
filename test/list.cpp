/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>
#include <neo/list.h>

extern "C" struct list_test {
	int number;
	/* link is not at the beginning to ensure offsets are subtracted */
	listnode_t link;
};

SCENARIO( "list: items can be added and removed", "[src/list.c]" )
{
	GIVEN( "list is initialized" )
	{
		list_t list = {
			._len = 0,
		};
		list_init(&list);

		REQUIRE( nlen(&list) == 0 );

		WHEN( "one item is added" )
		{
			struct list_test item1 = {
				.number = 1,
			};
			list_add(&list, &item1.link);

			THEN( "item is in the list" )
			{
				REQUIRE( nlen(&list) == 1 );
				struct list_test *cursor;
				int iterations = 0;
				list_foreach(cursor, &list, link) {
					iterations++;
					REQUIRE( cursor == &item1 );
					REQUIRE( cursor->number == 1 );
				}
				REQUIRE( iterations == 1 );
			}

			WHEN( "item is removed again" )
			{
				list_del(&item1.link);

				THEN( "list is empty" )
				{
					REQUIRE( nlen(&list) == 0 );
					struct list_test *cursor;
					int iterations = 0;
					list_foreach(cursor, &list, link) {
						iterations++;
					}
					REQUIRE( iterations == 0 );
				}
			}

			WHEN( "another item is added" )
			{
				struct list_test item2 = {
					.number = 2,
				};
				list_add(&list, &item2.link);

				THEN( "new item is in position 2")
				{
					REQUIRE( nlen(&list) == 2 );
					struct list_test *cursor;
					int iterations = 0;
					list_foreach(cursor, &list, link) {
						iterations++;
						REQUIRE( cursor->number == iterations );
					}
					REQUIRE( iterations == 2 );
				}
			}
		}
	}
}

SCENARIO( "list: items are inserted at the right position", "[src/list.c]" )
{
	GIVEN( "list is initialized and populated" )
	{
		list_t list = {
			/* required because C++ i think */
			._len = 0,
		};
		list_init(&list);

		REQUIRE( nlen(&list) == 0 );

		struct list_test item1 = {
			.number = 1,
		};
		list_add(&list, &item1.link);
		struct list_test item2 = {
			.number = 2,
		};
		list_add(&list, &item2.link);

		WHEN( "item is added at the end" )
		{
			struct list_test item3 = {
				.number = 3,
			};
			list_add(&list, &item3.link);

			THEN( "item is at the end" )
			{
				struct list_test *cursor;
				int number = 0;
				list_foreach(cursor, &list, link) {
					number++;
					REQUIRE( cursor->number == number );
				}
				REQUIRE( number == 3 );
			}
		}

		WHEN( "item is added at the beginning" )
		{
			struct list_test item0 = {
				.number = 0,
			};
			list_add_first(&list, &item0.link);

			THEN( "item is at the beginning" )
			{
				struct list_test *cursor;
				int number = -1;
				list_foreach(cursor, &list, link) {
					number++;
					REQUIRE( cursor->number == number );
				}
				REQUIRE( number == 2 );
			}
		}

		WHEN( "item is inserted after position 1" )
		{
			struct list_test item11 = {
				.number = 11,
			};
			list_insert(&item1.link, &item11.link);

			THEN( "item is at position 2" )
			{
				struct list_test *cursor;
				int i = 0;
				static const int numbers[] = { 1, 11, 2 };
				list_foreach(cursor, &list, link) {
					REQUIRE( cursor->number == numbers[i] );
					i++;
				}
				REQUIRE( i == 3 );
			}
		}

		WHEN( "item is inserted before position 2" )
		{
			struct list_test item11 = {
				.number = 11,
			};
			list_insert_before(&item2.link, &item11.link);

			THEN( "item is at position 2" )
			{
				struct list_test *cursor;
				int i = 0;
				static const int numbers[] = { 1, 11, 2 };
				list_foreach(cursor, &list, link) {
					REQUIRE( cursor->number == numbers[i] );
					i++;
				}
				REQUIRE( i == 3 );
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
