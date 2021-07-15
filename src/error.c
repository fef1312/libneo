/** See the end of this file for copyright and license terms. */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "neo/_error.h"
#include "neo/_nalloc.h"
#include "neo/_nref.h"
#include "neo/_stddef.h"
#include "neo/_string.h"
#include "neo/_types.h"

void yeet(error *err, u32 number, const char *restrict fmt, ...)
{
	va_list vargs;
	usize msg_size = 64;
	char *msg = nil;

	if (fmt != nil) {
		do {
			msg = nalloc(msg_size, nil);
			va_start(vargs, fmt);
			int required_size = vsnprintf(msg, msg_size, fmt, vargs);
			va_end(vargs);
			/* required_size excludes NUL, therefore >= */
			if (required_size >= msg_size) {
				msg_size = required_size + 1;
				nfree(msg);
				msg = nil;
			} else if (required_size < 0) {
				write(2, "Runtime error\n", strlen("Runtime error\n"));
				exit(1);
			}
		} while (msg == nil);
	} else {
		msg = "Runtime error";
	}

	if (err == nil) {
		write(2, msg, strlen(msg));
		exit(number);
	}

	err->_number = number;
	err->_message = nstr(msg, nil);
	nfree(msg);
}

void neat(error *err)
{
	if (err) {
		err->_number = 0;
		err->_message = nil;
	}
}

void errput(error *err)
{
	if (err != nil) {
		if (err->_message != nil)
			nput(err->_message);
		err->_number = 0xffffffff;
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
