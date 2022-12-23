#include "llist.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct llist_t {
	llist_node_t *head;
	llist_node_t *tail;
	uint64_t llist_size;
};

llist_t *llist_create()
{
	llist_t *llist = calloc(1, sizeof(llist_t));
	if (!llist) {
		return NULL;
	}
	llist->head = NULL;
	return llist;
}

/**
 * @brief returns 0 if llist is empty, 1 if anything else
 * 
 * @param llist 
 * @return int 
 */
int is_llist_empty(llist_t * llist)
{
	if (!llist) {
		return -1;
	}
	if (llist->llist_size > 0) {
		return 1;
	}
	return 0;
}

void llist_insert_front(llist_t * llist, int data)
{
	if (!llist || !data) {
		return;
	}
	llist_node_t *new_node = calloc(1, sizeof(llist_node_t));
	llist->llist_size++;
	new_node->data = data;
	new_node->next = llist->head;
	llist->head = new_node;
}

void llist_insert_back(llist_t * llist, int data)
{
	if (!llist || !data) {
		return;
	}

	llist_node_t *new_node = calloc(1, sizeof(llist_node_t));
	new_node->data = data;
	if (!new_node) {
		return;
	}

	if (llist->tail) {
		llist->tail->next = new_node;
		llist->tail = new_node;
	} else {
		llist->head = new_node;
		llist->tail = new_node;
	}
	llist->llist_size++;
}

llist_node_t *llist_remove_front(llist_t * llist)
{
	if (!llist) {
		return NULL;
	} else if (is_llist_empty(llist)) {
		printf("linked list is empty.\n");
		return NULL;
	}
	llist_node_t *temp = llist->head;
	llist->head = temp->next;

	return (temp);

}

llist_node_t *llist_remove_back(llist_t * llist)
{
	if (!llist) {
		return NULL;
	}

	else if (is_llist_empty(llist)) {
		return NULL;
	}
	// if only head element exists
	else if (llist->head == NULL) {
		llist_node_t *temp_head = llist->head;
		free(llist->head);
		return temp_head;
	}

	llist_node_t *curr = llist->head;
	while (curr->next->next != NULL) {
		curr = curr->next;
	}

	free(curr->next);
	curr->next = NULL;

	return curr;
}

void llist_display(llist_t * llist)
{
	if (!llist) {
		return;
	}
	llist_node_t *curr = llist->head;
	while (curr != NULL) {
		printf("%d ", curr->data);
		curr = curr->next;
	}
	printf("\n");
}

int llist_size(llist_t * llist)
{
	if (!llist) {
		return -1;
	}
	return llist->llist_size;
}

void llist_destroy(llist_t ** llist)
{
	if (!*llist || !llist) {
		return;
	}
	llist_node_t *temp = (*llist)->head;
	while (temp) {
		(*llist)->head = temp->next;
		free(temp);
		temp = (*llist)->head;
	}
	free(*llist);
	llist = NULL;

}

/*** end of file ***/
