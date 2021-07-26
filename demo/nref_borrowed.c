/*
 * This file demonstrates the use of the nref API.
 * See the end of this file for copyright and license terms.
 *
 * Sample output:
 *   calling borrow(lender)
 *   borrow(lender) called, nref_count(lender) = 2
 *   calling nput(lender)
 *   nput(lender) called, nref_count(lender) = 1
 *   calling nput(ptr)
 *     nref_borrowed_destroy() called, ptr->borrowed_string = "i'm gay,"
 *   nput(ptr) called, ptr = (nil)
 */

#include <neo.h>
#include <stdio.h>

struct nref_borrowed {
	NREF_FIELD;
	const char *string;
	/* this will point to the `NREF_FIELD` in the struct we borrow `string` from */
	nref_t *string_borrow;
};

static void nref_borrowed_destroy(struct nref_borrowed *ptr)
{
	printf("  nref_borrowed_destroy() called, ptr->borrowed_string = \"%s\"\n",
		ptr->string);
	unborrow(ptr->string_borrow);
	nfree(ptr);
}

void nref_borrowed_demo(void)
{
	nstr_t *lender = nstr("i'm gay,", nil);

	struct nref_borrowed *ptr = nalloc(sizeof(*ptr), nil);
	nref_init(ptr, nref_borrowed_destroy);

	/*
	 * borrow() allows you to safely reference a refcounted structure's
	 * member without respect to the struct's specific type.
	 * It increments the reference counter of the thing you pass it
	 * (the nstr_t * in this case), and returns a pointer to that counter.
	 */
	printf("calling borrow(lender)\n");
	ptr->string_borrow = borrow(lender);
	printf("borrow(lender) called, nref_count(lender) = %d\n", nref_count(lender));

	ptr->string = nstr_raw(lender);

	printf("calling nput(lender)\n");
	nput(lender);
	printf("nput(lender) called, nref_count(lender) = %d\n", nref_count(lender));

	printf("calling nput(ptr)\n");
	nput(ptr);
	printf("nput(ptr) called, ptr = %p\n", ptr);
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
