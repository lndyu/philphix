#include "hashtable.h"

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */
HashTable *createHashTable(int size, unsigned int (*hashFunction)(void *),
                           int (*equalFunction)(void *, void *)) {
  int i = 0;
  HashTable *newTable = malloc(sizeof(HashTable));
  if (NULL == newTable) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  newTable->size = size;
  newTable->buckets = malloc(sizeof(struct HashBucketEntry *) * size);
  if (NULL == newTable->buckets) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  for (i = 0; i < size; i++) {
    newTable->buckets[i] = NULL;
  }
  newTable->hashFunction = hashFunction;
  newTable->equalFunction = equalFunction;
  return newTable;
}

/* Task 1.2 */
void insertData(HashTable *table, void *key, void *data) {
  unsigned int location = table->hashFunction(key) % table->size;
  HashBucketEntry *new = malloc(sizeof(HashBucketEntry));
  if(new == NULL){
	fprintf(stderr, "malloc failed \n");
	exit(1);
  }
  new->key = key;
  new->data = data;
  new->next = NULL;

  if(table->buckets[location] == NULL){
	table->buckets[location] = new;
  }
  else{
     HashBucketEntry *current = table->buckets[location];
     while(current->next != NULL){
   	current = current->next;
     }
  current->next = new;
  }

  // HINT:
  // 1. Find the right hash bucket location with table->hashFunction.
  // 2. Allocate a new hash bucket entry struct.
  // 3. Append to the linked list or create it if it does not yet exist. 
}

/* Task 1.3 */
void *findData(HashTable *table, void *key) {
  unsigned int location = table->hashFunction(key) % table->size;
  if(table->buckets[location] == NULL){
         return NULL;
  }
  HashBucketEntry *current = table->buckets[location];
  while(current != NULL){
	 if(table->equalFunction(current->key,key)){
              return current->data;
	 }
         current = current->next;
  }
  return NULL;
  // HINT:
  // 1. Find the right hash bucket with table->hashFunction.
  // 2. Walk the linked list and check for equality with table->equalFunction.
}

/* Task 2.1 */
unsigned int stringHash(void *s) {
  unsigned int length = strlen(s);
  int i;
  int sum = 0;
  char *string = (char*)s;
  for(i = 1; i<length+1; i++){
	int c = string[i] - 'a' + 1;
	sum = (sum<<1) + c * i;
  }
  return sum;
}

/* Task 2.2 */
int stringEquals(void *s1, void *s2) { 
  unsigned int l1 = strlen(s1);
  unsigned int l2 = strlen(s2);
  int i;
  char *string1 = (char*)s1;
  char *string2 = (char*)s2;
  if(l1 != l2){
	return 0;
  }
  for(i = 0; i < l1; i++){
	if(string1[i] != string2[i]){
		return 0;
	}
  }
  return 1;
}
