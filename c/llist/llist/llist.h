#ifndef LLIST_H
#define LLIST_H

typedef struct llist_node_t llist_node_t;

struct llist_node_t {
	int data;
	llist_node_t *next;
};

typedef struct llist_t llist_t;

llist_t *llist_create();

int is_llist_empty(llist_t * llist);

void llist_insert_front(llist_t * llist, int data);

void llist_insert_back(llist_t * llist, int data);

llist_node_t *llist_remove_front(llist_t * llist);

llist_node_t *llist_remove_back(llist_t * llist);

void llist_display(llist_t * llist);

int llist_size(llist_t * llist);

void llist_destroy(llist_t ** llist);

#endif				/* LLIST_H */
