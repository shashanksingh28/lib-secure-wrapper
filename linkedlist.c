//@author: shashank.h.singh@asu.edu
#define _GNU_SOURCE
#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

// underlying libc functions that we will use
void * (*libc_malloc)(size_t);
void (*libc_free)(void*);
char * error;

Node* createNode(void* ptr, size_t size){
	if (libc_malloc == NULL){
		libc_malloc = dlsym(RTLD_NEXT,"malloc");
		if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
	}
	Node* n = libc_malloc(sizeof(Node));
	n -> ptr = ptr;
	n -> size = size;
	n -> next = NULL;
	//printf("Saved %p : %zd\n", ptr, size);
	return n;
}

List* createList(){
	if (libc_malloc == NULL){
		libc_malloc = dlsym(RTLD_NEXT,"malloc");
		if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
	}
	List * list = libc_malloc(sizeof(List));
	if (list != NULL){
		list -> first = NULL;
	}
	return list;
}

Node * addToList(List * list, void * ptr, size_t size){
	if (list == NULL || ptr == NULL){
		return NULL;
	}
	Node * existing = findInList(list, ptr);
	if (existing != NULL){
		// update the existing size
		// this would fail to save actually if the ptr was found somewhere in between region, but that ideally should never be the case
		existing -> size = size;
		return existing;
	}

	// reaching here means add to end of list
	if (list -> first == NULL){
		list -> first = createNode(ptr, size);
		return list -> first;
	}
	Node * prev = list -> first;
	Node * curr = prev -> next;
	while(curr != NULL){
		prev = curr;
		curr = curr -> next;
	}
	prev -> next = createNode(ptr, size);
	return prev -> next;
}

Node * findInList(List * list, void * ptr){
	if (list == NULL || ptr == NULL){
		return NULL;
	}

	Node * curr = list -> first;
	while(curr != NULL){
		if (curr -> ptr == ptr){
			return curr;
		}
		// Could paging affect this?
		else if ((ptr - curr -> ptr) > 0 && ((ptr - curr -> ptr) < curr -> size)){
			// pointer falls within range. return a node with ptr and remaining size
			Node * tempNode = libc_malloc(sizeof(Node));
			tempNode -> ptr = ptr;
			tempNode -> size = curr -> size - (ptr - curr -> ptr);
			return tempNode;
		}
		curr = curr -> next;
	}
	return curr;
}

int removeFromList(List * list, void * ptr){
	if (list == NULL || ptr == NULL){
		return -1;
	}

	if (libc_free == NULL){
		libc_free = dlsym(RTLD_NEXT,"free");
		if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
	}

	Node * curr = list -> first;
	if (curr -> ptr == ptr){
		list -> first = curr -> next;
		curr -> next = NULL;
		libc_free(curr);
		return 0;
	}

	Node * prev = curr;
	curr = prev -> next;
	while(curr != NULL){
		if (curr -> ptr == ptr){
			prev -> next = curr -> next;
			curr -> next = NULL;
			libc_free(curr);
			return 0;
		}
		prev = curr;
		curr = curr -> next;
	}

	return -1;
}

void clearList(List * list){
	if (list == NULL) return;
	if (libc_free == NULL){
		libc_free = dlsym(RTLD_NEXT,"free");
		if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
	}

	Node* curr = list -> first;
	while (curr != NULL){
		Node * temp = curr -> next;
		libc_free(curr);
		curr = temp;
	}
	list -> first = NULL;
}
