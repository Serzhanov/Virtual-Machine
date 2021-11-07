#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#define TABLE_SIZE 256


unsigned int hash(const char *key){//Store key in slot number'value'
  unsigned long int value = 0;
  unsigned int i = 0;
  unsigned int key_len = strlen(key);
  
  // Fait plusieurs multiplication
  for (;i<key_len;i++){
    value = value *37 + key[i];
  }
  
  //Assure que la valeur est (0<=value<TABLE_SIZE)
  value = value%TABLE_SIZE;
  
  return value;
}

entry_t *ht_pair(const char *key, const char *value){
  //allocation de l'entree
  entry_t *entry = malloc(sizeof(entry)*1);
  entry->key = malloc(strlen(key)+1);
  entry->value = malloc(strlen(value)+1);
  
  //copie key et value
  strcpy(entry->key, key);
  strcpy(entry->value, value);
    
  //next commence avec 0, mais peut-etre modifier plus tard
  entry->next = NULL;
  return entry;
}

void ht_delete(ht_t *ht){
  for(int i=0;i<TABLE_SIZE;i++){
    free(ht->entries[i]);
  }
  free(ht);
}

ht_t *ht_create(void){
  //Allocation
  ht_t *hashtable = malloc(sizeof(ht_t) *1);
  
  //Allocation des entrees
  hashtable->entries = malloc(sizeof(entry_t*)* TABLE_SIZE);
  
  //Mettre tous a zero
  int i = 0;
  for (;i< TABLE_SIZE; i++){
     hashtable->entries[i] = NULL; 
  }
  
  return hashtable;
}


void ht_set(ht_t *hashtable, const char *key, const char *value){
  unsigned int bucket = hash(key);
  //Try to look up an entry set
  entry_t *entry = hashtable->entries[bucket];
  //no entry means bucket is empty, insert immediately
  if (entry == NULL){
    hashtable->entries[bucket] = ht_pair(key,value);
    return;
  }
  
  entry_t *prev;
  
  //Passage par chaque entree jusqu'a trouver key ou la fin de sequence
  while(entry!= NULL){
    if (strcmp(entry->key, key)==0){
      free(entry->value);
      entry->value = malloc(strlen(value)+1);
      strcpy(entry->value, value);
      return;
    
    }
    prev = entry;
    entry = prev->next;
  
  }
  //Key pas trouve, alors ajoute key-value pair
  prev->next = ht_pair(key,value);
}

int ht_get(ht_t *hashtable, const char *key){
  unsigned int slot = hash(key);
  
  //Essaie de trouver slot valide
  entry_t * entry = hashtable->entries[slot];
  
  //Pas de slot = pas d'entreen
  if (entry == NULL){
    printf("Not exisiting value\n");
    return 0;
  }
  
  while (entry !=NULL){
    if (strcmp(entry->key, key) == 0){
      return atoi(entry ->value);
    }
    entry = entry->next;
  }
  printf("error in hash\n");
  return 0;//Pas de key trouve
}

void ht_aff(ht_t *hashtable){
  
  int i = 0;
  for (;i< TABLE_SIZE; i++){
     if(hashtable->entries[i] == NULL){
       continue;
     }
     printf("key - %s and value - %s\n",hashtable->entries[i]->key,hashtable->entries[i]->value);
  }
}




/*int main(int argc, char**agrv){
  ht_t *ht = ht_create();
  ht_set(ht, "name", "Pidor");
  char *c = ht_get(ht, "name");
  printf("%s\n", c);
  
  
  return 0;


}*/