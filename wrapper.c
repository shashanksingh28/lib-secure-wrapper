// @author : shashank.h.singh@asu.edu
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include "linkedlist.h"

// functions to provide wrappers of
void *(*libc_malloc)(size_t);
void *(*libc_realloc)(void * , size_t);
void *(*libc_calloc)(size_t ,size_t);
void (*libc_free)(void * );
// Original overflow functions
char *(*libc_strcpy)(char * , const char * );
char *(*libc_strcat)(char * , const char * );
char *(*libc_gets)(char *);

// datastructure to store pointer - size mappings
List * list;
char * error;

void * malloc(size_t size){
  /* error checks and initializations */
  if (libc_malloc == NULL){
		libc_malloc = dlsym(RTLD_NEXT,"malloc");
		if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
	}
  if (list == NULL) list = createList();
  /* -- */

  void * newp = libc_malloc(size);
  addToList(list, newp, size);
  return newp;
}

void free(void * oldp){
  /* error checks and initializations */
  if (libc_free == NULL){
		libc_free = dlsym(RTLD_NEXT,"free");
		if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
	}
  if (list == NULL) list = createList();
  /* -- */

  removeFromList(list, oldp);
  libc_free(oldp);
}

void * realloc(void * oldp, size_t new_size) {
  /* error checks and initializations */
  if (libc_realloc == NULL){
		libc_realloc = dlsym(RTLD_NEXT,"realloc");
		if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
	}
  if (list == NULL) list = createList();
  /* -- */

  void * newp = libc_realloc(oldp, new_size);
  if (oldp == NULL) {
    // realloc internally calls malloc, so add newp
    addToList(list, newp, new_size);
  }
  else{
    if (new_size == 0) {
      // realloc internally calls free, so remove oldp
      removeFromList(list, oldp);
    }
    else{
      // change has happened. are they the same?
      if (newp == oldp) {
        addToList(list, newp, new_size);
      }
      else{
        // remove old and add newp
        removeFromList(list, oldp);
        addToList(list, newp, new_size);
      }
    }
  }

  return newp;
}

void * calloc(size_t num, size_t size) {
  /* error checks and initializations */
  if (libc_calloc == NULL){
		libc_calloc = dlsym(RTLD_NEXT,"calloc");
		if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
	}
  if (list == NULL) list = createList();
  /* -- */
  
  void * newp = libc_calloc(num, size);
  addToList(list, newp, (num * size));
  return newp;
}

// Returns safe, null terminated dest (might loose last byte for safety)
char * strcpy(char * dest, const char * src){
  /* error checks and initializations */
  if (libc_strcpy == NULL){
		libc_strcpy = dlsym(RTLD_NEXT,"strcpy");
		if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
	}
  if (list == NULL) list = createList();
  /* -- */

  Node * node = findInList(list, dest);
  if (node != NULL){
    //printf("Using strncpy(%p,%p,%zd)\n", dest, src, node -> size);
		dest = strncpy(dest, src, node -> size - 1);
    dest[node -> size - 1] = '\0';
  }
  else{
    // Not in heap. Future scope for something?
    dest = libc_strcpy(dest, src);
  }
  return dest;
}

// Returns safe, null terminated dest (might loose last byte for safety)
char * strcat(char * dest, const char * src) {
  /* error checks and initializations */
  if (libc_strcat == NULL){
    libc_strcat = dlsym(RTLD_NEXT,"strcat");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
  }
  if (list == NULL) list = createList();
  /* -- */

  Node * node = findInList(list, dest);
  if (node != NULL) {
    size_t curr = strlen(dest);
    size_t left = node -> size - curr;
    if (left > 0) {
      //printf("Using strncat(%p,%p,%zd)\n", dest, src, left);
      dest = strncat(dest, src, left - 1);
    } else {
      //printf("Skipping strcat(%p,%p) as there is no room left in %p\n", dest, src, dest);
    }
  }
  else {
    // Not in heap, future scope
    dest = libc_strcat(dest, src);
  }
  return dest;
}

char * gets(char * s) {
  /* error checks and initializations */
  if (libc_gets == NULL){
    libc_gets = dlsym(RTLD_NEXT,"gets");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
  }
  if (list == NULL) list = createList();
  /* -- */

  Node * node = findInList(list, s);
  if (node != NULL) {
    //printf("Using fgest(%p, %zd, stdin)\n", s, node -> size);
    return fgets(s, node -> size, stdin);
  }

  return libc_gets(s);
}
