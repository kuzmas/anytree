/*
 * any.h - this file is part of Libtree.
 *
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
#ifndef ANYTREE__ANY__INCLUDED
#define ANYTREE__ANY__INCLUDED

#include "avl.h"
#include "bs.h"
#include "rb.h"
#include "splay.h"

/*
 * The definition has been stolen from the Linux kernel.
 */
#ifdef __GNUC__
#  define anytree_container_of(node, type, member) ({      \
    const struct anytree_node *__mptr = (node);            \
    (type *)( (char *)__mptr - offsetof(type,member) );})
#else
#  define anytree_container_of(node, type, member)         \
    ((type *)((char *)(node) - offsetof(type, member)))
#endif    /* __GNUC__ */

/*
 * any tree
 */
struct anytree;

struct anytree_node {
    union {
        struct anytree *tree;
        struct avltree_node avl;
        struct bstree_node bs;
        struct rbtree_node rb;
        struct splaytree_node splay;
    };
};

typedef int (*anytree_cmp_fn_t)(const struct anytree_node *, const struct anytree_node *);

typedef struct anytree_node * (*anytree_first_fn_t)(const struct anytree *tree);
typedef struct anytree_node * (*anytree_last_fn_t)(const struct anytree *tree);
typedef struct anytree_node * (*anytree_next_fn_t)(const struct anytree_node *node);
typedef struct anytree_node * (*anytree_prev_fn_t)(const struct anytree_node *node);

typedef struct anytree_node * (*anytree_lookup_fn_t)(const struct anytree_node *key, const struct anytree *tree);
typedef struct anytree_node * (*anytree_insert_fn_t)(struct anytree_node *node, struct anytree *tree);
typedef void (*anytree_remove_fn_t)(struct anytree_node *node, struct anytree *tree);
typedef void (*anytree_replace_fn_t)(struct anytree_node *old, struct anytree_node *node, struct anytree *tree);

struct anytree_functions {
    anytree_first_fn_t first_fn;
    anytree_last_fn_t last_fn;
    anytree_next_fn_t next_fn;
    anytree_prev_fn_t prev_fn;

    anytree_lookup_fn_t lookup_fn;
    anytree_insert_fn_t insert_fn;
    anytree_remove_fn_t remove_fn;
    anytree_replace_fn_t replace_fn;
};

struct anytree {
    union {
        anytree_cmp_fn_t cmp_fn;
        struct avltree avl;
        struct bstree bs;
        struct rbtree rb;
        struct splaytree splay;
    };

    struct anytree_functions *functions;
};

#define anytree_first(TREE) TREE->functions->first_fn(TREE)
#define anytree_last(TREE) TREE->functions->last_fn(TREE)
#define anytree_next(NODE) NODE->tree->functions->next_fn(NODE)
#define anytree_prev(NODE) NODE->tree->functions->prev_fn(NODE)

#define anytree_lookup(KEY, TREE) TREE->functions->lookup_fn(KEY, TREE)
#define anytree_insert(NODE, TREE) TREE->functions->insert_fn(NODE, TREE)
#define anytree_remove(NODE) NODE->tree->functions->remove_fn(NODE, NODE->tree)
#define anytree_replace(OLD, NODE) OLD->tree->functions->replace_fn(OLD, NODE, OLD->tree)


enum anytree_type {
    ANYTREE_AVL,
    ANYTREE_BS,
    ANYTREE_RB,
    ANYTREE_SPLAY
};

struct anytree * anytree_init(enum anytree_type type, anytree_cmp_fn_t cmp);
void anytree_release(struct anytree *tree);

typedef void (*anytree_call_fn_t)(const struct anytree_node *);
void anytree_foreach(struct anytree *tree, anytree_call_fn_t call);
void anytree_foreach_backward(struct anytree *tree, anytree_call_fn_t call);


#endif /* ANYTREE__ANY__INCLUDED */
