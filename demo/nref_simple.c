/*
 * This file demonstrates the use of the nref API.
 * See the end of this file for copyright and license terms.
 *
 * Sample output:
 *   nref_init() called, refcount is 1
 *   nget() called, refcount = 2, ptr = 0x55c4fddef6b0
 *   nput() called, refcount = 1, ptr = 0x55c4fddef6b0
 *   nref_simple_destroy() called, ptr->data = 69, releasing memory
 *   nput() called again, refcount = 0, ptr = (nil)
 */

#include <neo.h>
#include <stdio.h>

struct nref_simple {
	/*
	 * put this macro anywhere in your struct (doesn't have to be the first
	 * member) to enable refcounting.  Initialize the refcounter with
	 * nref_init() and increment/decrement it using nget() and nput().
	 */
	NREF_FIELD;
	nstr_t *string;
};

static void nref_simple_destroy(struct nref_simple *ptr)
{
	printf("  nref_simple_destroy() called, ptr->string = \"%s\"\n",
		nstr_raw(ptr->string));

	nput(ptr->string);
	nfree(ptr);
}

void nref_simple_demo(void)
{
	/*
	 * no need to check for errors here because the error pointer passed
	 * to nalloc() is nil.  This means that if an error is yeeted, the
	 * error message is printed to stderr and the program terminates.
	 */
	struct nref_simple *ptr = nalloc(sizeof(*ptr), nil);

	/* again, no error checking required */
	ptr->string = nstr("i'm gay,,", nil);

	/*
	 * the nref_init() macro typechecks the callback signature
	 * so that you can't accidentally pass a wrong method name
	 */
	nref_init(ptr, nref_simple_destroy);
	printf("ptr instantiated, nref_count(ptr) = %d\n", nref_count(ptr));

	printf("calling nget(ptr)\n");
	nget(ptr);
	printf("nget(ptr) called, nref_count(ptr) = %d, ptr = %p\n", nref_count(ptr), ptr);

	printf("calling nput(ptr)\n");
	nput(ptr);
	printf("nput(ptr) called, nref_count(ptr) = %d, ptr = %p\n", nref_count(ptr), ptr);

	printf("calling nput(ptr) again\n");
	nput(ptr);
	printf("nput(ptr) called again, ptr = %p\n", ptr);
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
