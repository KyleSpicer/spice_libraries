#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue_t queue_t;

queue_t *queue_create(int size);

void queue_destroy(queue_t ** queue);

void reset_queue(queue_t * queue);

queue_t *queue_enqueue(queue_t * queue, int value);

int queue_dequeue(queue_t * queue);

int array_int_sort(const void *data1, const void *data2);

void queue_print(queue_t * queue);

bool is_queue_empty(queue_t * queue);

bool is_queue_full(queue_t * queue, int max_queue_size);

#endif				/* QUEUE_H */
