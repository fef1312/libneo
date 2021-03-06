/* See the end of this file for copyright and license terms. */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "neo/_stddef.h"
#include "neo/_types.h"

struct _neo_list;

/** @private */
struct _neo_listnode {
	struct _neo_listnode *_next;
	struct _neo_listnode *_prev;
	struct _neo_list *_list;
};
/**
 * @brief List node anchor for embedding into your own structure.
 *
 * @ingroup list
 */
typedef struct _neo_listnode listnode_t;

/** @private */
struct _neo_list {
	struct _neo_listnode _root;
	NLEN_FIELD(_len);
};
/**
 * @brief List data type
 *
 * @ingroup list
 */
typedef struct _neo_list list_t;

/**
 * When casting out from a @a `listnode_t` to its supposed containing structure
 * (in a loop), it is possible that it was in fact the @a `list_t` that contained
 * the @a `listnode_t`.  This macro checks whether that is the case.
 *
 * @param casted `struct *` that the @a `listnode_t *` was casted out to
 * @param list @a `list_t *` storing the root @a `listnode_t`
 * @param member Name of the @a `listnode_t` member embedded within the `struct *`
 * @private
 */
#define _neo_list_is_root(casted, list, member) \
	( &(casted)->member == &(list)->_root )

/*
 * we use u8 * for pointer arithmetic here because this is code is compiled with
 * external compiler settings which my complain about calculating with void *
 */

/** @private */
#define _neo_list_first(list, type, member) \
	((type *)( (u8 *)((list)->_root._next) - offsetof(type, member) ))

/** @private */
#define _neo_list_last(list, type, member) \
	((type *)( (u8 *)((list)->_root._prev) - offsetof(type, member) ))

/** @private */
#define _neo_list_next(current, member) \
	((typeof(current))( (u8 *)((current)->member._next) - offsetof(typeof(*(current)), member) ))

/** @private */
#define _neo_list_prev(current, member) \
	((typeof(current))( (u8 *)((current)->member._prev) - offsetof(typeof(*(current)), member) ))

/**
 * @defgroup list List API
 *
 * @{
 */

/**
 * @brief Initialize a list.
 *
 * @param list The list
 */
void list_init(list_t *list);

/**
 * @brief Append a new node to the end of a list.
 *
 * @param list List to append to
 * @param new_node New node to append
 */
void list_add(list_t *list, listnode_t *new_node);

/**
 * @brief Remove a node from a list.
 *
 * @param node Node to remove
 */
void list_del(listnode_t *node);

/**
 * @brief Insert a new node to the beginning of a list.
 *
 * @param list List to insert the node into
 * @param new_node New node to insert
 */
void list_add_first(list_t *list, listnode_t *new_node);

/**
 * @brief Insert a new node after the specified list node.
 *
 * @param pos List node to insert the new node after
 * @param new_node Node to insert after the specified position
 */
void list_insert(listnode_t *pos, listnode_t *new_node);

/**
 * @brief Insert a new node before the specified list node.
 *
 * @param pos List node to insert the new node before
 * @param new_node Node to insert before the specified position
 */
void list_insert_before(listnode_t *pos, listnode_t *new_node);

/**
 * @brief Iterate over each item in a list.
 *
 * The current entry can be safely removed from the list.
 *
 * @param cursor `type *` to use as a cursor
 * @param list `list_t *` to iterate over
 * @param member Name of the `listnode_t` member embedded within `cursor`
 */
#define list_foreach(cursor, list, member)					\
	for (typeof(cursor) __tmp = _neo_list_next(				\
		cursor = _neo_list_first( list, typeof(*(cursor)), member ),	\
		member								\
	     );									\
	     !_neo_list_is_root(cursor, list, member);				\
	     cursor = __tmp, __tmp = _neo_list_next(__tmp, member))

/**
 * @brief Iterate over each item in a list in reverse order.
 *
 * The current entry can be safely removed from the list.
 *
 * @param cursor `type *` to use as a cursor
 * @param list `list_t *` to iterate over
 * @param member Name of the `listnode_t` member embedded within `cursor`
 */
#define list_foreach_reverse(cursor, list, member)				\
	for (typeof(cursor) __tmp = _neo_list_prev(				\
		cursor = _neo_list_last( list, typeof(*(cursor)), member ),	\
		member								\
	     );									\
	     !_neo_list_is_root(cursor, list, member);				\
	     cursor = __tmp, __tmp = _neo_list_prev(__tmp, member))

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
