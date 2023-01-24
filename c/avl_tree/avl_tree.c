/**
 * @file avl_tree.c
 * @author CW2 Kyle Spicer
 * @brief 
 * @version 0.1
 * @date 2023-01-23
 * @cite Logic for this library was inspired/adapted from the coursework 
 * provided during the 170D Warrant Officer Basic Course (2022 - 2023). 
 * US Army Cyber School.
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdlib.h>
#include <string.h>

#include "avl_tree.h"
#include "bacon_funcs.h"

/**
 * @brief returns the larger of the two inputs
 * 
 * @param a 
 * @param b 
 * @return int 
 */
static int max(int a, int b)
{
	return (a > b) ? a : b;
}

/**
 * @brief return the height of the input node
 * 
 * @param node 
 * @return int 
 */
static int height(avl_node_t * node)
{
	return (node == NULL) ? -1 : node->height;
}

/**
 * @brief conducts a proper rotate right to keep tree balanced
 * 
 * @param node 
 * @return avl_node_t* 
 */
static avl_node_t *rotate_right(avl_node_t * node)
{
	avl_node_t *left = node->left;
	node->left = left->right;
	left->right = node;
	node->height = max(height(node->left), height(node->right)) + 1;
	left->height = max(height(left->left), node->height) + 1;
	return left;
}

/**
 * @brief conducts a proper rotate left to keep tree balanced
 * 
 * @param node 
 * @return avl_node_t* 
 */
static avl_node_t *rotate_left(avl_node_t * node)
{
	avl_node_t *right = node->right;
	node->right = right->left;
	right->left = node;
	node->height = max(height(node->left), height(node->right)) + 1;
	right->height = max(height(right->right), node->height) + 1;
	return right;
}

/**
 * @brief conducts a proper rotate left, right to keep tree balanced
 * 
 * @param node 
 * @return avl_node_t* 
 */
static avl_node_t *rotate_left_right(avl_node_t * node)
{
	node->left = rotate_left(node->left);
	return rotate_right(node);
}

/**
 * @brief conducts a proper rotate right, left to keep tree balanced
 * 
 * @param node 
 * @return avl_node_t* 
 */
static avl_node_t *rotate_right_left(avl_node_t * node)
{
	node->right = rotate_right(node->right);
	return rotate_left(node);
}

/**
 * @brief inserts node into avl tree
 * 
 * @param node 
 * @param data 
 * @param cmp 
 * @return avl_node_t* 
 */
static avl_node_t *insert_node(avl_node_t * node, void *data,
			       int (*cmp)(const void *, const void *))
{
	if(node == NULL) {
		struct avl_node *new_node = calloc(1, sizeof(avl_node_t));
		new_node->data = data;
		new_node->height = 0;
		new_node->left = NULL;
		new_node->right = NULL;
		return new_node;
	}
	int result = cmp(data, node->data);
	if (result < 0) {
		node->left = insert_node(node->left, data, cmp);
		if (height(node->left) - height(node->right) == 2) {
			if (cmp(data, node->left->data) < 0) {
				node = rotate_right(node);
			} else {
				node = rotate_left_right(node);
			}
		}
	} else if (result > 0) {
		node->right = insert_node(node->right, data, cmp);
		if (height(node->right) - height(node->left) == 2) {
			if (cmp(data, node->right->data) > 0) {
				node = rotate_left(node);
			} else {
				node = rotate_right_left(node);
			}
		}
	}
	node->height = max(height(node->left), height(node->right)) + 1;
	return node;
}

/**
 * @brief removes node from avl tree, adjusting to remain balanced.
 * 
 * @param node 
 * @param data 
 * @param cmp 
 * @return avl_node_t* 
 */
