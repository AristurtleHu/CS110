#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

Queue *queue_create(void) {
  Queue *queue = malloc(sizeof(Queue));
  queue->size = 0;
  queue->capacity = QUEUE_INITIAL_CAPACITY;
  queue->data = malloc(sizeof(double) * queue->capacity);
  return queue;
}

void push(Queue *queue, double element) {
  if (!queue) {
    printf("invalid queue\n");
    return;
  }

  if (queue->size == queue->capacity) {
    int capacity = queue->capacity * 2;

    queue->data = realloc(queue->data, sizeof(double) * capacity);
    queue->capacity = capacity;
  }

  int insert_index = queue->size % queue->capacity;
  queue->data[insert_index] = element;
  queue->size++;
}

double back(Queue *queue) {
  if (!queue || queue->size == 0) {
    printf("no element in queue\n");
    return 0.0;
  }

  return queue->data[queue->size - 1];
}

void queue_free(Queue *queue) {
  if (!queue) {
    printf("invalid queue\n");
    return;
  }

  free(queue->data);
  free(queue);
}

// avoid dangling pointer
void another_queue_free(Queue **queue) {
  if (!queue || !*queue) {
    printf("invalid queue\n");
    queue = NULL;
    return;
  }

  free((*queue)->data);
  free(*queue);
  *queue = NULL;
}