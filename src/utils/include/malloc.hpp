#pragma once

// ALL THE CREDIT FOR THIS FILE GOES TO Max Klein (https://github.com/maxkl/) 
// FROM THE PROJECT https://github.com/maxkl/wasm-malloc

#include <stddef.h>
#include <stdint.h>

extern "C" {
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);

void *memcpy(void *dst, const void *src, size_t len);
void *memset(void *dst, uint8_t data, size_t len);
}