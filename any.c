/*
 * any - abstraction of tree implementation
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

#include <malloc.h>

#include "any.h"
#include "avl.h"
#include "bs.h"
#include "rb.h"
#include "splay.h"

struct anytree * anytree_init(enum anytree_type type, anytree_cmp_fn_t cmp)
{
    struct anytree *tree = NULL;
    switch (type)
    {
    case ANYTREE_AVL:
        tree = (struct anytree *)malloc(sizeof(struct avltree));
        tree->first_fn = (anytree_first_fn_t)avltree_first;
        tree->last_fn  = (anytree_last_fn_t)avltree_last;
        tree->next_fn  = (anytree_next_fn_t)avltree_next;
        tree->prev_fn  = (anytree_prev_fn_t)avltree_prev;
        tree->lookup_fn  = (anytree_lookup_fn_t)avltree_lookup;
        tree->insert_fn  = (anytree_insert_fn_t)avltree_insert;
        tree->remove_fn  = (anytree_remove_fn_t)avltree_remove;
        tree->replace_fn = (anytree_replace_fn_t)avltree_replace;
        if (avltree_init((struct avltree*)tree, (avltree_cmp_fn_t)cmp))
        {
            free(tree);
            tree = NULL;
        }
        break;

    case ANYTREE_BS:
        tree = (struct anytree *)malloc(sizeof(struct bstree));
        tree->first_fn = (anytree_first_fn_t)bstree_first;
        tree->last_fn  = (anytree_last_fn_t)bstree_last;
        tree->next_fn  = (anytree_next_fn_t)bstree_next;
        tree->prev_fn  = (anytree_prev_fn_t)bstree_prev;
        tree->lookup_fn  = (anytree_lookup_fn_t)bstree_lookup;
        tree->insert_fn  = (anytree_insert_fn_t)bstree_insert;
        tree->remove_fn  = (anytree_remove_fn_t)bstree_remove;
        tree->replace_fn = (anytree_replace_fn_t)bstree_replace;
        if (bstree_init((struct bstree*)tree, (bstree_cmp_fn_t)cmp))
        {
            free(tree);
            tree = NULL;
        }
        break;

    case ANYTREE_RB:
        tree = (struct anytree *)malloc(sizeof(struct rbtree));
        tree->first_fn = (anytree_first_fn_t)rbtree_first;
        tree->last_fn  = (anytree_last_fn_t)rbtree_last;
        tree->next_fn  = (anytree_next_fn_t)rbtree_next;
        tree->prev_fn  = (anytree_prev_fn_t)rbtree_prev;
        tree->lookup_fn  = (anytree_lookup_fn_t)rbtree_lookup;
        tree->insert_fn  = (anytree_insert_fn_t)rbtree_insert;
        tree->remove_fn  = (anytree_remove_fn_t)rbtree_remove;
        tree->replace_fn = (anytree_replace_fn_t)rbtree_replace;
        if (rbtree_init((struct rbtree*)tree, (rbtree_cmp_fn_t)cmp))
        {
            free(tree);
            tree = NULL;
        }
        break;

    case ANYTREE_SPLAY:
        tree = (struct anytree *)malloc(sizeof(struct splaytree));
        tree->first_fn = (anytree_first_fn_t)splaytree_first;
        tree->last_fn  = (anytree_last_fn_t)splaytree_last;
        tree->next_fn  = (anytree_next_fn_t)splaytree_next;
        tree->prev_fn  = (anytree_prev_fn_t)splaytree_prev;
        tree->lookup_fn  = (anytree_lookup_fn_t)splaytree_lookup;
        tree->insert_fn  = (anytree_insert_fn_t)splaytree_insert;
        tree->remove_fn  = (anytree_remove_fn_t)splaytree_remove;
        tree->replace_fn = (anytree_replace_fn_t)splaytree_replace;
        if (splaytree_init((struct splaytree*)tree, (splaytree_cmp_fn_t)cmp))
        {
            free(tree);
            tree = NULL;
        }
        break;

    }
    return tree;
}
