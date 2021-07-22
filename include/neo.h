/** See the end of this file for copyright and license terms. */

#pragma once

#if !defined(__GNUC__) && !defined(__clang__)
#error "Only gcc and clang are supported"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "neo/_error.h"
#include "neo/_nbuf.h"
#include "neo/_nref.h"
#include "neo/_nstr.h"
#include "neo/_types.h"
#include "neo/_stddef.h"
#include "neo/_nalloc.h"

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
