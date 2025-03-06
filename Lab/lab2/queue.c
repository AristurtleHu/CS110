#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

Queue *queue_create(void) {
  Queue *queue = malloc(sizeof(Queue));

  if (!queue) {
    printf("malloc failed for queue\n");
    exit(EXIT_FAILURE);
  }

  queue->size = 0;
  queue->capacity = QUEUE_INITIAL_CAPACITY;
  queue->data = malloc(sizeof(double) * queue->capacity);

  if (!queue->data) {
    printf("malloc failed for data\n");
    free(queue);
    exit(EXIT_FAILURE);
  }

  return queue;
}

void push(Queue *queue, double element) {
  if (!queue) {
    printf("invalid queue\n");
    exit(EXIT_FAILURE);
  }

  if (queue->size == queue->capacity) {
    int capacity = queue->capacity * 2;

    queue->data = realloc(queue->data, sizeof(double) * capacity);

    if (!queue->data) {
      printf("realloc failed\n");
      free(queue);
      exit(EXIT_FAILURE);
    }

    queue->capacity = capacity;
  }

  int insert_index = queue->size % queue->capacity;
  queue->data[insert_index] = element;
  queue->size++;
}

double back(Queue *queue) {
  if (!queue) {
    printf("invalid queue\n");
    exit(EXIT_FAILURE);
  }

  if (!queue->data) {
    printf("invalid data\n");
    exit(EXIT_FAILURE);
  }

  if (queue->size <= 0) {
    printf("no element in queue\n");
    exit(EXIT_FAILURE);
  }

  return queue->data[queue->size - 1];
}

void queue_free(Queue *queue) {
  if (!queue)
    return;

  if (queue->data)
    free(queue->data);

  free(queue);
}

// avoid dangling pointer
void another_queue_free(Queue **queue) {
  if (!queue || !*queue)
    return;

  if ((*queue)->data)
    free((*queue)->data);

  free(*queue);
  *queue = NULL;
}