# lib-secure-wrapper
Small wrapper C library that remembers malloc's with their max-sizes and helps convert vulnerable overflow calls to safer calls

`gcc -g -shared -fPIC -o <libsafer.so> wrapper.c linkedlist.c -ldl
LD_PRELOAD=./<libsafe.so> <path to binary>`

Further Improvements : 
1. Use hashmap instead of linked list for linear performance.
2. Check why gdb and vim fail with this library.
3. See if something is possible for dealing with stack based buffers
