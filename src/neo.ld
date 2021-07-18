/* See the end of this file for copyright and license terms. */

/*
 * The INSERT command at the end makes this linker script merely augment the
 * default one rather than entirely replace it.  This allows us to inject
 * arbitrary extra sections we can reference in init and fini code without
 * having to maintain a complete linker script for each architecture.
 */

SECTIONS
{
	.__neo_data :
	{
		/*
		 * global strings defined with the NSTR_DEFINE macro are
		 * referenced in this section because their length cannot be
		 * calculated at compile time (because UTF-8).
		 *
		 * See nstr_init_array() in src/string/nstr.c for the
		 * initialization routine.
		 */
		__neo_nstr_array_start = .;
		KEEP(*(.data.__neo.nstr_array))
		__neo_nstr_array_end = .;
	}
}
INSERT AFTER .data;

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
