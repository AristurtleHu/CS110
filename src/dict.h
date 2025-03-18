
/* DO NOT MODIFY this file */

#ifndef DICT_H
#define DICT_H

typedef struct DictEntry {
  char *key;
  int val;
  struct DictEntry *next;
} DictEntry;

typedef struct Dict {
  DictEntry **table;
  int size;
} Dict;

/**
 * Create and return a dictionary with given `size`.
 * `Size` does not represent actual elements contained by underlying size of
 * "buckets". You can set `size` as a relatively larger number for possibly
 * better performance but with more memory required.
 */
Dict *dict_create(int size);

/* Release `dict` and its allocated resources. */
void dict_free(Dict *dict);

/**
 * Get and return the entry with given `key` from `dict`.
 * Return null if not found or error.
 */
DictEntry *dict_get(Dict *dict, const char *key);

/**
 * Insert an entry with given `key` and `val` to `dict`.
 * If an entry with given `key` exists in `dict`, update its val with given
 * `val`.
 * Return the number of entres inserted/updated.
 */
int dict_insert(Dict *dict, const char *key, int val);

/**
 * Remove an entry with given `key` from `dict`.
 * Return the number of entries removed.
 */
int dict_remove(Dict *dict, const char *key);

#endif // DICT_H
