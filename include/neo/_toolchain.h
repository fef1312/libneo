/** See the end of this file for copyright and license terms. */

#pragma once

#ifdef __clang__ /* clang doesn't support specifying a deallocator qwq */
#define __neo_malloc(deallocator, argindex) \
	__attribute__(( __malloc__ ))
#else
#define __neo_malloc(deallocator, argindex) \
	__attribute__(( __malloc__, __malloc__(deallocator, argindex) ))
#endif

#define __neo_section(name) __attribute__(( __section__(#name) ))

#define __neo_init(fn) \
	__neo_section(.init_array) static void (*__neo_init_##fn)(void) = fn

#define __neo_fini(fn) \
	__neo_section(.fini_array) static void (*__neo_fini_##fn)(void) = fn

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