static avl_node_t *remove_node(avl_node_t * node, void *data, int (*cmp)
			        (const void *, const void *))
{
	if(node == NULL) {
		return NULL;
	}
	int result = cmp(data, node->data);
	if (result < 0) {
		node->left = remove_node(node->left, data, cmp);
		if (height(node->right) - height(node->left) == 2) {
			if (height(node->right->left) >
			    height(node->right->right)) {
				node = rotate_right_left(node);
			} else {
				node = rotate_left(node);
			}
		}
	} else if (result > 0) {
		node->right = remove_node(node->right, data, cmp);
		if (height(node->left) - height(node->right) == 2) {
			if (height(node->left->right) >
			    height(node->left->left)) {
				node = rotate_left_right(node);
			} else {
				node = rotate_right(node);
			}
		}
	} else {
		if (node->left != NULL && node->right != NULL) {
			struct avl_node *min = node->right;
			while (min->left != NULL) {
				min = min->left;
			}
			node->data = min->data;
			node->right = remove_node(node->right, min->data, cmp);
			if (height(node->left) - height(node->right) == 2) {
				if (height(node->left->right) >
				    height(node->left->left)) {
					node = rotate_left_right(node);
				} else {
					node = rotate_right(node);
				}
			}
		} else {
			struct avl_node *old = node;
			node = (node->left != NULL) ? node->left : node->right;
			free(old);
		}
	}
	if (node != NULL) {
		node->height = max(height(node->left), height(node->right)) + 1;
	}
	return node;
}

/**
 * @brief function to build shell of avl tree and hold comparison function ptr
 * 
 * @param tree 
 * @param cmp 
 */
void avl_create(avl_tree_t * tree, int (*cmp)(const void *, const void *))
{
	tree->root = NULL;
	tree->cmp = cmp;	// compare function
}

/**
 * @brief insert new node into tree
 * 
 * @param tree - already created avl shell or functional tree
 * @param data - void * data
 */
void avl_insert(avl_tree_t * tree, void *data)
{
	tree->root = insert_node(tree->root, data, tree->cmp);
}

/**
 * @brief removes node from avl_tree
 * 
 * @param tree 
 * @param data 
 */
void avl_remove(avl_tree_t * tree, void *data)
{
	actor_t tmp;
	tmp.full_name = data;
	tree->root = remove_node(tree->root, (void *)&tmp, tree->cmp);
}

struct trunk {
	struct trunk *prev;
	const char *str;
};

void print_trunks(struct trunk *p)
{
	if (!p) {
		return;
	}
	print_trunks(p->prev);
	printf("%s", p->str);
}

void print_recursive(avl_node_t * root, struct trunk *prev, int is_left)
{
	if (!root) {
		return;
	}

	struct trunk this_disp = { prev, "     " };
	const char *prev_str = this_disp.str;
	print_recursive(root->right, &this_disp, 1);

	if (!prev) {
		this_disp.str = "---";
	} else if (is_left) {
		this_disp.str = ".--";
		prev_str = "    |";
	} else {
		this_disp.str = "`--";
		prev->str = prev_str;
	}

	actor_t *actor = root->data;
	print_trunks(&this_disp);
	printf("%s\n", (char *)actor->full_name);	// whatever custom print you need

	if (prev) {
		prev->str = prev_str;
	}
	this_disp.str = "    |";

	print_recursive(root->left, &this_disp, 0);
	if (!prev) {
		puts("");
	}
}

/**
 * @brief displays avl tree in an easily digestable way
 * @cite received print function from instructor while in 170D WOBC (2022 - 2023)
 */
void printvisual(avl_tree_t * tree)
{
	if (!tree->root) {
		return;
	}
	print_recursive(tree->root, NULL, 0);
}

/**
 * @brief uses in-order traversal to print all nodes, must modify print statement
 * to match void * data.
 * 
 * @param root 
 */
void display_actors_avl_inorder_traverse(avl_node_t * root)
{
	if (root == NULL) {
		return;
	}

	display_actors_avl_inorder_traverse(root->left);
	actor_t *temp = root->data;
	printf("%s\n", temp->full_name);
	display_actors_avl_inorder_traverse(root->right);
}

/**
 * @brief searches avl tree for provided name and comparison function
 * 
 * @param root 
 * @param full_name 
 * @param cmp 
 * @return void* 
 */
void *search(avl_node_t * root, void *full_name,
	     int (*cmp)(const void *, const void *))
{
	if (NULL == root || NULL == full_name) {
		return NULL;
	}

	actor_t *temp = root->data;
	int result = cmp(temp->full_name, full_name);

	if (0 == result) {
		return root->data;
	} else if (0 < result) {
		return search(root->right, full_name, cmp);
	} else {
		return search(root->left, full_name, cmp);
	}
}

/**
 * @brief traverses tree and provided total amount of nodes present
 * 
 * @param tree 
 * @return int 
 */
int count_nodes(avl_node_t * tree)
{
	if (tree == NULL) {
		return 0;
	}

	return 1 + count_nodes(tree->left) + count_nodes(tree->right);
}
