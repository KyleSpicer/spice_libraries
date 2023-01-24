#include "llist.h"
#include "bacon_funcs.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

llist_t *llist_create()
{
	llist_t *llist = calloc(1, sizeof(llist_t));
	if (!llist) {
		return NULL;
	}
	llist->head = NULL;
	llist->tail = NULL;
	llist->count = 0;
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
	if (llist->count > 0) {
		return 0;
	}
	return 1;
}

void llist_insert_front(llist_t * llist, void *data)
{
	if (!llist || !data) {
		return;
	}
	llist_element_t *new_node = calloc(1, sizeof(llist_element_t));
	if (!new_node) {
		return;
	}
	new_node->data = data;

	if (!llist->tail) {
		llist->tail = new_node;
	}
	new_node->next = llist->head;
	llist->head = new_node;
	llist->count++;
}

void llist_actor_insert_sort(llist_t * llist, void *data)
{
	if (!llist || !data) {
		return;
	}
	llist_element_t *new_node = calloc(1, sizeof(llist_element_t));
	if (!new_node) {
		return;
	}

	new_node->data = data;

	if (!llist->tail) {
		llist->tail = new_node;
		new_node->next = NULL;
		llist->head = new_node;
		llist->count++;
		return;
	}
	// compare new actor to head
	llist_element_t *curr = llist->head;
	actor_t *curr_actor = curr->data;

	actor_t *new_actor = new_node->data;

	int first_result = compare_actor_names(curr_actor, new_actor);
	if (first_result > 0) {
		// printf("INSERTING AT FRONT\n");
		llist_insert_front(llist, new_actor);
		return;
	}

	while (curr->next) {
		actor_t *next_actor = curr->next->data;
		int ret = compare_actor_names(next_actor, new_actor);

		if (0 < ret) {
			break;
		} else {
			curr = curr->next;
		}
	}
	new_node->next = curr->next;
	curr->next = new_node;
	llist->count++;
}

void llist_insert_back(llist_t * llist, void *data)
{
	if (!llist || !data) {
		return;
	}

	llist_element_t *new_node = calloc(1, sizeof(llist_element_t));
	if (!new_node) {
		return;
	}

	new_node->data = data;
	new_node->next = NULL;

	if (NULL == llist->head) {
		llist->head = new_node;
	} else {
		llist_element_t *current = llist->head;

		while (NULL != current->next) {
			current = current->next;
		}
		current->next = new_node;
	}
	llist->count++;
}

llist_element_t *llist_remove_front(llist_t * llist)
{
	if (!llist) {
		return NULL;
	} else if (is_llist_empty(llist)) {
		printf("linked list is empty.\n");
		return NULL;
	}
	llist_element_t *temp = llist->head;
	llist->head = temp->next;
	llist->count--;
	llist_element_t *data = temp->data;
	free(temp);
	return (data);
}

// llist_node_t *llist_remove_back(llist_t * llist)
// {
//      if (!llist) {
//              return NULL;
//      }

//      else if (is_llist_empty(llist)) {
//              return NULL;
//      }
//      // if only head element exists
//      else if (llist->head == NULL) {
//              llist_node_t *temp_head = llist->head;
//              free(llist->head);
//              return temp_head;
//      }

//      llist_node_t *curr = llist->head;
//      while (curr->next->next != NULL) {
//              curr = curr->next;
//      }

//      free(curr->next);
//      curr->next = NULL;

//      return curr;
// }

// void llist_display(llist_t * llist)
// {
//      if (!llist) {
//              return;
//      }
//      llist_node_t *curr = llist->head;
//      int station_count = 1;
//      while (curr != NULL) {
//              printf("Stop %2d: (x: %lf, y: %lf)\n",
//                     station_count, curr->node->x_coord, curr->node->y_coord);
//              curr = curr->next;
//              station_count++;
//      }
//      printf("\n");
// }

int llist_size(llist_t * llist)
{
	if (!llist) {
		return -1;
	}
	return llist->count;
}

void llist_destroy(llist_t ** llist)
{
	if (!*llist || !llist) {
		return;
	}
	llist_element_t *temp = (*llist)->head;
	while (temp) {
		(*llist)->head = temp->next;
		free(temp);
		temp = (*llist)->head;
	}
	free(*llist);
	llist = NULL;

}

/*** end of file ***/
