/* See the end of this file for copyright and license terms. */

#pragma once

#include "neo/_toolchain.h"
#include "neo/_types.h"

/**
 * @defgroup nalloc Memory Management
 *
 * @{
 */

/**
 * @brief Release memory.
 *
 * @param ptr Pointer returned by `nalloc()` or `nzalloc()`
 */
void nfree(void *ptr);

/**
 * Allocate `size` bytes of memory and return a pointer to the memory region.
 * The memory is *not* initialized; use `nzalloc()` if you want it to be.
 * If `size` is 0, the allocation fails.
 * If the allocation fails, the error is set and `nil` is returned.
 *
 * @param size Desired memory size in bytes
 * @param err Error object
 */
void *nalloc(usize size, error *err) __neo_malloc(nfree, 1);

/**
 * Allocate `size` bytes of memory and return a pointer to the memory region.
 * The memory is initialized to zeroes; use `nalloc()` if you don't want that.
 * If `size` is 0, the allocation fails.
 * If the allocation fails, the error is set and `nil` is returned.
 *
 * @param size Desired memory size in bytes
 * @param err Error object
 */
void *nzalloc(usize size, error *err) __neo_malloc(nfree, 1);

/**
 * Resize an allocated memory region to fit at least `newsize` bytes and return
 * the updated pointer.  The old pointer becomes invalid.
 * If `newsize` is 0, the memory is released and `nil` is returned.
 * If `ptr` is `nil`, the function behaves like `nalloc`.
 * If allocation fails, an error is yeeted.
 *
 * @param ptr The pointer to the memory region to be expanded,
 *	as returned by `nalloc()` or `nzalloc()`
 * @param newsize The new size
 * @param err Error object
 */
void *nrealloc(void *ptr, usize newsize, error *err) __neo_malloc(nfree, 1);

/** @} */

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
