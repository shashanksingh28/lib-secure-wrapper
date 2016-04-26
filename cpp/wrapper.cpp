#define _GNU_SOURCE
#include <unordered_map>
#include <dlfcn.h>
#include <iostream>
#include <cstdlib>

std::unordered_map<void *, size_t> map;
void *(*libc_malloc)(size_t);
void (*libc_free)(void *);

// Overflow functions
char *(*libc_strcpy)(char * , const char * );
char *(*libc_strcat)(char * , const char * );
char *(*libc_gets)(char *);

void * malloc(size_t size){
	if (libc_malloc == NULL) libc_malloc = (void *(*)(size_t)) dlsym(RTLD_NEXT, "malloc");

	void * ptr = libc_malloc(size);
	map[ptr] = size;
	std::cout << "Saved : "<< ptr <<" : "<< size << std::endl;
	return ptr;
}

void free(void * ptr){
	if (libc_free == NULL) libc_free = (void (*)(void *)) dlsym(RTLD_NEXT, "free");
	
	map.erase(ptr);
	libc_free(ptr);
}

char * strcpy(char * dest, char* src){
	std::cout<<"Custom strcpy called"<<std::endl;
	if (libc_strcpy == NULL) libc_strcpy = (char * (*)(char *,const char *)) dlsym(RTLD_NEXT, "strcpy");

	std::unordered_map<void *, size_t>::const_iterator got = map.find(dest);

	if(got == map.end()){
		std::cout<<"No memory of heap allocating : "<<dest<<std::endl;
		dest = libc_strcpy(dest, src);
	}
	else{
		size_t max_size = got -> second;
		std::cout<<dest<<" : "<<max_size<<std::endl;
		dest = strncpy(dest,src,max_size);
	}

	return dest;
}
