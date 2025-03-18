#ifndef SKIP_LIST_H
#define SKIP_LIST_H

/**
 * Feel free to add more fields in given structures.
 * DO NOT modify any function declerations below.
 */

typedef struct SkipListNode {
  char *member;
  int score;

  /* If level i given, forwar[i] points to the next node */
  struct SkipListNode **forward;

  /* levels this node has, ranges [1,MAX_LEVEL] */
  int level;
} SkipListNode;

typedef struct SkipList {
  /* Dummy node as sentinel */
  SkipListNode *header;

  /* Current max level, ranges [1,MAX_LEVEL] */
  int level;

  int length;
} SkipList;

/* Helper functions for test */
void sl_print(SkipList *sl);

int sl_insert(SkipList *sl, const char *member, int score);

/**
 * Implement the following functions at `skiplist.c`.
 * For detailed requirements, see corresponding implementations.
 */

SkipList *sl_create(void);
void sl_free(SkipList *sl);
int sl_get_length(SkipList *sl);
SkipListNode *sl_get_by_score(SkipList *sl, int score);
// Declared here only for testing. For normal usage, call `sl_insert()` instead
int _sl_insert(SkipList *sl, const char *member, int score, int level);
SkipListNode *sl_get_by_rank(SkipList *sl, int rank);
int sl_remove(SkipList *sl, int score);
int sl_get_rank_by_score(SkipList *sl, int score);
SkipListNode **sl_get_range_by_rank(SkipList *sl, int start, int end,
                                    int *count);
SkipListNode **sl_get_range_by_score(SkipList *sl, int min_score, int max_score,
                                     int *count);
#endif // SKIP_LIST_H
