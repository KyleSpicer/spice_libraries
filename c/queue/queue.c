#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "queue.h"

struct queue_t {
	int head;
	int tail;
	int size;
	int *data;
};

queue_t *queue_create(int size)
{
	queue_t *queue = calloc(1, sizeof(*queue));

	if (queue) {
		queue->size = size;
		queue->data = calloc(size, sizeof(int));
		if (!queue->data) {
			free(queue);
			queue = NULL;
		}
	}

	return queue;
}

void queue_destroy(queue_t ** queue)
{
	if (!queue || !*queue) {
		return;
	}

	free((*queue)->data);
	free(*queue);
	*queue = NULL;
}

void reset_queue(queue_t * queue)
{
	if (!queue) {
		return;
	}
	queue->head = 0;
	queue->tail = 0;
}

queue_t *queue_enqueue(queue_t * queue, int value)
{
	// avoids negative numbers, or max capacity reached
	if (!queue || value < 0 || queue->tail == queue->size) {
		if (!queue) {
			printf("bad queue\n");
		} else if (value < 0) {
			printf("bad value\n");
		} else {
			printf("QUEUE IS FULL!\n");
			printf("%d == %d\n", queue->tail, queue->size);
		}
		return NULL;
	}

	queue->data[queue->tail++] = value;

	return queue;
}

int queue_dequeue(queue_t * queue)
{
	if (!queue || queue->head == queue->tail) {
		return -1;
	}

	return queue->data[queue->head++];
}

int array_int_sort(const void *data1, const void *data2)
{
	if (!data1 || !data2) {
		printf("insufficient data entered.\n");
		return 1;
	}
	return *(int *)data1 - *(int *)data2;
}

void queue_print(queue_t * queue)
{
	if (!queue) {
		printf("Unable to print queue.\n");
		return;
	}

	for (int i = queue->head; i < queue->tail; i++) {
		printf("%d ", queue->data[i]);
	}
	printf("\n");
}

bool is_queue_empty(queue_t * queue)
{
	if (!queue) {
		return false;
	}
	if (0 == queue->size) {
		return true;
	}
	return false;
}

bool is_queue_full(queue_t * queue, int max_queue_size)
{
	if (!queue) {
		return NULL;
	}
	printf("q size = %d\n", queue->size);
	printf("max size = %d\n", max_queue_size);

	if (queue->size == max_queue_size) {
		return true;
	}
	return false;
}

/*** end of file ***/
