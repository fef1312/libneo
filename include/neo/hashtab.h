/* See the end of this file for copyright and license terms. */

/**
 * @file Hashtable API
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "neo/_error.h"
#include "neo/_stddef.h"
#include "neo/_types.h"
#include "neo/list.h"

struct _neo_hashtab_entry {
	listnode_t link;
	nbuf_t *key;
	void *val;
};

struct _neo_hashtab {
	NLEN_FIELD(_len);
	NREF_FIELD;
	u32 (*_hashfn)(const nbuf_t *key, u32 limit);
	u32 _buckets_len;
	list_t _buckets[0]; /* -> _neo_hashtab_entry::link */
};

/**
 * @defgroup hashtab Hashtable API
 *
 * @{
 */

/** @brief The hash table type. */
typedef struct _neo_hashtab hashtab_t;

/**
 * @brief Create a new hash table.
 *
 * The hashing function used is implementation defined; use
 * `hashtab_create_custom` to specify your own.
 * If allocation fails or `buckets` is 0, an error is yeeted.
 *
 * @param buckets Number of hash buckets
 * @param err Error pointer
 * @returns The initialized hash table, unless an error occurred
 */
hashtab_t *hashtab_create(u32 buckets, error *err);

/**
 * @brief Create a new hash table with custom hashing algorithm.
 *
 * If allocation fails, `buckets` is 0, or `hashfn` is nil, an error is yeeted.
 * The custom hash function must return a value less than the `limit` parameter
 * passed to it.  The `limit` parameter is the number of buckets minus one.
 *
 * @param buckets Number of hash buckets
 * @param hashfn Custom hash function to use
 * @param err Error pointer
 * @returns The initialized hash table, unless an error occurred
 */
hashtab_t *hashtab_create_custom(u32 buckets,
				 u32 (*hashfn)(const nbuf_t *key, u32 limit),
				 error *err);

/**
 * @brief Get an entry in a hash table.
 *
 * If the key does not exist, *no* error is yeeted and the return value is `nil`.
 * If the key is `nil` or the hash function returned a value greater than the
 * maxval parameter passed to it, an error is yeeted.
 *
 * @param table Hash table to get the entry from
 * @param key Key to get the value of
 * @param err Error pointer
 * @returns The entry or `nil` if it does not exist, unless an error occurred
 */
void *hashtab_get(hashtab_t *table, const nbuf_t *key, error *err);

/**
 * @brief Put an entry into a hash table.
 *
 * The reference counter in `key` is incremented.
 * If `key` is `nil`, `key_size` is 0, the key already exists in the table,
 * or the hash function returned a value greater than or equal to the `limit`
 * parameter passed to it, an error is yeeted.
 *
 * @param table Hash table to insert the value at
 * @param key Key to insert the value under
 * @param val Value to insert
 * @param err Error pointer
 */
void hashtab_put(hashtab_t *table, nbuf_t *key, void *val, error *err);

/**
 * @brief Delete an entry from a hash table.
 *
 * If `table` or `key` is `nil`, or the key was not found within the table,
 * an error is yeeted.
 *
 * @param table Table to delete an entry from
 * @param key Key of the item to delete
 * @param err Error pointer
 * @returns The removed item, unless an error occurred
 */
void *hashtab_del(hashtab_t *table, nbuf_t *key, error *err);

/**
 * @brief Iterate over every entry in a hash table.
 *
 * If `table` or `callback` is `nil`, an error is yeeted.
 *
 * @param table Table to iterate over
 * @param callback Callback function that is invoked for every entry;
 *	the iteration stops if the return value is nonzero
 * @param extra Optional pointer that is passed as an extra argument to the
 *	callback function
 * @returns The last return value of the callback, unless an error occurred
 */
int hashtab_foreach(hashtab_t *table,
		    int (*callback)(hashtab_t *table, nbuf_t *key, void *val, void *extra),
		    void *extra, error *err);

/** @} */

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
