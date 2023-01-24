#ifndef LLIST_H
#define LLIST_H

#include <stdint.h>

// #include "bacon_funcs.h"

typedef struct llist_element llist_element_t;
/**
 * @brief structure for each node within linked list
 * 
 */
typedef struct llist_element {
	void *data;
	llist_element_t *next;
} llist_element_t;

typedef struct llist llist_t;

typedef struct llist {
	llist_element_t *head;	// same thing as an element
	llist_element_t *tail;	// same thing as an element
	uint64_t count;		// number of elements
} llist_t;

/**
 * @brief allocates memory to begin populating linked list
 * 
 * @return llist_t* 
 */

llist_t *llist_create();

/**
 * @brief checks the amount of nodes within llist
 * 
 * @param llist 
 * @return int - the amount of nodes within the llist
 */
int is_llist_empty(llist_t * llist);

/**
 * @brief inserts a llist node into the front of a given llist
 * 
 * @param llist 
 * @param data 
 */
void llist_insert_front(llist_t * llist, void *data);

void llist_actor_insert_sort(llist_t * llist, void *data);

/**
 * @brief inserts a llist node into the back of a given llist
 * 
 * @param llist 
 * @param data 
 */
void llist_insert_back(llist_t * llist, void *data);

/**
 * @brief removes front node from a given llist
 * 
 * @param llist 
 * @return llist_node_t* 
 */
llist_element_t *llist_remove_front(llist_t * llist);

/**
 * @brief removes end node from given llist
 * 
 * @param llist 
 * @return llist_node_t* 
 */
llist_element_t *llist_remove_back(llist_t * llist);

/**
 * @brief prints contents within llist according to function logic
 * 
 * @param llist 
 */
void llist_display(llist_t * llist);

/**
 * @brief returns the amount of nodes within a given llist
 * 
 * @param llist 
 * @return int 
 */
int llist_size(llist_t * llist);

/**
 * @brief frees all memory allocation and sets container memory address to NULL
 * 
 * @param llist 
 */
void llist_destroy(llist_t ** llist);

#endif				/* LLIST_H */
/*** end of file ***/
