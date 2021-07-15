/** See the end of this file for copyright and license terms. */

#include <catch2/catch.hpp>
#include <errno.h>

#include <neo.h>
#include <neo/utf.h>

TEST_CASE( "utf8_strlen: ASCII string", "[string/utf.c]" )
{
	usize len = utf8_strlen("i'm gay,,,");

	REQUIRE( len == 10 );
}

TEST_CASE( "utf8_strlen: UTF-8 string", "[string/utf.c]" )
{
	usize len = utf8_strlen("i'm gay\xf0\x9f\xa5\xba,,,");

	REQUIRE( len == 11 );
}

TEST_CASE( "utf8_strlen: Empty string", "[string/utf.c]" )
{
	usize len = utf8_strlen("");

	REQUIRE( len == 0 );
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
