// References:
// http://stackoverflow.com/questions/262439/create-a-wrapper-function-for-malloc-and-free-in-c

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "linkedlist.h"

void * (*libc_malloc)(size_t);

void* malloc(size_t sz)
{
    if (libc_malloc == NULL){
    	libc_malloc = dlsym(RTLD_NEXT, "malloc");
	}
    void *p = libc_malloc(sz);
    printf("custom malloc returned %p with %zd bytes\n",p,sz);
    return p;
}
