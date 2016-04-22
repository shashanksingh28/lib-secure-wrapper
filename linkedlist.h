#ifndef linklist_h
#define linklist_h

#include <stdlib.h>

typedef struct Node {
	void * p;
	size_t max_sz;
	struct Node *next;
} Node;

typedef struct {
	int count;
	Node* first;
} List;

List* createList();
void destroyList(List* list);
void clearList(List* list);
Node* findInList(List* list, void* value);
Node* addToList(List* list, void* p, size_t sz);
Node* removeFromList(List* list, void* p);

#endif
