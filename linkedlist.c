#define _GNU_SOURCE
#include "linkedlist.h"
#include <stdlib.h>
#include <dlfcn.h>

// Use these so that we don't fall into an eternal loop
void * (*libc_malloc)(size_t);
void (*libc_free)(void* ptr);

List* createList(){
	if (libc_malloc == NULL){
		libc_malloc = dlsym(RTLD_NEXT,"malloc");
	}
	List * l = libc_malloc(sizeof(List));
	l -> first = NULL;
	return l;
}

Node* createNode(void* p, size_t sz){
	if (libc_malloc == NULL){
		libc_malloc = dlsym(RTLD_NEXT,"malloc");
	}
	Node* n = libc_malloc(sizeof(Node));
	n -> p = p;
	n -> max_sz = sz;
	n -> next = NULL;
	return n;
}

Node* addToList(List* l, void* p, size_t sz){
	if (l == NULL) return NULL;
	if (l -> first == NULL){
		l -> first = createNode(p,sz);
		return l -> first;
	}

	if (l -> first -> p == p) return l -> first;
		
	Node* curr = l -> first -> next;
	Node* prev = l -> first;
	while (curr != NULL){
		if (curr -> p == p){
			return curr;
		}
		prev = curr;
		curr = curr -> next;
	}
	// reaching here means adding to end
	prev -> next = createNode(p, sz);
	return prev -> next;
}

Node* findInList(List* l, void* p){
	if (l == NULL || l -> first == NULL) return NULL;

	Node *curr = l -> first;
	while(curr != NULL){
		if(curr -> p == p){
			return curr;
		}
		curr = curr -> next;
	}
	return curr;
}

int removeFromList(List* l, void* p){
	if (libc_free == NULL){
		libc_free = dlsym(RTLD_NEXT,"free");
	}
	if (l == NULL || l -> first == NULL) return -1;
	
	if (l -> first -> p == p){
		Node* temp = l -> first;
		l -> first = l -> first -> next;
		//libc_free(temp);
		return 0;
	}

	Node* curr = l -> first -> next;
	Node* prev = l -> first;
	while(curr != NULL){
		if (curr -> p == p){
			Node* temp = curr;
			prev -> next = curr -> next;
			//libc_free(curr);
			return 0;
		}
		prev = curr;
		curr = curr -> next;
	}
	return -1;
}
