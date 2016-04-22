// References:
// http://stackoverflow.com/questions/262439/create-a-wrapper-function-for-malloc-and-free-in-c
// @author : shashanksingh28@gmail.com
//
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "linkedlist.h"

void *(*libc_malloc)(size_t);
void (*libc_free)(void * p);

// Linked List that stores allocated pointers with their maxSizes
List* ptrSizes;

void* malloc(size_t sz)
{
    if (libc_malloc == NULL){
    	libc_malloc = dlsym(RTLD_NEXT, "malloc");
	}
	if (ptrSizes == NULL) ptrSizes = createList();

    void *p = libc_malloc(sz);
	addToList(ptrSizes, p, sz);
    printf("Saved %p : %zd bytes\n", p, sz);
    return p;
}

void free(void* p){
	if (libc_free == NULL){
		libc_free = dlsym(RTLD_NEXT, "free");
	}
	if (ptrSizes == NULL) ptrSizes = createList();

	Node* removed = removeFromList(ptrSizes, p);
	libc_free(p);
	if (removed == NULL){
		// not found in our list. probably not called via malloc
		printf("Not found %p\n",p);
	}
	else{
		printf("Removed %p : %zd\n", removed -> p, removed -> max_sz);
	}
}

