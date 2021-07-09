/** See the end of this file for copyright and license terms. */

.global _neo_syscall

/*
 * long _neo_syscall(long number, ...);
 *
 * We just want to get stuff working for now, therefore we don't care
 * about efficiency and just always copy all 6 arguments to the
 * respective registers and hope Linux just ignores them lmao
 *
 *   SysV ABI -> Linux syscall
 * -----------------------------
 *   1. %rdi  -> %rax (number)
 *   2. %rsi  -> %rdi (arg1)
 *   3. %rdx  -> %rsi (arg2)
 *   4. %rcx  -> %rdx (arg3)
 *   5. %r8   -> %r10 (arg4)
 *   6. %r9   -> %r8  (arg5)
 *   7. stack -> %r9  (arg6)
 */
_neo_syscall:
	mov	%rdi,	%rax
	mov	%rsi,	%rdi
	mov	%rdx,	%rsi
	mov	%rcx,	%rdx
	mov	%r8,	%r10
	mov	%r9,	%r8
	mov	(%rsp),	%r9
	syscall
	ret	/* result is already in %rax */
.size _neo_syscall,.-_neo_syscall
.type _neo_syscall,function

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
