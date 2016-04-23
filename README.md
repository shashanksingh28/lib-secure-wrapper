# lib-secure-wrapper
Small wrapper C library that remembers malloc's with their max-sizes and helps convert vulnerable overflow calls to safer calls

`gcc -shared -fPIC wrapper.c linkedlist.c -o <libsafe.so>
LD_PRELOAD=./<libsafe.so> <binary>`
