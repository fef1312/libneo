/*
 * This file demonstrates the use of the error API.
 * See the end of this file for copyright and license terms.
 *
 * Sample output:
 *   Calling fails(1, &err)
 *     fails() failed with code 22: Calling fails(1, err) does, in fact, fail
 *   Calling succeeds(2, &err)
 *     Calling succeeds(2, err) does, in fact, succeed
 *   Calling chain(3, &err)
 *     chain() failed with code 22: Calling fails(3, err) does, in fact, fail
 */

#include <errno.h>
#include <neo.h>
#include <stdio.h>

static void fails(int i, error *err)
{
	/* indicate failure */
	yeet(err, EINVAL, "Calling fails(%d, err) does, in fact, fail", i);
}

static void succeeds(int i, error *err)
{
	printf("  Calling succeeds(%d, err) does, in fact, succeed\n", i);
	/* indicate success */
	neat(err);
}

static void chain(int i, error *err)
{
	fails(i, err);
	catch(err) {
		/*
		 * pass the error up to whoever called chain().  We don't call
		 * errput() here because that is the caller's job.  See below.
		 */
		return;
	}

	printf("  this should never be reached\n");
}

void error_demo(void)
{
	error err;

	printf("Calling fails(1, &err)\n");
	fails(1, &err);
	catch(&err) {
		/* this will only be executed if the callee yeeted an error */
		printf("  fails() failed with code %u: %s\n",
			errnum(&err), nstr_raw(errmsg(&err)));

		/*
		 * you always need to call errput() in the outermost function,
		 * i.e. the function that stored the error object as a variable
		 * on its stack rather than got it passed in as a pointer.
		 * This releases memory for the error message and sets the
		 * error number to 0xffffffff.
		 */
		errput(&err);
	}

	printf("Calling succeeds(2, &err)\n");
	succeeds(2, &err);
	catch(&err) {
		printf("  succeeds() failed with code %u: %s\n",
			errnum(&err), nstr_raw(errmsg(&err)));
		errput(&err);
	}

	printf("Calling chain(3, &err)\n");
	chain(3, &err);
	catch(&err) {
		printf("  chain() failed with code %u: %s\n",
			errnum(&err), nstr_raw(errmsg(&err)));
		errput(&err);
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
