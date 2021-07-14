/** See the end of this file for copyright and license terms. */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "neo/_types.h"

/**
 * Throw an error.  If `err` is `nil`, the program halts.
 * Functions accepting an `err` object must call either `yeet` or `neat`
 * on the object exactly once, or the behavior is undefined.
 * If a function yeets an error, its return value is undefined.
 *
 * @param err: The error pointer passed to the callee
 * @param number: An error number appropriate for the condition,
 *	usually one from `errno.h`
 * @param fmt: If non nil, a printf-style format string followed by
 *	the values to insert which will become the error message.
 */
__attribute__(( __format__(printf, 3, 4) ))
void yeet(error *err, u32 number, const char *restrict fmt, ...);

/**
 * Indicate an operation has completed successfully.
 * Functions accepting an `error` pointer must call either `yeet` or `neat`,
 * or the begavior is undefined.
 *
 * @param err: Error object
 */
void neat(error *err);

/**
 * Release any resources allocated for an error.
 * This must always be called within the catch block of the outermost calling
 * function, i.e. the one that declared the error variable (not the ones just
 * accepting an error * argument and passing it through to further calls).
 *
 * Put another way, you probably need to call this if you had to put an `&`
 * before the error variable for passing it into `catch`.
 *
 * @param err: Error object to destroy
 */
void errput(error *err);

/**
 * Execute the expression after this macro call if the error pointed to
 * by `err` is an actual error, i.e. it has been `yeet`ed to.
 * Resources for the error must be released using `nput`.
 */
#define ncatch(err) if ((err) != nil && (err)->_number != 0)
#ifndef __cplusplus
#	define catch(err) ncatch(err)
#endif

/**
 * Get the error number.
 * Must only be used within a catch block and before `errput` is called.
 */
#define errnum(err) ((err) == nil ? 0 : (err)->_number)

/**
 * Get an optional error message, this may be `nil`
 * Must only be used within a catch block and before `errput` is called.
 */
#define errmsg(err) ((err) == nil ? nil : (err)->_message)

#ifdef __cplusplus
}; /* extern "C" */
#endif

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
