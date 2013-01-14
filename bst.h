/*
 * libtree.h - this file is part of Libtree.
 *
 * Copyright (C) 2010 Franck Bui-Huu <fbuihuu@gmail.com>
 * Copyright (C) 2013 Kuzma Shapran <kuzma.shapran@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; version 2 of the
 * License.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */
#ifndef ANYTREE__BST__INCLUDED
#define ANYTREE__BST__INCLUDED

#include <stdint.h>
#include <stddef.h>

/*
 * The definition has been stolen from the Linux kernel.
 */
#ifdef __GNUC__
#  define bstree_container_of(node, type, member) ({      \
    const struct bstree_node *__mptr = (node);            \
    (type *)( (char *)__mptr - offsetof(type,member) );})
#else
#  define bstree_container_of(node, type, member)         \
    ((type *)((char *)(node) - offsetof(type, member)))
#endif    /* __GNUC__ */

/*
 * Threaded binary search tree
 */

struct bstree_node {
    struct bstree_node *left, *right;
    unsigned left_is_thread:1;
    unsigned right_is_thread:1;
};

typedef int (*bstree_cmp_fn_t)(const struct bstree_node *, const struct bstree_node *);

struct bstree {
    struct bstree_node *root;
    bstree_cmp_fn_t cmp_fn;
    struct bstree_node *first, *last;
    uint64_t reserved[4];
};

struct bstree_node *bstree_first(const struct bstree *tree);
struct bstree_node *bstree_last(const struct bstree *tree);
struct bstree_node *bstree_next(const struct bstree_node *node);
struct bstree_node *bstree_prev(const struct bstree_node *node);

struct bstree_node *bstree_lookup(const struct bstree_node *key, const struct bstree *tree);
struct bstree_node *bstree_insert(struct bstree_node *node, struct bstree *tree);
void bstree_remove(struct bstree_node *node, struct bstree *tree);
void bstree_replace(struct bstree_node *old, struct bstree_node *node, struct bstree *tree);
int bstree_init(struct bstree *tree, bstree_cmp_fn_t cmp, unsigned long flags);

#endif /* ANYTREE__BST__INCLUDED */
