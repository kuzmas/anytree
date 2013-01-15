/*
 * rb.h - this file is part of Anytree.
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
#ifndef ANYTREE__RB__INCLUDED
#define ANYTREE__RB__INCLUDED

#include <stdint.h>
#include <stddef.h>

/*
 * The definition has been stolen from the Linux kernel.
 */
#ifdef __GNUC__
#  define rbtree_container_of(node, type, member) ({      \
    const struct rbtree_node *__mptr = (node);            \
    (type *)( (char *)__mptr - offsetof(type,member) );})
#else
#  define rbtree_container_of(node, type, member)         \
    ((type *)((char *)(node) - offsetof(type, member)))
#endif    /* __GNUC__ */

/*
 * Red-black tree
 */
enum rb_color {
    RB_BLACK,
    RB_RED
};

struct rbtree;

struct rbtree_node {
    struct rbtree *tree;
    struct rbtree_node *left, *right;
    struct rbtree_node *parent;
    enum rb_color color;
};

typedef int (*rbtree_cmp_fn_t)(const struct rbtree_node *, const struct rbtree_node *);

struct rbtree {
    rbtree_cmp_fn_t cmp_fn;

    struct rbtree_node *root;
    struct rbtree_node *first, *last;
};

struct rbtree_node *rbtree_first(const struct rbtree *tree);
struct rbtree_node *rbtree_last(const struct rbtree *tree);
struct rbtree_node *rbtree_next(const struct rbtree_node *node);
struct rbtree_node *rbtree_prev(const struct rbtree_node *node);

struct rbtree_node *rbtree_lookup(const struct rbtree_node *key, const struct rbtree *tree);
struct rbtree_node *rbtree_insert(struct rbtree_node *node, struct rbtree *tree);
void rbtree_remove(struct rbtree_node *node, struct rbtree *tree);
void rbtree_replace(struct rbtree_node *old, struct rbtree_node *node, struct rbtree *tree);

int rbtree_init(struct rbtree *tree, rbtree_cmp_fn_t cmp);

#endif /* ANYTREE__RB__INCLUDED */
