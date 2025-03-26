
/* DO NOT MODIFY this file */

#include "dict.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static uint32_t hash_function(const char *key, int size) {
  uint32_t hash = 5381;
  int c;

  while ((c = *key++))
    hash = ((hash << 5) + hash) + c;

  return hash % size;
}

static char *udf_strdup(const char *str) {
  if (str == NULL)
    return NULL;

  size_t len = strlen(str) + 1;
  char *new_str = (char *)malloc(len);
  if (new_str == NULL)
    return NULL;

  memcpy(new_str, str, len);
  return new_str;
}

Dict *dict_create(int size) {
  Dict *dict = (Dict *)malloc(sizeof(Dict));
  if (!dict)
    return NULL;

  dict->size = size;
  dict->table = (DictEntry **)calloc(size, sizeof(DictEntry *));
  if (!dict->table) {
    free(dict);
    return NULL;
  }
  return dict;
}

void dict_free(Dict *dict) {
  if (!dict)
    return;

  for (int i = 0; i < dict->size; i++) {
    DictEntry *entry = dict->table[i];
    while (entry) {
      DictEntry *next = entry->next;
      free(entry->key);
      free(entry);
      entry = next;
    }
  }

  free(dict->table);
  free(dict);
}

DictEntry *dict_get(Dict *dict, const char *key) {
  if (!dict || !key)
    return NULL;

  uint32_t index = hash_function(key, dict->size);
  DictEntry *entry = dict->table[index];

  while (entry) {
    if (strcmp(entry->key, key) == 0)
      return entry;
    entry = entry->next;
  }

  return NULL;
}

int dict_insert(Dict *dict, const char *key, int val) {
  if (!dict || !key)
    return 0;

  DictEntry *entry = dict_get(dict, key);
  if (entry) {
    /* update */
    entry->val = val;
    return 1;
  }

  uint32_t index = hash_function(key, dict->size);
  entry = (DictEntry *)malloc(sizeof(DictEntry));
  if (!entry)
    return 0;

  entry->key = udf_strdup(key);
  if (!entry->key) {
    free(entry);
    return 0;
  }

  entry->val = val;
  entry->next = dict->table[index];
  dict->table[index] = entry;
  return 1;
}

int dict_remove(Dict *dict, const char *key) {
  if (!dict || !key)
    return 0;

  uint32_t index = hash_function(key, dict->size);
  DictEntry *entry = dict->table[index];
  DictEntry *prev = NULL;

  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      if (prev)
        prev->next = entry->next;
      else
        dict->table[index] = entry->next;

      free(entry->key);
      free(entry);
      return 1;
    }

    prev = entry;
    entry = entry->next;
  }

  return 0;
}
