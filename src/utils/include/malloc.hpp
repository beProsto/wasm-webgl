#pragma once

// ALL THE CREDIT FOR THIS FILE GOES TO Max Klein (https://github.com/maxkl/) 
// FROM THE PROJECT https://github.com/maxkl/wasm-malloc

#include <stddef.h>
#include <stdint.h>

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);

inline void *memcpy(void *dst, const void *src, size_t len) {
	size_t i;

	if(
		(uintptr_t)dst % sizeof(long) == 0 &&
		(uintptr_t)src % sizeof(long) == 0 &&
		len % sizeof(long) == 0
	) {
		long *d = (long *)dst;
		const long *s = (const long *)src;

		for(i=0; i<len/sizeof(long); i++) {
			d[i] = s[i];
		}
	}
	else {
		char *d = (char *)dst;
		const char *s = (const char *)src;

		for(i=0; i<len; i++) {
			d[i] = s[i];
		}
	}

	return dst;
}
inline void *amemset(void *dst, uint8_t data, size_t len) {
	uint8_t* ptr = (uint8_t*)dst;

	for(; ptr < ((uint8_t*)dst)+len; ptr++) {
		*ptr = data;
	}
	
	return dst;
}