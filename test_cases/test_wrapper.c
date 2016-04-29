#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

char * str = "Some REAAAAAAAAAAAAAAAAAAAAAALLLLLY LONG STRING for testing";

void testMalloc(){
  printf("Testing malloc\n");
  char * p = malloc(10);
  strcpy(p, str);
  assert(strlen(p) == 9);
  p = malloc(20);
  strcpy(p, str);
  assert(strlen(p) == 19);
  free(p);
  char * q = malloc(30);
  strcpy(q, str);
  assert(strlen(q) == 29);
  free(q);
}

void testCalloc(){
  printf("Testing calloc\n");
  char * p = calloc(2,10);
  strcpy(p, str);
  assert(strlen(p) == 19);
  p = calloc(1,21);
  strcpy(p, str);
  assert(strlen(p) == 20);
  free(p);
  char * q = calloc(1,30);
  strcpy(q, str);
  assert(strlen(q) == 29);
  free(q);
  q = calloc(0,0);
  free(q);
}

void testFree(){
  printf("Testing free\n");
  char * p = malloc(10);
  strcpy(p, str);
  assert(strlen(p) == 9);
  p = malloc(20);
  strcpy(p, str);
  assert(strlen(p) == 19);
  //free(p);
  char * q = malloc(30);
  strcpy(q, str);
  assert(strlen(q) == 29);
  free(q);
  q = malloc(300);
  strcpy(q,str);
  assert(strlen(q) == strlen(str));
  free(q);
}

void testRealloc(){
  printf("Testing realloc\n");
  char * p = NULL;
  // this shoudl malloc
  p = realloc(p, 10);
  strcpy(p, str);
  assert(strlen(p) == 9);
  p = realloc(p, 9);
  strcpy(p, str);
  assert(strlen(p) == 8);
  p = realloc(p, 11);
  strcpy(p, str);
  assert(strlen(p) == 10);
  char * q = realloc(p,0);
  // below should be a nop
  free(q);
}

void testStrCpy(){
  printf("Testing strcpy\n");
  char * p;
  p = malloc(strlen(str)-10);
  strcpy(p, str);
  assert(strlen(p) == strlen(str)-11);
  free(p);
}

void testStrCat(){
  printf("Testing strcat\n");
  char * p;
  p = malloc(strlen(str) + 10);
  strcpy(p, str);
  strcat(p, str);
  assert(strlen(p) == strlen(str) + 9);
  free(p);
}

void testGetS(){
  printf("Testing gets\n");
  char * p = malloc(10);
  gets(p);
  assert(strlen(p) == 9);
  free(p);
}

int main(){
  printf("%s\n", str);
  testMalloc();
  testCalloc();
  testFree();
  testRealloc();
  testStrCpy();
  testStrCat();
  //testGetS();
  return 0;
}
