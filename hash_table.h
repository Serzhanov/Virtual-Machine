#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 256
typedef struct entry_t{
  char *key;
  char *value;
  struct entry_t *next;
} entry_t;

typedef struct {
  entry_t **entries;
} ht_t;



unsigned int hash(const char *key);//Store key in slot number'value'

entry_t *ht_pair(const char *key, const char* value); //Create key-value pair

ht_t *ht_create(void); //Initialize hash_table

void ht_set(ht_t *hashtable, const char *key, const char* value); 

int ht_get(ht_t *hashtable, const char *key);
 
void ht_aff(ht_t *hashtable);

void ht_delete(ht_t *ht);