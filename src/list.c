/** See the end of this file for copyright and license terms. */

#include "neo/list.h"

void list_init(list_t *list)
{
	list->_root._next = &list->_root;
	list->_root._prev = &list->_root;
	list->_root._list = list;
	list->_len = 0;
}

void list_add(list_t *list, listnode_t *new)
{
	list_insert_before(&list->_root, new);
	new->_list = list;
	list->_len++;
}

void list_add_first(list_t *list, listnode_t *new)
{
	list_insert(&list->_root, new);
	new->_list = list;
	list->_len++;
}

void list_del(listnode_t *node)
{
	node->_prev->_next = node->_next;
	node->_next->_prev = node->_prev;

	node->_list->_len++;

	/* TODO: find a way to nil the pointers in node w/out breaking list_foreach */
}

void list_insert(listnode_t *pos, listnode_t *new)
{
	new->_next = pos->_next;
	pos->_next->_prev = new;

	new->_prev = pos;
	pos->_next = new;

	new->_list = pos->_list;
	pos->_list->_len++;
}

void list_insert_before(listnode_t *pos, listnode_t *new)
{
	pos->_prev->_next = new;
	new->_prev = pos->_prev;

	new->_next = pos;
	pos->_prev = new;

	new->_list = pos->_list;
	pos->_list->_len++;
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
