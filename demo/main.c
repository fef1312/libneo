/*
 * This example program demonstrates various features of libneo.
 * See the end of this file for copyright and license terms.
 */

#include <neo.h>
#include <stdio.h>

void nref_simple_demo(void);
void nref_borrowed_demo(void);
void error_demo(void);

int main(int argc, char **argv)
{
	printf("==== running nref_simple_demo ====\n");
	nref_simple_demo();
	printf("==== end of nref_simple_demo ====\n\n");

	printf("==== running nref_borrowed_demo ====\n");
	nref_borrowed_demo();
	printf("==== end of nref_borrowed_demo ====\n\n");

	printf("==== running error_demo ====\n");
	error_demo();
	printf("==== end of error_demo ====\n\n");
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
