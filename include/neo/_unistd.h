/** See the end of this file for copyright and license terms. */

#pragma once

#include "neo.h"

long _neo_syscall(long number, ...);

isize _neo_sys_write(int fd, const void *buf, usize count);
__attribute__((__noreturn__))
void _neo_sys_exit(int status);

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
