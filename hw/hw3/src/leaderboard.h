
/* DO NOT MODIFY this file*/

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "dict.h"
#include "skiplist.h"

/**
 * Leaderboard supports common operations needed for ranking systems, such as
 * adding/removing entries, retrieving scores, ranks, and ranges of entries by
 * rank or score.
 *
 * Leaderboard consists of two complementary data structures:
 * 1. Skip List (`sl`): Provides efficient ordered access by score and rank
 * lookups
 * 2. Hash Table (`dict`): Provides efficient lookups of scores by `member`
 *
 * This combination allows for fast operations in all required use cases:
 * - Fast lookups by member name (via the hash table)
 * - Fast range queries and rank calculations (via the skip list)
 *
 * The leaderboard maintains `member`s in ascending order by `score`, with rank
 * 1 corresponding to the lowest score. Reverse operations are provided for
 * cases where higher scores should have lower ranks.
 */
typedef struct Leaderboard {
  SkipList *sl;
  Dict *dict;
} Leaderboard;

Leaderboard *lb_create(void);
void lb_free(Leaderboard *lb);

/**
 * Implement the following interfaces.
 * For detailed requirements, see `skiplist.c`
 */

void zadd(Leaderboard *lb, const char *member, int score);
void zrem(Leaderboard *lb, const char *member);
void zcard(Leaderboard *lb);
void zscore(Leaderboard *lb, const char *member);
void zrank(Leaderboard *lb, const char *member, int reverse);
void zrevrank(Leaderboard *lb, const char *member);
void zrange(Leaderboard *lb, int start, int end);
void zrevrange(Leaderboard *lb, int start, int end);
void zrangebyscore(Leaderboard *lb, int min_score, int max_score);

#endif // !LEADERBOARD_H
