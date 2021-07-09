/** See the end of this file for copyright and license terms. */

#include "neo.h"
#include "neo/_unistd.h"

/* TODO: get rid of hardcoded syscall numbers */

isize _neo_sys_write(int fd, const void *buf, usize len)
{
	return _neo_syscall(1, fd, buf, len);
}

void _neo_sys_exit(int status)
{
	_neo_syscall(60, status);
	while (1); /* should not be reached */
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
