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
Node* findInList(List* list, void* value);
Node* addToList(List* list, void* p, size_t sz);
int removeFromList(List* list, void* p);

#endif
