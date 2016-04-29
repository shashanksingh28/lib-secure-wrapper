#include <cstdlib>
#include <iostream>
#include <string.h>

int main(){
  char * p;
  p = (char *) malloc(10);
  strcpy(p,"check out this cool new line!\n");
  std::cout << p;
  return 0;
}
