/** See the end of this file for copyright and license terms. */

#pragma once

#include "neo/_types.h"

/**
 * Throw an error.  If `err` is `nil`, the program halts.
 *
 * @param err: The error pointer passed to the callee
 * @param number: An error number appropriate for the condition,
 *	usually one from `errno.h`
 * @param fmt: If non nil, a printf-style format string followed by
 *	the values to insert which will become the error message.
 */
__attribute__(( __format__(printf, 3, 4) ))
void yeet(error *err, int number, const char *restrict fmt, ...);

/**
 * Functions accepting an error pointer must call this to indicate success.
 */
#define neat(errptr) ({			\
	if (errptr)			\
		*(errptr) = nil;	\
})

/**
 * Functions passing an error pointer must call this to acknowledge an error.
 */
void catch(error *err);

/** Get the error number */
#define errnum(err) ((err)->_number)
/** Get an optional error message, this may be `nil` */
#define errmsg(err) ((err)->_message)

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
