#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

// #include "fake_bacon_funcs.h"

typedef int (cmp) (const void *, const void *);
typedef struct avl_node avl_node_t;
typedef struct avl_tree avl_tree_t;

typedef struct avl_node {
	void *data;
	int height;
	avl_node_t *left;
	avl_node_t *right;
} avl_node_t;

typedef struct avl_tree {
	avl_node_t *root;
	int count;
	int (*cmp)(const void *, const void *);
	// void (*free_data)(void*); //void (*free_data)(void*)
} avl_tree_t;

void avl_create(avl_tree_t * tree, int (*cmp)(const void *, const void *));

void avl_insert(avl_tree_t * tree, void *data);

void avl_remove(avl_tree_t * tree, void *data);

void avl_destroy(avl_tree_t ** tree);

void printvisual(avl_tree_t * tree);

void display_actors_avl_inorder_traverse(avl_node_t * root);

void *search(avl_node_t * root, void *full_name,
	     int (*cmp)(const void *, const void *));

int count_nodes(avl_node_t * tree);

void destroy_avl_actor_db(avl_tree_t ** tree);

// TODO: add inorder, postorder, preorder, and level order funcs
#endif				/* AVL_H */
