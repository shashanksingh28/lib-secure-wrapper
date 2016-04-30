# lib-secure-wrapper
Small wrapper C library that remembers malloc's with their max-sizes and helps convert vulnerable overflow calls to safer calls

Compile:
`gcc -shared -fPIC -o <libsafer.so> wrapper.c linkedlist.c -ldl`

Run:
`LD_PRELOAD=./<libsafe.so> <path to binary>`

Test Cases in test_cases folder. Running them without LD_PRELOAD should give seg-faults/memory corruption.

Bugs:
1. dlsym - calloc recursive call loops
2. Known seg-faults with vim, gdb and python

Further Improvements : 
1. Use hashmap instead of linked list for linear performance
2. See if malloc-hooks is a better approach
3. See if something is possible for dealing with stack based buffers
