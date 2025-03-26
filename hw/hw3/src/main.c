
/* DO NOT MODIFY this file */

#include "leaderboard.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_LEN 512
#define MAX_NAME_LEN 32

static void trim(char *str);
static void print_help(void);

int main(void) {
  srand(time(NULL));

  Leaderboard *lb = lb_create();
  if (!lb) {
    printf("Failed to create leaderboard\n");
    return 0;
  }

  char input[MAX_INPUT_LEN];
  char command[MAX_INPUT_LEN];
  char arg1[MAX_NAME_LEN];
  char arg2[MAX_NAME_LEN];
  char arg3[MAX_NAME_LEN];
  int score;

  printf("================================\n");
  printf("Leaderboard\n");
  printf("Type HELP for available commands\n");

  while (1) {
    printf("> ");
    if (!fgets(input, MAX_INPUT_LEN, stdin))
      break;

    trim(input);

    command[0] = '\0';
    arg1[0] = '\0';
    arg2[0] = '\0';
    arg3[0] = '\0';

    int parsed = sscanf(input, "%s %s %s %s", command, arg1, arg2, arg3);
    if (parsed < 1)
      continue;

    // Convert command to uppercase
    for (int i = 0; command[i]; i++)
      command[i] = toupper(command[i]);

    if (strcmp(command, "EXIT") == 0)
      break;

    if (strcmp(command, "HELP") == 0) {
      print_help();
      continue;
    }

    if (strcmp(command, "ZREM") == 0) {
      if (parsed < 2) {
        printf("Error: ZREM <member> - Remove a member from leaderboard\n");
        continue;
      }
      zrem(lb, arg1);
      continue;
    }

    if (strcmp(command, "ZCARD") == 0) {
      zcard(lb);
      continue;
    }

    if (strcmp(command, "ZADD") == 0) {
      if (parsed < 3) {
        printf("Error: ZADD <member> <score> - Add or update a member with "
               "score\n");
        continue;
      }

      score = atoi(arg2);
      zadd(lb, arg1, score);
      continue;
    }

    if (strcmp(command, "ZSCORE") == 0) {
      if (parsed < 2) {
        printf("Error: ZSCORE <member> - Get score of member\n");
        continue;
      }

      zscore(lb, arg1);
      continue;
    }

    if (strcmp(command, "ZRANK") == 0) {
      if (parsed < 2) {
        printf("Error: ZRANK <member> - Get rank of member (1-based, "
               "ascending)\n");
        continue;
      }

      zrank(lb, arg1, 0);
      continue;
    }

    if (strcmp(command, "ZREVRANK") == 0) {
      if (parsed < 2) {
        printf("Error: ZREVRANK <member> - Get rank of member (1-based, "
               "descending)\n");
        continue;
      }

      zrevrank(lb, arg1);
      continue;
    }

    if (strcmp(command, "ZRANGE") == 0 || strcmp(command, "ZREVRANGE") == 0) {
      if (parsed < 3) {
        printf("Error: %s <start> <end>\n", command);
        continue;
      }

      int start = atoi(arg1);
      int end = atoi(arg2);

      if (strcmp(command, "ZRANGE") == 0) {
        zrange(lb, start, end);
      } else {
        zrevrange(lb, start, end);
      }
      continue;
    }

    if (strcmp(command, "ZRANGEBYSCORE") == 0) {
      if (parsed < 3) {
        printf("Error: ZRANGEBYSCORE <min> <max> - Get range of members by "
               "score\n");
        continue;
      }

      int min_score = atoi(arg1);
      int max_score = atoi(arg2);

      zrangebyscore(lb, min_score, max_score);
      continue;
    }

    printf("Unknown command: %s\n", command);
    print_help();
  }

  lb_free(lb);
  printf("Program exited!\n");
  return 0;
}

static void trim(char *str) {
  if (!str)
    return;

  char *start = str;
  while (isspace((unsigned char)*start))
    start++;

  if (start != str) {
    memmove(str, start, strlen(start) + 1);
  }

  char *end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;

  end[1] = '\0';
}

void print_help(void) {
  printf("Leaderboard Commands:\n");
  printf("  ZADD <member> <score>     - Add or update a member with score\n");
  printf("  ZREM <member>             - Remove a member from leaderboard");
  printf("  ZCARD                     - The the number of elements in "
         "leaderboard\n");
  printf("  ZSCORE <member>           - Get score of member\n");
  printf("  ZRANK <member>            - Get rank of member (1-based, "
         "ascending)\n");
  printf("  ZREVRANK <member>         - Get rank of member (1-based, "
         "descending)\n");
  printf("  ZRANGE <start> <end>      - Get range of members by rank "
         "(ascending)\n");
  printf("  ZREVRANGE <start> <end>   - Get range of members by rank "
         "(descending)\n");
  printf("  ZRANGEBYSCORE <min> <max> - Get range of members by score\n");
  printf("  HELP                      - Show this help\n");
  printf("  EXIT                      - Exit program\n");
}
