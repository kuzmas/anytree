/*
 * avl.h - this file is part of Anytree.
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
#ifndef ANYTREE__AVL__INCLUDED
#define ANYTREE__AVL__INCLUDED

#include <stdint.h>
#include <stddef.h>

/*
 * The definition has been stolen from the Linux kernel.
 */
#ifdef __GNUC__
#  define avltree_container_of(node, type, member) ({      \
    const struct avltree_node *__mptr = (node);            \
    (type *)( (char *)__mptr - offsetof(type,member) );})
#else
#  define avltree_container_of(node, type, member)         \
    ((type *)((char *)(node) - offsetof(type, member)))
#endif    /* __GNUC__ */

/*
 * AVL tree
 */

struct avltree;

struct avltree_node {
    struct avltree *tree;
    struct avltree_node *left, *right;
    struct avltree_node *parent;
    signed balance:3;        /* balance factor [-2:+2] */
};

typedef int (*avltree_cmp_fn_t)(const struct avltree_node *, const struct avltree_node *);

struct avltree {
    avltree_cmp_fn_t cmp_fn;
    unsigned size;

    struct avltree_node *root;
    struct avltree_node *first, *last;

    int height;
};

struct avltree_node *avltree_first(const struct avltree *tree);
struct avltree_node *avltree_last(const struct avltree *tree);
struct avltree_node *avltree_next(const struct avltree_node *node);
struct avltree_node *avltree_prev(const struct avltree_node *node);

struct avltree_node *avltree_lookup(const struct avltree_node *key, const struct avltree *tree);
struct avltree_node *avltree_insert(struct avltree_node *node, struct avltree *tree);
void avltree_remove(struct avltree_node *node, struct avltree *tree);
void avltree_replace(struct avltree_node *old, struct avltree_node *node, struct avltree *tree);

#define avltree_is_empty(TREE) (TREE->size == 0)
#define avltree_size(TREE) (TREE->size)

int avltree_init(struct avltree *tree, avltree_cmp_fn_t cmp);

#endif /* ANYTREE__AVL__INCLUDED */
