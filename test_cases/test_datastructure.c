#include "linkedlist.h"
#include <stdio.h>
#include <assert.h>

void testClearList(List * list){
  char * p1 = malloc(10);
  addToList(list, p1, 10);
  char * p2 = malloc(20);
  addToList(list, p2, 20);
  clearList(list);
  assert(list -> first == NULL);
}

void testFindFirst(List * list){
  char * p1 = malloc(10);
  addToList(list, p1, 10);
  char * p2 = malloc(20);
  addToList(list, p2, 20);
  char * p3 = malloc(30);
  addToList(list, p3, 30);
  Node *node = findInList(list, p1);
  assert(node != NULL);
}

void testFindMiddle(List * list){
  char * p1 = malloc(10);
  addToList(list, p1, 10);
  char * p2 = malloc(20);
  addToList(list, p2, 20);
  char * p3 = malloc(30);
  addToList(list, p3, 30);
  Node *node = findInList(list, p2);
  assert(node != NULL);
}

void testFindLast(List * list){
  char * p1 = malloc(10);
  addToList(list, p1, 10);
  char * p2 = malloc(20);
  addToList(list, p2, 20);
  char * p3 = malloc(30);
  addToList(list, p3, 30);
  Node *node = findInList(list, p3);
  assert(node != NULL);
}

void testFindInRange(List * list){
  char * p1 = malloc(10);
  addToList(list, p1, 10);
  char * p2 = malloc(200);
  addToList(list, p2, 200);
  char * p3 = malloc(30);
  addToList(list, p3, 30);
  Node *node = findInList(list, (p2 + 100));
  assert(node != NULL);
}

void testRemoveFirst(List * list){
  char * p1 = malloc(10);
  addToList(list, p1, 10);
  char * p2 = malloc(20);
  addToList(list, p2, 20);
  char * p3 = malloc(30);
  addToList(list, p3, 30);
  int i = removeFromList(list, p1);
  assert ( i == 0);
  Node *node = findInList(list, p3);
  assert(node != NULL);
}

void testRemoveMiddle(List * list){
  char * p1 = malloc(10);
  addToList(list, p1, 10);
  char * p2 = malloc(20);
  addToList(list, p2, 20);
  char * p3 = malloc(30);
  addToList(list, p3, 30);
  int i = removeFromList(list, p2);
  assert ( i == 0);
  Node *node = findInList(list, p3);
  assert(node != NULL);
}

void testRemoveLast(List * list){
  char * p1 = malloc(10);
  addToList(list, p1, 10);
  char * p2 = malloc(20);
  addToList(list, p2, 20);
  char * p3 = malloc(30);
  addToList(list, p3,30);
  int i = removeFromList(list, p3);
  assert ( i == 0);
  Node *node = findInList(list, p2);
  assert(node != NULL);
}

void testRemoveAll(List * list){
  char * p1 = malloc(10);
  addToList(list, p1, 10);
  char * p2 = malloc(20);
  addToList(list, p2, 20);
  char * p3 = malloc(30);
  addToList(list, p3,30);
  int i = removeFromList(list, p3);
  assert ( i == 0);
  i = removeFromList(list, p1);
  assert ( i == 0);
  i = removeFromList(list, p2);
  assert ( i == 0);
  Node *node = findInList(list, p2);
  assert(node == NULL);
  addToList(list, p2, 20);
  node = findInList(list, p2);
  assert(node != NULL);
}

void testRemoveAbsent(List * list){
  char * p1 = malloc(10);
  addToList(list, p1,10);
  char * p2 = malloc(20);
  int i = removeFromList(list, p2);
  assert(i == -1);
}

int main(){
  List* list = createList();
  printf("test1\n");
  testClearList(list);
  printf("test2\n");
  testFindFirst(list);
  clearList(list);
  printf("test3\n");
  testFindMiddle(list);
  clearList(list);
  printf("test4\n");
  testFindLast(list);
  clearList(list);
  printf("test5\n");
  testFindInRange(list);
  clearList(list);
  printf("test6\n");
  testRemoveFirst(list);
  clearList(list);
  printf("test7\n");
  testRemoveMiddle(list);
  clearList(list);
  printf("test8\n");
  testRemoveLast(list);
  clearList(list);
  printf("test9\n");
  testRemoveAbsent(list);
  clearList(list);
  printf("test10\n");
  testRemoveAbsent(list);
  clearList(list);
  return 0;
}
