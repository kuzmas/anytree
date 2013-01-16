/*
 * splay.h - this file is part of Anytree.
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
#ifndef ANYTREE__SPLAY__INCLUDED
#define ANYTREE__SPLAY__INCLUDED

#include <stdint.h>
#include <stddef.h>

/*
 * The definition has been stolen from the Linux kernel.
 */
#ifdef __GNUC__
#  define splaytree_container_of(node, type, member) ({      \
    const struct splaytree_node *__mptr = (node);            \
    (type *)( (char *)__mptr - offsetof(type,member) );})
#else
#  define splaytree_container_of(node, type, member)         \
    ((type *)((char *)(node) - offsetof(type, member)))
#endif    /* __GNUC__ */

/*
 * Splay tree
 */

struct splaytree;

struct splaytree_node {
    struct splaytree *tree;
    struct splaytree_node *left, *right;
    unsigned left_is_thread:1;
    unsigned right_is_thread:1;
};

typedef int (*splaytree_cmp_fn_t)(const struct splaytree_node *, const struct splaytree_node *);

struct splaytree {
    splaytree_cmp_fn_t cmp_fn;
    unsigned size;

    struct splaytree_node *root;
    struct splaytree_node *first, *last;
};

struct splaytree_node *splaytree_first(const struct splaytree *tree);
struct splaytree_node *splaytree_last(const struct splaytree *tree);
struct splaytree_node *splaytree_next(const struct splaytree_node *node);
struct splaytree_node *splaytree_prev(const struct splaytree_node *node);

struct splaytree_node *splaytree_lookup(const struct splaytree_node *key, struct splaytree *tree);
struct splaytree_node *splaytree_insert( struct splaytree_node *node, struct splaytree *tree);
void splaytree_remove(struct splaytree_node *node, struct splaytree *tree);
void splaytree_replace(struct splaytree_node *old, struct splaytree_node *node, struct splaytree *tree);

#define splaytree_is_empty(TREE) (TREE->size == 0)
#define splaytree_size(TREE) (TREE->size)

int splaytree_init(struct splaytree *tree, splaytree_cmp_fn_t cmp);
void splaytree_clean(struct splaytree *tree);

#endif /* ANYTREE__SPLAY__INCLUDED */
