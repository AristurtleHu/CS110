#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

Queue *queue_create(void)
{
  Queue *queue = malloc(sizeof(Queue));
  queue->size = 0;
  queue->capacity = QUEUE_INITIAL_CAPACITY;
  queue->data = malloc(sizeof(double) * queue->capacity);
  return queue;
}

void push(Queue *queue, double element)
{

  if (queue->size == queue->capacity)
  {
    int capacity = queue->capacity * 2;

    queue->data = realloc(queue->data, sizeof(double) * capacity);
    queue->capacity = capacity;
  }

  int insert_index = queue->size % queue->capacity;
  queue->data[insert_index] = element;
  queue->size++;
}

double back(Queue *queue)
{
  return queue->data[queue->size - 1];
}

void queue_free(Queue *queue)
{

  free(queue->data);
  free(queue);
}

