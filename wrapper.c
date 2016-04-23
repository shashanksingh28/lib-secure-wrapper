// References:
// http://stackoverflow.com/questions/262439/create-a-wrapper-function-for-malloc-and-free-in-c
// @author : shashanksingh28@gmail.com
//
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include "linkedlist.h"

void *(*libc_malloc)(size_t);
void (*libc_free)(void * p);
// Original overflow functions
char *(*libc_strcpy)(char * dest, const char * src);
char *(*libc_strcat)(char * dest, const char * src);
char *(*libc_gets)(char *s);

// Linked List that stores allocated pointers with their maxSizes
List * ptrSizes;

void * malloc(size_t sz)
{
    if (libc_malloc == NULL) libc_malloc = dlsym(RTLD_NEXT, "malloc");
	if (ptrSizes == NULL) ptrSizes = createList();

    void *p = libc_malloc(sz);
	addToList(ptrSizes, p, sz);
    printf("Saved %p : %zd bytes\n", p, sz);
    return p;
}

void free(void* p){
	if (libc_free == NULL) libc_free = dlsym(RTLD_NEXT, "free");
	if (ptrSizes == NULL) ptrSizes = createList();

	Node* removed = removeFromList(ptrSizes, p);
	
	if (removed != NULL){
		libc_free(p);
		printf("Removed %p : %zd\n", removed -> p, removed -> max_sz);
	}
	else{
		printf("Invalid free call for %p, not allocated\n", p);
	}
}

char * strcpy(char * dest, const char * src){
	if (ptrSizes == NULL) ptrSizes = createList();
	if (libc_strcpy == NULL) libc_strcpy = dlsym(RTLD_NEXT, "strcpy");

	Node* node = findInList(ptrSizes, dest);
	if (node != NULL){
		printf("Found %p : %zd, using strncpy instead of strcpy..\n", dest,node -> max_sz );
		dest = strncpy(dest, src, node -> max_sz - 1);
		dest[node -> max_sz - 1] = '\0';
	}
	else{
		// not memory of malloc. Can't help yet
		dest = libc_strcpy(dest, src);
	}
	return dest;
}

char * strcat(char * dest, const char * src){
	if (ptrSizes == NULL) ptrSizes = createList();
	if (libc_strcat == NULL) libc_strcat = dlsym(RTLD_NEXT, "strcat");

	Node* node = findInList(ptrSizes, dest);
	if (node != NULL){
		size_t curr_sz = strlen(dest);
		size_t left = node -> max_sz - curr_sz - 1;
		dest = strncat(dest, src, left);
	}
	else{
		// no memory of malloc. Can't help yet
		dest = libc_strcat(dest, src);
	}
	return dest;
}

char * gets(char * s){
	if (ptrSizes == NULL) ptrSizes = createList();
	if (libc_gets == NULL) libc_gets = dlsym(RTLD_NEXT, "gets");
	
	Node* node = findInList(ptrSizes, s);
	if(node != NULL){
		return fgets(s, node -> max_sz, stdin);
	}
	else{
		return libc_gets(s);
	}
}


