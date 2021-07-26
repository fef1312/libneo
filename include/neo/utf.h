/* See the end of this file for copyright and license terms. */

/**
 * @file Conversion utilities for raw UTF.
 *
 * Note that libneo strings already have native UTF-8 support, so you only
 * really need this if you explicitly need to deal with different encodings or
 * raw bytes, in which case i am very sorry.
 *
 * Special attention must be paid to methods reading raw UTF from `char *`
 * parameters, as they may read a few bytes beyond the memory region allocated
 * for them if the string contains a malformed UTF sequence.
 *
 * Believe me when i say you do not want to use these.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "neo/_toolchain.h"
#include "neo/_types.h"

/**
 * @brief Check whether a NUL terminated string is valid UTF-8.
 *
 * If the string contains any malformed code sequences, an error is yeeted.
 *
 * @param s String to validate
 * @param err Error pointer
 * @returns The number of UTF-8 code points (i.e. number of Unicode characters)
 *	excluding the terminating NUL byte; undefined on error
 */
usize utf8_check(const char *restrict s, error *err);

/**
 * @brief Check whether a NUL terminated string is valid UTF-8.
 * At most `maxsize + 3` bytes are read (this function uses `utf8_to_nchr` internally).
 *
 * If a NUL terminator is encountered before `maxsize` bytes, reading stops
 * before the specified size.  If the string contains any malformed code
 * sequences, an error is yeeted.
 *
 * @param s String to validate
 * @param maxsize Maximum amount of byte to read from `s`
 * @param err Error pointer
 * @returns The number of UTF-8 code points (i.e. number of Unicode characters)
 *	excluding the terminating NUL byte; undefined on error
 */
usize utf8_ncheck(const char *restrict s, usize maxsize, error *err);

/**
 * @brief Compute the length of a raw UTF-8 encoded, NUL terminated string.
 *
 * The string is *not* checked for malformed code sequences,
 * use `utf8_check` for that.
 *
 * @param s String to get the length of
 * @returns String length as in Unicode code points (not bytes),
 *	excluding the terminating NUL byte
 */
usize utf8_strlen(const char *restrict s);

/**
 * @brief Get the amount of bytes a Unicode character takes up in UTF-8.
 *
 * If the character is outside of the Unicode range (`0x00000000`~`0x0010ffff`),
 * an error is yeeted.
 *
 * @param c The character
 * @param err Error pointer
 * @returns The amount of bytes needed to store the character in UTF-8 encoding,
 *	which is always between 1 and 4 except on errors
 */
usize utf8_chrsize(nchar c, error *err);

/**
 * @brief UTF-8 encode a Unicode character and store it in `dest` with NUL terminator.
 *
 * The buffer needs to hold at least 5 bytes.  If the character is outside of
 * the Unicode range (`0x00000000`~`0x0010ffff`), an error is yeeted and the
 * buffer is not modified.
 *
 * @param dest Where to store the encoded character (*not* NUL terminated)
 * @param c Character to encode
 * @param err Error pointer
 * @returns The amount of bytes taken up by the character,
 *	which is always between 1 and 4 except on errors
 */
usize utf8_from_nchr(char *restrict dest, nchar c, error *err);

/**
 * @brief Decode a UTF-8 character and store it in `c`.
 *
 * If the character encoding is malformed, an error is yeeted and `c` is set to
 * the ASCII NUL character.  The encoded character does not need to be NUL
 * terminated.  The amount of bytes read from the buffer depends on the first
 * byte which marks the beginning of the Unicode code point.  Keep in mind that
 * this may cause the method to read up to 3 bytes over the end of the buffer
 * if the code sequence is malformed.
 *
 * @param c Where to store the decoded character
 * @param utf8chr UTF-8 encoded character sequence
 * @param err Error pointer
 * @returns The amount of bytes the character took up when encoded as UTF-8,
 *	which is always between 1 and 4 except on errors
 */
usize utf8_to_nchr(nchar *c, const char *restrict utf8chr, error *err);

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
