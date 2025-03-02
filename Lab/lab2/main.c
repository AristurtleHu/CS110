#include "queue.h"
#include <stdio.h>

int main(void)
{
  Queue *queue = queue_create();
  for (int i = 0; i < 100; ++i)
  {
    push(queue, i * 10);
    printf("%f\n", back(queue));
  }
  queue_free(queue);
  return 0;
}