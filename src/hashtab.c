/** See the end of this file for copyright and license terms. */

#include <errno.h>

#include "neo/_error.h"
#include "neo/_nalloc.h"
#include "neo/_nbuf.h"
#include "neo/_nref.h"
#include "neo/_types.h"
#include "neo/hashtab.h"
#include "neo/list.h"

static void hashtab_destroy(hashtab_t *table)
{
	for (u32 i = 0; i < table->_buckets_len; i++) {
		struct _neo_hashtab_entry *cursor;
		list_foreach(cursor, &table->_buckets[i], link) {
			nput(cursor->key);
			nfree(cursor);
		}
	}
	nfree(table);
}

hashtab_t *hashtab_create_custom(u32 buckets,
				 u32 (*hashfn)(const nbuf_t *key, u32 limit),
				 error *err)
{
	if (buckets == 0) {
		yeet(err, ERANGE, "Number of buckets is 0");
		return nil;
	}
	if (hashfn == nil) {
		yeet(err, EFAULT, "Hash function is nil");
		return nil;
	}

	struct _neo_hashtab *table;
	usize buckets_size = sizeof(table->_buckets[0]) * buckets;
	table = nalloc(sizeof(*table) + buckets_size, err);
	catch(err) {
		return nil;
	}

	table->_len = 0;
	table->_hashfn = hashfn;
	table->_buckets_len = buckets;
	for (usize i = 0; i < buckets; i++)
		list_init(&table->_buckets[i]);
	nref_init(table, hashtab_destroy);

	neat(err);
	return table;
}

/* djb2 */
static u32 hashtab_default_hashfn(const nbuf_t *key, u32 limit)
{
	u32 hash = 0;
	const u8 *cursor;

	nbuf_foreach(cursor, key) {
		hash = (hash * 33) ^ *cursor;
	}

	/* TODO: we can probably do better than this */
	return hash % limit;
}

hashtab_t *hashtab_create(u32 buckets, error *err)
{
	return hashtab_create_custom(buckets, hashtab_default_hashfn, err);
}

static u32 hashtab_compute_hash(hashtab_t *table, const nbuf_t *key, error *err)
{
	if (table == nil) {
		yeet(err, EFAULT, "Hash table is nil");
		return 0;
	}
	if (key == nil) {
		yeet(err, EFAULT, "Key is nil");
		return 0;
	}

	u32 hash = table->_hashfn(key, table->_buckets_len - 1);
	if (hash >= table->_buckets_len) {
		yeet(err, ERANGE, "Hash function returned value outside range");
		return 0;
	}

	neat(err);
	return hash;
}

static struct _neo_hashtab_entry *hashtab_find_entry(hashtab_t *table,
						     const nbuf_t *key,
						     error *err)
{
	u32 hash = hashtab_compute_hash(table, key, err);
	catch(err) {
		return nil;
	}

	list_t *bucket = &table->_buckets[hash];
	struct _neo_hashtab_entry *cursor;
	bool found = false;
	list_foreach(cursor, bucket, link) {
		if (nbuf_eq(cursor->key, key, nil)) {
			found = true;
			break;
		}
	}
	if (!found)
		cursor = nil;

	neat(err);
	return cursor;
}

void *hashtab_get(hashtab_t *table, const nbuf_t *key, error *err)
{
	struct _neo_hashtab_entry *entry = hashtab_find_entry(table, key, err);
	catch(err) {
		return nil;
	}

	if (entry == nil)
		return nil;
	else
		return entry->val;
}

void hashtab_put(hashtab_t *table, nbuf_t *key, void *val, error *err)
{
	/* TODO: avoid double hash computing */
	error get_err;
	struct _neo_hashtab_entry *existing_entry = hashtab_find_entry(table, key, err);
	catch(err) {
		return;
	}
	if (existing_entry != nil) {
		yeet(err, EEXIST, "Key already present");
		return;
	}

	u32 hash = table->_hashfn(key, table->_buckets_len - 1);
	if (hash >= table->_buckets_len) {
		yeet(err, ERANGE, "Hash function returned value out of range");
		return;
	}

	struct _neo_hashtab_entry *entry = nalloc(sizeof(*entry), err);
	catch(err) {
		return;
	}
	nget(key);
	entry->key = key;
	entry->val = val;

	list_t *bucket = &table->_buckets[hash];
	list_add(bucket, &entry->link);
	table->_len++;
	neat(err);
}

void *hashtab_del(hashtab_t *table, nbuf_t *key, error *err)
{
	struct _neo_hashtab_entry *entry = hashtab_find_entry(table, key, err);
	catch(err) {
		return nil;
	}

	if (entry != nil) {
		list_del(&entry->link);
		table->_len--;
		nput(entry->key);
		return entry->val;
	} else {
		return nil;
	}
}

int hashtab_foreach(hashtab_t *table,
		    int (*callback)(hashtab_t *table, nbuf_t *key, void *val, void *extra),
		    void *extra, error *err)
{
	if (table == nil) {
		yeet(err, EFAULT, "Hash table is nil");
		return 0;
	}
	if (callback == nil) {
		yeet(err, EFAULT, "Callback is nil");
		return 0;
	}

	int ret = 0;
	for (u32 i = 0; i < table->_buckets_len; i++) {
		struct _neo_hashtab_entry *cursor;
		list_foreach(cursor, &table->_buckets[i], link) {
			ret = callback(table, cursor->key, cursor->val, extra);
			if (ret != 0)
				break;
		}

		if (ret != 0)
			break;
	}

	neat(err);
	return ret;
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
