#include "hash.h"
#include <stdlib.h>
#include "linked_list.h"
//#include "/home/dmytro/module-cunix/ex07/include/linked_list.h"
unsigned int hash_func(char *key)
{
  if(key == NULL)
     return 0;
  unsigned int result = 0;
  while(*key != '\0') 
  {
    result += *key;
    key++;
  }
  return result;
}

void hash_set(hashtable_t *ht, char *key, void *ptr, void (*fp)(void *data))
{
    int n = hash_func(key)%ht -> size;
    fp(ptr);
    if(ht -> table[n] == NULL)
      ht -> table[n] = list_create(ptr);
    else
      list_push(ht -> table[n],ptr);
}

void *hash_get(hashtable_t *ht, char *key)
{
    int index = hash_func(key)%ht -> size;
    if(ht -> table[index] == NULL)
      return NULL;
    node_t *ptr = ht -> table[index];
    return ptr -> data;
}

hashtable_t *hash_create(unsigned int size)
{
  hashtable_t *newt;
  if(size < 1)
    return NULL;
  newt = malloc(sizeof(hashtable_t));
  newt -> table = malloc(size*sizeof(node_t*));
  for(int i = 0; i < size; i++)
     newt -> table[i] = NULL;

  newt -> size = size;

  return newt;
}

void hash_destroy(hashtable_t *ht, void (*fp)(void *data))
{
  for(int i = 0; i < ht -> size; i++) 
  {
    if(ht -> table[i] != NULL)
    {
      node_t  *ptr = ht -> table[i];
      list_destroy(&(ptr),fp);
    }
  }
  free(ht -> table);
  free(ht);
}

