#ifndef linklist_h
#define linklist_h
#include <stdlib.h>

typedef struct Node {
	void * ptr;
	size_t size;
	struct Node *next;
} Node;

typedef struct {
	int count;
	Node* first;
} List;

List* createList();
// returns a pointer even if it lies in between allocated area
Node* findInList(List* list, void* value);
// if already exists, returns same
Node* addToList(List* list, void* ptr, size_t sz);
// removes only the node in the list and does not free memory. 0 if success -1 if not found
int removeFromList(List* list, void* ptr);
// helps debug
void clearList(List* list);

#endif
