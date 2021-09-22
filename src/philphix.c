#include <ctype.h>
/*
 * Include the provided hash table library.
 */
#include "hashtable.h"

/*
 * Include the header file.
 */
#include "philphix.h"

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This hash table stores the dictionary.
 */
HashTable *dictionary;

/*
 * The MAIN routine.  You can safely print debugging information
 * to standard error (stderr) as shown and it will be ignored in 
 * the grading process.
 */
#ifndef _PHILPHIX_UNITTEST
int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Specify a dictionary\n");
    return 1;
  }
  /*
   * Allocate a hash table to store the dictionary.
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(0x61C, &stringHash, &stringEquals);

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  processInput();

  /*
   * The MAIN function in C should always return 0 as a way of telling
   * whatever program invoked this that everything went OK.
   */
  return 0;
}
#endif /* _PHILPHIX_UNITTEST */

/* Task 3 */
void readDictionary(char *dictName) {
  int current_char;	
  FILE *file = fopen( dictName, "r");
  int current_key_size;
  int current_word_size;
  int key_char_index;
  int word_char_index;
  char *key;
  char *word;
  if(file == NULL){
     exit(61);
  }
  while(current_char != EOF){
     current_key_size = 60;
     current_word_size = 60;
     key_char_index = 0;
     word_char_index = 0;
     key = calloc(current_key_size,sizeof(int));
     word = calloc(current_word_size,sizeof(int));
     if(key == NULL){
	  exit(61);
     }
     if(word == NULL){
	  exit(61);
     }
     current_char = fgetc(file);
     /* get the key first */
     while(current_char != ' ' && current_char != '\t' && current_char != EOF){
	 if(key_char_index == current_key_size-1){
	      current_key_size = current_key_size * 2;
	      char *temp = realloc(key,sizeof(int) * current_key_size);
	      if(temp == NULL){
		  exit(61);
	      }
	      key = temp;
	 }
	 key[key_char_index] = current_char;
	 key_char_index++;
	 current_char = fgetc(file);
     }
     key[key_char_index] = '\0';
     /* clear out all the spaces and tabs*/
     while(current_char == ' ' || current_char == '\t'){
	 if(current_char == EOF){
		break;
	 }
	 current_char = fgetc(file);
     }
     /* get the word itself*/
     while(current_char != '\n' && current_char != EOF){
	 if(word_char_index == current_word_size-1){
               current_word_size = current_word_size * 2;
               char *temp = realloc(word,sizeof(int) * current_word_size);
	       if(temp == NULL){
		    exit(61);
	       }
	       word = temp;
          }
          word[word_char_index] = current_char;
	  word_char_index++;
	  current_char = fgetc(file);
     }
     word[word_char_index] = '\0';
  if(*key != 0 && *word != 0){
	insertData(dictionary,key,word);
  }  
  }
}

/* Task 4 */
void processInput() {
  int current_key_size;
  int key_char_index;
  int string_length;
  int i;
  char *hash_value;
  char current_char;
  char *key;
  char *original_key;
  current_char = getchar();

  while(current_char != EOF){
      key_char_index = 0;
      current_key_size = 60;
      key = calloc(current_key_size,sizeof(char));
      original_key = calloc(current_key_size,sizeof(char));
      if(key == NULL){
	  exit(61);
      }
      while(isalnum(current_char) == 0){
          if(current_char == EOF){
               break;
          }
          putchar(current_char);
          current_char = getchar();
      }
      while(isalnum(current_char) != 0){
          if(key_char_index == current_key_size-2){
               current_key_size = current_key_size * 2;
               key = realloc(key,sizeof(int) * current_key_size);
	       original_key = realloc(original_key,sizeof(int) * current_key_size);
          }
          key[key_char_index] = current_char;
	  original_key[key_char_index] = current_char;
          key_char_index++;
          current_char = getchar();
      }
      key[key_char_index] = '\0';
      original_key[key_char_index] = '\0';
      hash_value = (char*) findData(dictionary,key);
      if(hash_value != NULL){
	  printf("%s",hash_value);
      }
      else{
         string_length = strlen(key);
         for(i = 1; i < string_length ; i++){
	     key[i] = tolower(key[i]);
         }
         hash_value = (char*) findData(dictionary,key);
         if(hash_value != NULL){
	     printf("%s",hash_value);
         }
	 else{
            key[0] = tolower(key[0]);
            hash_value = (char*) findData(dictionary,key);
            if(hash_value != NULL){
      	       printf("%s",hash_value);
            }
	    else{
	       printf("%s",original_key);
	    }
	 }
      }
      free(key);
      free(original_key);
      key = NULL;
      original_key = NULL;
  }
  return;
}
