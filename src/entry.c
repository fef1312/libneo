/** See the end of this file for copyright and license terms. */

#include "neo.h"
#include "neo/buildconfig.h"

extern int main(int argc, char **argv);

/* this is only temporary to test stuff until i implement syscall() */
__attribute__((__noreturn__))
static void exit(int code)
{
	register u64 rax __asm__("rax") = 60;
	register u64 rdi __asm__("rdi") = code;
	__asm__ __volatile__ (
		"syscall"
		: "+r" (rax)
		: "r" (rdi)
		: "rcx", "r11", "memory"
	);
	while (1);
}

void _start(void)
{
	int exit_code = main(0, nil);
	exit(exit_code);
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
