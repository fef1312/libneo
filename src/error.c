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
#include "neo/_toolchain.h"
#include "neo/_types.h"

/* flags for the error structure */
#define NEO_ERR_CAUGHT		(1 << 0)

/* TODO: we need one of these for every thread */
static struct _neo_error _neo_error_instance = {
	._number = 0,
	._message = nil,
	._flags = NEO_ERR_CAUGHT,
};

void yeet(error *err, int number, const char *restrict fmt, ...)
{
	va_list vargs;
	usize msg_capacity = 64;
	char *msg = nil;
	int printf_ret;

	if (fmt != nil) {
		do {
			msg = nalloc(msg_capacity, nil);
			va_start(vargs, fmt);
			printf_ret = vsnprintf(msg, msg_capacity, fmt, vargs);
			va_end(vargs);
			if (printf_ret > 0) {
				msg_capacity += printf_ret;
				nfree(msg);
				msg = nil;
			} else if (printf_ret < 0) {
				write(1, "Runtime error\n", 14);
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

	*err = &_neo_error_instance;
	(*err)->_number = number;
	(*err)->_message = nstr(msg, nil);
	(*err)->_flags &= ~NEO_ERR_CAUGHT;
}

void catch(error *err)
{
	if ((*err)->_message)
		nput((*err)->_message);
	(*err)->_flags |= NEO_ERR_CAUGHT;
	*err = nil;
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
